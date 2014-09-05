// Copyright 2014 MongoDB Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <cstdint>

#include "bson/builder.hpp"

#include "driver/libmongoc.hpp"

#include "driver/base/private/collection.hpp"
#include "driver/base/private/database.hpp"
#include "driver/model/private/bulk_write.hpp"
#include "driver/base/collection.hpp"
#include "driver/base/client.hpp"
#include "driver/model/aggregate.hpp"
#include "driver/model/find.hpp"
#include "driver/model/find_one_and_replace.hpp"
#include "driver/model/find_one_and_remove.hpp"
#include "driver/model/find_one_and_update.hpp"
#include "driver/model/insert_one.hpp"
#include "driver/model/update_one.hpp"
#include "driver/private/cast.hpp"
#include "driver/result/bulk_write.hpp"
#include "driver/result/insert_many.hpp"
#include "driver/result/insert_one.hpp"
#include "driver/result/remove.hpp"
#include "driver/result/remove.hpp"
#include "driver/result/replace_one.hpp"
#include "driver/result/update.hpp"
#include "driver/result/write.hpp"
#include "driver/result/bulk_write.hpp"
#include "driver/request/insert.hpp"
#include "driver/util/libbson.hpp"
#include "driver/model/bulk_write.hpp"
#include "driver/model/write.hpp"

namespace mongo {
namespace driver {

using namespace bson::libbson;

collection::collection(collection&&) = default;
collection& collection::operator=(collection&&) = default;
collection::~collection() = default;

collection::collection(const database& database, const std::string& collection_name)
    : _impl(new impl{mongoc_database_get_collection(database._impl->database_t,
                                                 collection_name.c_str()), &database, database._impl->client, collection_name.c_str()}) {}

result::bulk_write collection::bulk_write(const model::bulk_write& model) {
    using namespace model;

    mongoc_bulk_operation_t* b = model._impl->operation_t;
    mongoc_bulk_operation_set_database(b, _impl->database->_impl->name.c_str());
    mongoc_bulk_operation_set_collection(b, _impl->name.c_str());
    mongoc_bulk_operation_set_client(b, util::cast<mongoc_client_t>(_impl->client->_client));
    mongoc_bulk_operation_set_write_concern(b, mongoc_collection_get_write_concern(_impl->collection_t));

    result::bulk_write result;

    scoped_bson_t reply;
    reply.flag_init();

    bson_error_t error;

    if (! mongoc_bulk_operation_execute(b, reply.bson(), &error)) {
        throw std::runtime_error(error.message);
    }

    bson::document::view reply_view = reply.view();

    result.is_acknowledged = true;
    result.inserted_count = reply_view["nInserted"].get_int32();
    result.matched_count = reply_view["nMatched"].get_int32();
    result.modified_count = reply_view["nModified"].get_int32();
    result.removed_count = reply_view["nRemoved"].get_int32();
    result.upserted_count = reply_view["nUpserted"].get_int32();

    return result;
}

cursor collection::find(const model::find& model) const {
    using namespace bson;

    builder filter_builder;

    scoped_bson_t filter;
    scoped_bson_t projection(model.projection());

    if (model.modifiers()) {
        filter_builder << "$query" << types::b_document{model.criteria()}
                       << builder_helpers::concat{model.modifiers().value_or(document::view{})};

        filter.init_from_static(filter_builder.view());
    } else {
        filter.init_from_static(model.criteria());
    }

    return cursor(mongoc_collection_find(_impl->collection_t,
                                         (mongoc_query_flags_t)model.cursor_flags().value_or(0),
                                         model.skip().value_or(0), model.limit().value_or(0),
                                         model.batch_size().value_or(0), filter.bson(),
                                         projection.bson(), nullptr));
}

optional<bson::document::value> collection::find_one(const model::find& model) const {
    model::find copy(model);
    copy.limit(1);
    return bson::document::value{*find(copy).begin()};
}

cursor collection::aggregate(const model::aggregate& /* model */) { return cursor(nullptr); }

result::insert_one collection::insert_one(const model::insert_one& model) {
    result::bulk_write res(bulk_write(model::bulk_write(false).append(model)));

    result::insert_one result;
    result.is_acknowledged = true;
    return result;
}

result::insert_many collection::insert_many(const model::insert_many& model) {
    result::bulk_write res(bulk_write(model::bulk_write(false).append(model)));
    result::insert_many result;
    result.is_acknowledged = true;
    return result;
}


result::replace_one collection::replace_one(const model::replace_one& /* model */) {
    return result::replace_one();
}

result::update collection::update_many(const model::update_many& /* model */) {
    return result::update();
}
result::remove collection::remove_many(const model::remove_many& model) {
    result::bulk_write res(bulk_write(model::bulk_write(false).append(model)));
    result::remove result;
    result.is_acknowledged = true;
    return result;
}

result::update collection::update_one(const model::update_one& model) {
    result::bulk_write res(bulk_write(model::bulk_write(false).append(model)));
    result::update result;
    result.is_acknowledged = true;
    return result;
}

result::remove collection::remove_one(const model::remove_one& model) {
    result::bulk_write res(bulk_write(model::bulk_write(false).append(model)));
    result::remove result;
    result.is_acknowledged = true;
    return result;
}

optional<bson::document::value> collection::find_one_and_replace(const model::find_one_and_replace& model) {
    scoped_bson_t criteria{model.criteria()};
    scoped_bson_t sort{model.sort()};
    scoped_bson_t replacement{model.replacement()};
    scoped_bson_t projection{model.projection()};
    scoped_bson_t reply;
    reply.flag_init();

    bson_error_t error;

    bool r = mongoc_collection_find_and_modify(
        _impl->collection_t,
        criteria.bson(),
        sort.bson(),
        replacement.bson(),
        projection.bson(),
        false,
        model.upsert().value_or(false),
        model.return_replacement().value_or(false),
        reply.bson(),
        &error);

    if (!r) {
        throw std::runtime_error("shits fucked");
    }

    bson::document::view result = reply.view();

    if (result["value"].type() == bson::type::k_null) {
        return optional<bson::document::value>{};
    } else {
        using namespace bson::builder_helpers;

        bson::builder b;

        b << concat{result["value"].get_document()};

        return b.extract();
    }
}

optional<bson::document::value> collection::find_one_and_update(const model::find_one_and_update& model) {
    scoped_bson_t criteria{model.criteria()};
    scoped_bson_t sort{model.sort()};
    scoped_bson_t update{model.update()};
    scoped_bson_t projection{model.projection()};
    scoped_bson_t reply;
    reply.flag_init();

    bson_error_t error;

    bool r = mongoc_collection_find_and_modify(
        _impl->collection_t,
        criteria.bson(),
        sort.bson(),
        update.bson(),
        projection.bson(),
        false,
        model.upsert().value_or(false),
        model.return_replacement().value_or(false),
        reply.bson(),
        &error);

    if (!r) {
        throw std::runtime_error("shits fucked");
    }

    bson::document::view result = reply.view();

    if (result["value"].type() == bson::type::k_null) {
        return optional<bson::document::value>{};
    } else {
        using namespace bson::builder_helpers;

        bson::builder b;

        b << concat{result["value"].get_document()};

        return b.extract();
    }
}

optional<bson::document::value> collection::find_one_and_remove(const model::find_one_and_remove& model) {
    scoped_bson_t criteria{model.criteria()};
    scoped_bson_t sort{model.sort()};
    scoped_bson_t projection{model.projection()};
    scoped_bson_t reply;
    reply.flag_init();

    bson_error_t error;

    bool r = mongoc_collection_find_and_modify(
        _impl->collection_t,
        criteria.bson(),
        sort.bson(),
        nullptr,
        projection.bson(),
        true,
        false,
        false,
        reply.bson(),
        &error);

    if (!r) {
        throw std::runtime_error("shits fucked");
    }

    bson::document::view result = reply.view();

    if (result["value"].type() == bson::type::k_null) {
        return optional<bson::document::value>{};
    } else {
        using namespace bson::builder_helpers;

        bson::builder b;

        b << concat{result["value"].get_document()};

        return b.extract();
    }
}

bson::document::value collection::explain(const model::explain& /*model*/) const {
    return bson::document::value((const std::uint8_t*)nullptr, 0);
}

std::int64_t collection::count(const model::count& model) const {
    scoped_bson_t criteria{model.criteria()};
    bson_error_t error;
    auto result = mongoc_collection_count(_impl->collection_t, static_cast<mongoc_query_flags_t>(0),
                                          criteria.bson(), model.skip().value_or(0),
                                          model.limit().value_or(0), nullptr, &error);

    /* TODO throw an exception if error
    if (result < 0)
    */

    return result;
}

void collection::drop() {
    bson_error_t error;

    if (mongoc_collection_drop(_impl->collection_t, &error)) {
        /* TODO handle errors */
    }
}

}  // namespace driver
}  // namespace mongo

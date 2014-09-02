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

#include "driver/libmongoc.hpp"

#include "driver/base/collection.hpp"
#include "driver/base/client.hpp"
#include "driver/model/aggregate.hpp"
#include "driver/model/find.hpp"
#include "driver/model/insert.hpp"
#include "driver/model/update.hpp"
#include "driver/private/cast.hpp"
#include "driver/result/write.hpp"
#include "driver/result/distinct.hpp"
#include "driver/request/insert.hpp"
#include "driver/util/libbson.hpp"

namespace mongo {
namespace driver {

using namespace bson::libbson;

namespace {
static void mongoc_collection_dtor(void* collection_ptr) noexcept {
    mongoc_collection_destroy(static_cast<mongoc_collection_t*>(collection_ptr));
}
}  // namespace

collection::collection(const database& database, const std::string& collection_name)
    : _collection(mongoc_database_get_collection(util::cast<mongoc_database_t>(database._database),
                                                 collection_name.c_str()),
                  mongoc_collection_dtor) {}

cursor collection::find(const model::find& model) const {
    scoped_bson_t filter;
    scoped_bson_t projection(model.projection());

    if (model.modifiers()) {
        scoped_bson_t query(model.criteria());
        scoped_bson_t modifiers(model.modifiers());

        filter.init();

        BSON_APPEND_DOCUMENT(filter.bson(), "&query", query.bson());
        bson_concat(filter.bson(), modifiers.bson());
    } else {
        filter.init_from_static(model.criteria());
    }

    return cursor(mongoc_collection_find(util::cast<mongoc_collection_t>(_collection),
                                         (mongoc_query_flags_t)model.cursor_flags().value_or(0),
                                         model.skip().value_or(0), model.limit().value_or(0),
                                         model.batch_size().value_or(0), filter.bson(),
                                         projection.bson(), nullptr));
}

cursor collection::aggregate(const model::aggregate& /* model */) const { return cursor(nullptr); }

result::write collection::replace_one(const model::replace& /* model */) { return result::write(); }

result::write collection::update_many(const model::update& /* model */) { return result::write(); }
result::write collection::remove_many(const model::remove& /* model */) { return result::write(); }

result::write collection::update_one(const model::update& /* model */) { return result::write(); }
result::write collection::remove_one(const model::remove& /* model */) { return result::write(); }

bson::document::value collection::find_one_and_replace(
    const model::find_one_and_replace& /* model */) {
    return bson::document::value((const std::uint8_t*)nullptr, 0);
}
bson::document::value collection::find_one_and_update(
    const model::find_one_and_update& /* model */) {
    return bson::document::value((const std::uint8_t*)nullptr, 0);
}
bson::document::value collection::find_one_and_remove(
    const model::find_one_and_remove& /* model */) {
    return bson::document::value((const std::uint8_t*)nullptr, 0);
}

bson::document::value collection::explain(const model::explain& /*model*/) const {
    return bson::document::value((const std::uint8_t*)nullptr, 0);
}

result::distinct collection::distinct(const model::distinct& /* model */) const {
    return result::distinct();
}
std::int64_t collection::count(const model::count& /* model */) const { return 0; }

void collection::drop() {
    bson_error_t error;

    if (mongoc_collection_drop(util::cast<mongoc_collection_t>(_collection), &error)) {
        /* TODO handle errors */
    }
}

}  // namespace driver
}  // namespace mongo

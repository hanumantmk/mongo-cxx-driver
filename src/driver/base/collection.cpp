/**
 * Copyright 2014 MongoDB Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "private/preamble.hpp"

#include <cstdint>

#include "mongoc.h"
#include "bson.h"

#include "driver/base/collection.hpp"
#include "driver/base/client.hpp"
#include "driver/model/aggregate.hpp"
#include "driver/model/find.hpp"
#include "driver/model/insert.hpp"
#include "driver/model/update.hpp"
#include "driver/result/write.hpp"
#include "driver/result/distinct.hpp"
#include "driver/request/insert.hpp"
#include "driver/util/libbson.hpp"

namespace mongo {
namespace driver {

using namespace bson::libbson;

collection::collection(client* client, database* database, std::string name)
    : _client(client), _name(name) {
    _collection = libmongoc::client_get_collection(
        _client->_client, database->_name.c_str(), name.c_str());
}

collection::collection(collection&& rhs) {
    _database = rhs._database;
    _client = rhs._client;
    _collection = rhs._collection;
    _name = std::move(rhs._name);
}

collection& collection::operator=(collection&& rhs) {
    _database = rhs._database;
    _client = rhs._client;
    _collection = rhs._collection;
    _name = std::move(rhs._name);
    return *this;
}

collection::~collection() { libmongoc::collection_destroy(_collection); }

cursor collection::find(const model::find& model) const {
    scoped_bson_t filter;
    scoped_bson_t projection(model.projection());

    if (model.modifiers()) {
        scoped_bson_t query(model.filter());
        scoped_bson_t modifiers(model.modifiers());

        filter.init();

        BSON_APPEND_DOCUMENT(filter.bson(), "&query", query.bson());
        bson_concat(filter.bson(), modifiers.bson());
    } else {
        filter.init_from_static(model.filter());
    }

    return cursor(libmongoc::collection_find(
        _collection,
        (mongoc_query_flags_t)model.cursor_flags().value_or(0),
        model.skip().value_or(0),
        model.limit().value_or(0),
        model.batch_size().value_or(0),
        filter.bson(),
        projection.bson(),
        nullptr
    ));
}

cursor collection::aggregate(const model::aggregate& /* model */) const {
    return cursor(nullptr);
}

result::write collection::replaceOne(const model::replace& /* model */) {
    return result::write();
}

result::write collection::updateMany(const model::update& /* model */) {
    return result::write();
}
result::write collection::removeMany(const model::remove& /* model */) {
    return result::write();
}

result::write collection::updateOne(const model::update& /* model */) {
    return result::write();
}
result::write collection::removeOne(const model::remove& /* model */) {
    return result::write();
}

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

bson::document::value collection::explain(const model::explain& /*model*/)
    const {
    return bson::document::value((const std::uint8_t*)nullptr, 0);
}

result::distinct collection::distinct(const model::distinct& /* model */)
    const {
    return result::distinct();
}
std::int64_t collection::count(const model::count& /* model */) const { return 0; }

void collection::drop() {
    bson_error_t error;

    if (libmongoc::collection_drop(_collection, &error)) {
        /* TODO handle errors */
    }
}

} // namespace driver
} // namespace mongo

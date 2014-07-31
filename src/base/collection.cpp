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

#include <cstdint>

#include "mongoc.h"
#include "bson.h"
#include "base/collection.h"
#include "base/client.h"
#include "results/write.h"
#include "results/distinct.h"
#include "models/find.h"

namespace mongo {
namespace driver {

    Collection::Collection( Client* client, Database* database, std::string name) :
        _client(client), _name(name) {
        _collection = mongoc_client_get_collection(_client->_client, database->_name.c_str(), name.c_str());
    }

    Collection::Collection(Collection&& rhs) {
        _database = rhs._database;
        _client = rhs._client;
        _collection = rhs._collection;
        _name = std::move(rhs._name);
    }

    Collection& Collection::operator=(Collection&& rhs) {
        _database = rhs._database;
        _client = rhs._client;
        _collection = rhs._collection;
        _name = std::move(rhs._name);
        return *this;
    }

    Collection::~Collection() {
        mongoc_collection_destroy(_collection);
    }

    Cursor Collection::find(const FindModel& model) const {
        bson_t query;
        
        bson_init_static(&query, model.filter().getBuf(), model.filter().getLen());
        return Cursor(mongoc_collection_find(
            _collection,
            (mongoc_query_flags_t)model.cursor_flags().value_or(0),
            model.skip().value_or(0),
            model.limit().value_or(0),
            model.batch_size().value_or(0),
            &query,
            NULL,
            NULL
        ));
    }

    Cursor Collection::aggregate(const AggregateModel& /* model */) const { return Cursor(NULL); }

    Cursor Collection::end() const {
        return Cursor(NULL);
    }

    WriteResult Collection::replace(const ReplaceModel& /* model */) { return WriteResult(); }
    WriteResult Collection::insert(const InsertModel& /* model */) { return WriteResult(); }
    WriteResult Collection::update(const UpdateModel& /* model */) { return WriteResult(); }
    WriteResult Collection::remove(const RemoveModel& /* model */) { return WriteResult(); }

    bson::Document Collection::find_one_and_replace(const FindAndReplaceModel& /* model */) { return bson::Document(); }
    bson::Document Collection::find_one_and_update(const FindAndUpdateModel& /* model */) { return bson::Document(); }
    bson::Document Collection::find_one_and_remove(const FindAndRemoveModel& /* model */) { return bson::Document(); }

    bson::Document Collection::explain(const ExplainModel& /*model*/) const { return bson::Document(); }

    DistinctResult Collection::distinct(const DistinctModel& /* model */) const { return DistinctResult(); }
    int64_t Collection::count(const CountModel& /* model */) const { return 0; }

} // namespace driver
} // namespace mongo

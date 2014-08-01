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
#include "models/insert.h"
#include "models/insert_request.h"
#include "util/libbson.h"

namespace mongo {
namespace driver {
    using namespace bson::libbson;

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

        return Cursor(mongoc_collection_find(
            _collection,
            (mongoc_query_flags_t)model.cursor_flags().value_or(0),
            model.skip().value_or(0),
            model.limit().value_or(0),
            model.batch_size().value_or(0),
            filter.bson(),
            projection.bson(),
            NULL
        ));
    }

    Cursor Collection::aggregate(const AggregateModel& /* model */) const { return Cursor(NULL); }

    WriteResult Collection::replace(const ReplaceModel& /* model */) { return WriteResult(); }

    WriteResult Collection::insert(const InsertModel& model) { 
        BulkOperationBuilder op(this, false);
        InsertRequest req(model);
        op.add(&req);

        return op.execute();
    }

    WriteResult Collection::update(const UpdateModel& /* model */) { return WriteResult(); }
    WriteResult Collection::remove(const RemoveModel& /* model */) { return WriteResult(); }

    bson::Document::Value Collection::find_one_and_replace(const FindAndReplaceModel& /* model */) { return bson::Document::Value((const uint8_t *)NULL, 0); }
    bson::Document::Value Collection::find_one_and_update(const FindAndUpdateModel& /* model */) { return bson::Document::Value((const uint8_t *)NULL, 0); }
    bson::Document::Value Collection::find_one_and_remove(const FindAndRemoveModel& /* model */) { return bson::Document::Value((const uint8_t *)NULL, 0); }

    bson::Document::Value Collection::explain(const ExplainModel& /*model*/) const { return bson::Document::Value((const uint8_t *)NULL, 0); }

    DistinctResult Collection::distinct(const DistinctModel& /* model */) const { return DistinctResult(); }
    int64_t Collection::count(const CountModel& /* model */) const { return 0; }

    void Collection::drop() {
        bson_error_t error;

        if (mongoc_collection_drop(_collection, &error)) {
            /* TODO handle errors */
        }
    }

} // namespace driver
} // namespace mongo

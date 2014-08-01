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

#pragma once

#include <cstdint>
#include <memory>
#include <set>
#include <string>

#include "mongoc.h"
#include "base/cursor.h"
#include "bson/document.h"
#include "bson/element.h"

namespace mongo {
namespace driver {

    class Client;
    class Database;
    class ExplainResult;
    class WriteResult;
    class WriteConcern;
    class ReadPreference;
    class FindModel;
    class FindAndReplaceModel;
    class FindAndUpdateModel;
    class FindAndRemoveModel;
    class UpdateModel;
    class RemoveModel;
    class InsertModel;
    class ReplaceModel;
    class AggregateModel;
    class ExplainModel;
    class DistinctModel;
    class DistinctResult;
    class CountModel;

    class Collection {

        friend class Database;

    public:
        Collection(Collection&& client);
        ~Collection();

        Collection& operator=(Collection&& client);

        Cursor find(const FindModel& model) const;
        Cursor aggregate(const AggregateModel& model) const;

        WriteResult replace(const ReplaceModel& model);
        WriteResult insert(const InsertModel& model);
        WriteResult update(const UpdateModel& model);
        WriteResult remove(const RemoveModel& model);

        bson::Document::Value find_one_and_replace(const FindAndReplaceModel& model);
        bson::Document::Value find_one_and_update(const FindAndUpdateModel& model);
        bson::Document::Value find_one_and_remove(const FindAndRemoveModel& model);

        bson::Document::Value explain(const ExplainModel& model) const;

        DistinctResult distinct(const DistinctModel& model) const;
        int64_t count(const CountModel& model) const;

        void drop();

    private:
        Collection(
            Client* client,
            Database* database,
            std::string name
        );

        Collection(const Collection& client) = delete;
        Collection& operator=(const Collection& client) = delete;

        Client* _client;
        Database* _database;
        std::string _name;
        mongoc_collection_t* _collection;
    };

} // namespace driver
} // namespace mongo

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

    class Collection {
    public:

        Collection(
            Client* client,
            Database* database,
            const std::string& name
        ) : _client(client), _database(database), _name(name) {}

        //iterator begin() const;
        //iterator end() const;

        std::unique_ptr<Cursor> find(const FindModel& model) const;
        std::unique_ptr<Cursor> aggregate(const AggregateModel& model) const;

        WriteResult replace(const ReplaceModel model);
        WriteResult insert(const InsertModel& model);
        WriteResult update(const UpdateModel& model);
        WriteResult remove(const RemoveModel& model);

        bson::Document find_and_replace(const FindAndReplaceModel& model);
        bson::Document find_and_update(const FindAndUpdateModel& model);
        bson::Document find_and_remove(const FindAndRemoveModel& model);

        ExplainResult explain() const;

        std::set<bson::Element> distinct(
            const std::string& field_name,
            const bson::Document& filter,
            const int64_t max_time_ms,
            const ReadPreference* read_preference
        ) const;

        int64_t count(
            const bson::Document& filter,
            const bson::Document& hint,
            int32_t limit,
            const int64_t max_time_ms,
            int32_t skip,
            const ReadPreference* read_preference
        ) const;

    private:
        Client* _client;
        Database* _database;
        std::string _name;
    };

} // namespace driver
} // namespace mongo

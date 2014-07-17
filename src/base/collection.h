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
    class Pipeline;
    class ExplainResult;
    class WriteResult;
    class WriteConcern;
    class ReadPreference;

    class Collection {
    public:

        Collection(
            Client* client,
            Database* database,
            const std::string& name
        ) : _client(client), _database(database), _name(name) {}

        //iterator begin() const;
        //iterator end() const;

        WriteResult insert(
            const bson::Document& document,
            const WriteConcern* write_concern
        );

        std::unique_ptr<Cursor> aggregate(
            const Pipeline& p,
            bool allow_disk_use,
            int32_t batch_size,
            bool use_cursor,
            int64_t max_time_ms,
            const ReadPreference* read_preference
        ) const;

        std::unique_ptr<Cursor> find(
            const bson::Document& filter,
            int32_t batch_size,
            int32_t cursor_flags,
            int32_t limit,
            const bson::Document& modifiers,
            const bson::Document& projection,
            int32_t skip,
            const bson::Document& sort,
            int64_t max_time_ms,
            const ReadPreference* read_preference
        ) const;

        bson::Document find_and_replace(
            const bson::Document& filter,
            const bson::Document& replacement,
            const bson::Document& projection,
            bool returnReplacement,
            const bson::Document& sort,
            bool upsert
        );

        bson::Document find_and_update(
            const bson::Document& filter,
            const bson::Document& update,
            const bson::Document& projection,
            bool returnUpdated,
            const bson::Document& sort,
            bool upsert
        );

        bson::Document find_and_remove(
            const bson::Document& filter,
            const bson::Document& projection,
            const bson::Document& sort
        );

        WriteResult replace(
            const bson::Document& filter,
            const bson::Document& replacement,
            const WriteConcern* write_concern
        );

        WriteResult update(
            const bson::Document& filter,
            const bson::Document& update,
            const WriteConcern* write_concern
        );

        WriteResult remove(
            const bson::Document& filter,
            bool multi,
            const WriteConcern* write_concern
        );

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

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
    public:

        Collection(
            Client* const client,
            Database* const database,
            const std::string& name
        ) : _client(client), _database(database), _name(name) {}

        //iterator begin() const;
        //iterator end() const;

        /**
         * Finds the documents matching the model.
         *
         * @see http://docs.mongodb.org/manual/core/read-operations-introduction/
         * @param model The arguments.
         */
        std::unique_ptr<Cursor> find(const FindModel& model) const;

        /**
         * Runs an aggregation framework pipeline.
         *
         * @see http://docs.mongodb.org/manual/reference/command/aggregate/
         * @param model The arguments.
         */
        std::unique_ptr<Cursor> aggregate(const AggregateModel& model) const;

        /**
         * Replaces a single document.
         *
         * @see http://docs.mongodb.org/manual/reference/command/update/
         * @param model The arguments.
         * @throws WriteException
         * @throws DuplicateKeyException
         */
        WriteResult replace(const ReplaceModel model);

        /**
         * Inserts the provided document. If the document is missing an identifier,
         * the driver should generate one.
         *
         * @see http://docs.mongodb.org/manual/reference/command/insert/
         * @param model The arguments.
         * @throws WriteException
         * @throws DuplicateKeyException
         */
        WriteResult insert(const InsertModel& model);

        /**
         * Updates one or more documents.
         *
         * @see http://docs.mongodb.org/manual/reference/command/update/
         * @param model The arguments.
         * @throws WriteException
         * @throws DuplicateKeyException
         */
        WriteResult update(const UpdateModel& model);

        /**
         * Removes one or more documents.
         *
         * @see http://docs.mongodb.org/manual/reference/command/delete/
         * @throws WriteException
         */
        WriteResult remove(const RemoveModel& model);

        /**
         * Finds a single document and replaces it, returning either the original or the replaced
         * document.
         *
         * @see http://docs.mongodb.org/manual/reference/command/findAndModify/
         * @param model The arguments.
         * @throws WriteException
         */
        bson::Document find_one_and_replace(const FindAndReplaceModel& model);

        /**
         * Finds a single document and updates it, returning either the original or the updated
         * document.
         *
         * @see http://docs.mongodb.org/manual/reference/command/findAndModify/
         * @param model The arguments.
         * @throws WriteException
         */
        bson::Document find_one_and_update(const FindAndUpdateModel& model);

        /**
         * Finds a single document and removes it, returning the removed document.
         *
         * @see http://docs.mongodb.org/manual/reference/command/findAndModify/
         * @param model The arguments.
         * @throws WriteException
         */
        bson::Document find_one_and_remove(const FindAndRemoveModel& model);

        /**
         * Gets a document containing information on the processing of the pipeline.
         *
         * @see http://docs.mongodb.org/manual/reference/operator/meta/explain/
         */
        bson::Document explain(const ExplainModel& model) const;

        /**
         * Finds the distinct values for a specified field across a single collection.
         *
         * @see http://docs.mongodb.org/manual/reference/command/distinct/
         * @param model The arguments.
         */
        DistinctResult distinct(const DistinctModel& model) const;

        /**
         * Gets the number of documents matching the model.
         *
         * @see http://docs.mongodb.org/manual/reference/command/count/
         * @param model The arguments.
         */
        int64_t count(const CountModel& model) const;

    private:
        Client* const _client;
        Database* const _database;
        const std::string _name;
    };

} // namespace driver
} // namespace mongo

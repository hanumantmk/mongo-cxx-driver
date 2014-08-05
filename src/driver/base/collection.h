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

#include "bson/document.h"
#include "driver/base/bulk.h"
#include "driver/base/cursor.h"
#include "driver/result/write.h"

namespace mongo {
namespace driver {

    class client;
    class database;
    class explain_result;
    class write_result;
    class write_concern;
    class read_preference;
    class find;
    class find_one_and_replace;
    class find_one_and_remove;
    class find_one_and_update;
    class update;
    class remove;
    class insert;
    class replace;
    class aggregate;
    class explain;
    class distinct;
    class count;
    class findable;

    class collection {

        friend class BulkOperationBuilder;
        friend class database;

    public:
        collection(collection&& client);
        ~collection();

        collection& operator=(collection&& client);

        Cursor find(const find& model) const;
        findable find(bson::document::view filter) const;
        Cursor aggregate(const aggregate& model) const;

        write replace(const replace& model);
        write insert(const insert& model);
        write update(const update& model);
        write remove(const remove& model);

        bson::document::Value find_one_and_replace(const find_one_and_replace& model);
        bson::document::Value find_one_and_update(const find_one_and_update& model);
        bson::document::Value find_one_and_remove(const find_one_and_remove& model);

        bson::document::Value explain(const explain& model) const;
        distinct distinct(const distinct& model) const;

/*
 *        template <class T>
 *        WriteResult bulk_write(const BulkWriteModel<T>& model) const {
 *            BulkOperationBuilder op(this, model.ordered());
 *
 *            for (auto x : model.requests()) {
 *                op.add(x);
 *            }
 *
 *            return op.execute();
 *        }
 */

        int64_t count(const count& model) const;

        void drop();

    private:
        collection(
            client* client,
            database* database,
            std::string name
        );

        collection(const collection& client) = delete;
        collection& operator=(const collection& client) = delete;

        client* _client;
        database* _database;
        std::string _name;
        mongoc_collection_t* _collection;
    };

} // namespace driver
} // namespace mongo

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

#pragma once

#include "driver/config/prelude.hpp"

#include <cstdint>
#include <string>

#include "bson/document.hpp"

#include "driver/base/cursor.hpp"
#include "driver/result/distinct.hpp"
#include "driver/result/explain.hpp"
#include "driver/result/write.hpp"
#include "driver/util/unique_ptr_void.hpp"

namespace mongo {
namespace driver {

class client;
class database;
class write_concern;
class read_preference;

namespace model {
class aggregate;
class bulk_write;
class find;
class find_one_and_replace;
class find_one_and_remove;
class find_one_and_update;
class remove;
class insert;
class replace;
class distinct;
class count;
class explain;

namespace details {
class xupdate;
}

using update = details::xupdate;
}  // namespace model

namespace result {
class write;
class explain;
class distinct;
class bulk_write;
}  // namespace result

namespace fluent {
class findable;
class aggregatable;
}  // namespace fluent

class LIBMONGOCXX_EXPORT collection {

    friend class database;

   public:
    cursor find(const model::find& model) const;
    cursor aggregate(const model::aggregate& model) const;

    result::write insert_one(const model::insert& model);
    result::write insert_many(const model::insert& model);
    result::write replace_one(const model::replace& model);
    result::write update_one(const model::update& model);
    result::write update_many(const model::update& model);
    result::write remove_one(const model::remove& model);
    result::write remove_many(const model::remove& model);

    result::bulk_write bulkwrite(const model::bulk_write);

    bson::document::value find_one_and_replace(const model::find_one_and_replace& model);
    bson::document::value find_one_and_update(const model::find_one_and_update& model);
    bson::document::value find_one_and_remove(const model::find_one_and_remove& model);

    bson::document::value explain(const model::explain& model) const;
    result::distinct distinct(const model::distinct& model) const;

    std::int64_t count(const model::count& model) const;

    void drop();

   private:
    collection(const database& database, const std::string& collection_name);

    util::unique_ptr_void _collection;
};

}  // namespace driver
}  // namespace mongo

#include "driver/config/postlude.hpp"

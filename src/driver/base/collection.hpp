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
#include <memory>
#include <string>

#include "bson/document.hpp"

#include "driver/base/cursor.hpp"
#include "driver/base/bulk_write.hpp"
#include "driver/options/bulk_write.hpp"
#include "driver/options/aggregate.hpp"
#include "driver/options/count.hpp"
#include "driver/options/distinct.hpp"
#include "driver/options/insert.hpp"
#include "driver/options/update.hpp"
#include "driver/options/delete.hpp"
#include "driver/options/find.hpp"
#include "driver/options/find_one_and_delete.hpp"
#include "driver/options/find_one_and_update.hpp"
#include "driver/options/find_one_and_replace.hpp"
#include "driver/result/delete.hpp"
#include "driver/result/insert_many.hpp"
#include "driver/result/insert_one.hpp"
#include "driver/result/replace_one.hpp"
#include "driver/result/update.hpp"
#include "driver/result/bulk_write.hpp"

#include "driver/base/read_preference.hpp"
#include "driver/base/write_concern.hpp"

namespace mongo {
namespace driver {

class client;
class database;
class write_concern;
class read_preference;
class pipeline;

namespace model {
class bulk_write;
class insert_one;
}

namespace result {
struct insert_one;
struct insert_many;
struct replace_one;
struct update;
struct delete_result;
struct bulk_write;
}  // namespace result

class LIBMONGOCXX_EXPORT collection {

    class impl;

    friend class database;

   public:
    cursor aggregate(
        const pipeline& pipeline,
        const options::aggregate& options = options::aggregate()
    );

    std::int64_t count(
        const bson::document::view& filter,
        const options::count& options = options::count()
    ) const;

    bson::document::value distinct(
        const std::string& field_name,
        const bson::document::view& filter,
        const options::distinct& options = options::distinct()
    ) const;

    cursor find(
        const bson::document::view& filter,
        const options::find& options = options::find()
    ) const;

    optional<bson::document::value> find_one(
        const bson::document::view& filter,
        const options::find& options = options::find()
    ) const;

    optional<result::insert_one> insert_one(
        const bson::document::view& document,
        const options::insert& options = options::insert()
    );

    template<class Container>
    optional<result::insert_many> insert_many(
        const Container& container,
        const options::insert& options = options::insert()
    ) {
        return insert_many(container.begin(), container.end(), options);
    }

    template<class DocumentIteratorType>
    optional<result::insert_many> insert_many(
        const DocumentIteratorType& begin,
        const DocumentIteratorType& end,
        const options::insert& = options::insert()
    ) {
        class bulk_write writes(false);
        DocumentIteratorType current(begin);

        while (current != end) {
            model::insert_one insert(*current);
            writes.append(insert);
            ++current;
        }

        return convert_to_insert_result(bulk_write(writes).value());
    }

    optional<result::replace_one> replace_one(
        const bson::document::view& filter,
        const bson::document::view& replacement,
        const options::update& options = options::update()
    );

    optional<result::update> update_one(
        const bson::document::view& filter,
        const bson::document::view& update,
        const options::update& options = options::update()
    );

    optional<result::update> update_many(
        const bson::document::view& filter,
        const bson::document::view& update,
        const options::update& options = options::update()
    );

    optional<result::delete_result> delete_one(
        const bson::document::view& filter,
        const options::delete_options& options = options::delete_options()
    );

    optional<result::delete_result> delete_many(
        const bson::document::view& filter,
        const options::delete_options& options = options::delete_options()
    );

    template<class Container>
    optional<result::bulk_write> bulk_write(
        const Container& container,
        const options::bulk_write& options = options::bulk_write()
    ) {
        return bulk_write(container.begin(), container.end(), options);
    }

    template<class WriteIteratorType>
    optional<result::bulk_write> bulk_write(
        const WriteIteratorType& begin,
        const WriteIteratorType& end,
        const options::bulk_write& options
    ) {
        class bulk_write writes(options.ordered().value_or(true));

        WriteIteratorType current(begin);

        while (current != end) {
            writes.append(*begin);
            ++current;
        }

        return bulk_write(writes);
    }

    optional<result::bulk_write> bulk_write(
        const class bulk_write& bulk_write
    );

    optional<bson::document::value> find_one_and_delete(
        const bson::document::view& filter,
        const options::find_one_and_delete& options = options::find_one_and_delete()
    );

    optional<bson::document::value> find_one_and_replace(
        const bson::document::view& filter,
        const bson::document::view& replacement,
        const options::find_one_and_replace& options = options::find_one_and_replace()
    );

    optional<bson::document::value> find_one_and_update(
        const bson::document::view& filter,
        const bson::document::view& update,
        const options::find_one_and_update& options = options::find_one_and_update()
    );

    void drop();

    void read_preference(class read_preference rp);
    const class read_preference& read_preference() const;

    void write_concern(class write_concern wc);
    const class write_concern& write_concern() const;

    collection(collection&& rhs);
    collection& operator=(collection&& rhs);
    ~collection();

   private:
    collection(const database& database, const std::string& collection_name);

    optional<result::insert_many> convert_to_insert_result(result::bulk_write) { return optional<result::insert_many>(); }

    std::unique_ptr<impl> _impl;
};

}  // namespace driver
}  // namespace mongo

#include "driver/config/postlude.hpp"

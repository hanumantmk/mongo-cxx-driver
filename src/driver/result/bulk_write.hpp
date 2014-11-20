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
#include <map>

#include "bson/types.hpp"
#include "driver/result/delete.hpp"
#include "driver/result/insert_one.hpp"
#include "driver/result/insert_many.hpp"
#include "driver/result/replace_one.hpp"
#include "driver/result/update.hpp"

namespace mongo {
namespace driver {
namespace result {

struct LIBMONGOCXX_EXPORT bulk_write {

    std::int64_t inserted_count;
    std::int64_t matched_count;
    std::int64_t modified_count;
    std::int64_t deleted_count;
    std::int64_t upserted_count;

    std::map<std::size_t, bson::document::element> inserted_ids;
    std::map<std::size_t, bson::document::element> upserted_ids;

    // TODO: better to have constructors on insert_one, etc.. take bulk write?
    explicit operator insert_one();
    explicit operator insert_many();
    explicit operator replace_one();
    explicit operator update();
    explicit operator delete_result();

}; // struct bulk_write

}  // namespace result
}  // namespace driver
}  // namespace mongo

#include "driver/config/postlude.hpp"

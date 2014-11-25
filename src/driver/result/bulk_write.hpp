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

#include "bson/document.hpp"
#include "bson/types.hpp"

#include "driver/config/prelude.hpp"

#include <cstdint>

namespace mongo {
namespace driver {

    class collection;

namespace result {

class LIBMONGOCXX_EXPORT bulk_write {

    friend class driver::collection;

   public:
    std::int64_t inserted_count() const;
    std::int64_t matched_count() const;
    std::int64_t modified_count() const;
    std::int64_t deleted_count() const;
    std::int64_t upserted_count() const;

    bson::document::view inserted_ids() const;
    bson::document::view upserted_ids() const;

   private:
    bulk_write(bson::document::value raw_response)
        : _response(std::move(raw_response))
    {}

    bson::document::view _view() const;

    bson::document::value _response;

}; // class bulk_write

}  // namespace result
}  // namespace driver
}  // namespace mongo

#include "driver/config/postlude.hpp"

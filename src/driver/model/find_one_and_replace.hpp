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

#include "bson/document.hpp"
#include "driver/util/optional.hpp"

namespace mongo {
namespace driver {
namespace model {

class LIBMONGOCXX_EXPORT find_one_and_replace {

   public:
    find_one_and_replace(bson::document::view criteria, bson::document::view replacement);

    find_one_and_replace& projection(bson::document::view projection);
    find_one_and_replace& return_replacement(bool return_replacement);
    find_one_and_replace& sort(bson::document::view ordering);
    find_one_and_replace& upsert(bool upsert);

    const bson::document::view& criteria() const;
    const bson::document::view& replacement() const;

    const optional<bson::document::view>& projection() const;
    const optional<bool>& return_replacement() const;
    const optional<bson::document::view>& sort() const;
    const optional<bool>& upsert() const;

   private:
    bson::document::view _criteria;
    bson::document::view _replacement;

    optional<bson::document::view> _projection;
    optional<bool> _return_replacement;
    optional<bson::document::view> _ordering;
    optional<bool> _upsert;
};

}  // namespace model
}  // namespace driver
}  // namespace mongo

#include "driver/config/postlude.hpp"

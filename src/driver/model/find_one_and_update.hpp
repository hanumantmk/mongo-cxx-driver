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

class LIBMONGOCXX_EXPORT find_one_and_update {

   public:
    find_one_and_update(bson::document::view criteria, bson::document::view update);

    find_one_and_update& projection(bson::document::view projection);
    find_one_and_update& return_replacement(bool return_replacement);
    find_one_and_update& sort(bson::document::view ordering);
    find_one_and_update& upsert(bool upsert);

    const bson::document::view& criteria() const;
    const bson::document::view& update() const;

    const optional<bson::document::view>& projection() const;
    const optional<bool>& return_replacement() const;
    const optional<bson::document::view>& sort() const;
    const optional<bool>& upsert() const;

   private:
    bson::document::view _criteria;
    bson::document::view _update;

    optional<bson::document::view> _projection;
    optional<bool> _return_replacement;
    optional<bson::document::view> _ordering;
    optional<bool> _upsert;
};

}  // namespace model
}  // namespace driver
}  // namespace mongo

#include "driver/config/postlude.hpp"

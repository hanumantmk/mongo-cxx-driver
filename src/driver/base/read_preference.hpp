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

#include <string>
#include <cstdint>

#include "driver/util/optional.hpp"

namespace mongo {
namespace driver {

enum class read_mode : std::uint8_t {
    k_primary = (1 << 0),
    k_secondary = (1 << 1),
    k_primary_preferred = (1 << 2) | k_primary,
    k_secondary_preferred = (1 << 2) | k_secondary,
    k_nearest = (1 << 3) | k_secondary,
};

class read_preference {
   public:
       read_preference(read_mode = read_mode::k_primary);

       read_preference& mode(read_mode mode);
       read_preference& tags(bson::document::view tags);

       read_mode mode() const;
       const optional<bson::document::view>& tags() const;

   private:
       read_mode _mode;
       optional<bson::document::view> _tags;
};

}  // namespace driver
}  // namespace mongo

#include "driver/config/postlude.hpp"

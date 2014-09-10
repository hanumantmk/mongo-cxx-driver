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
#include "driver/util/optional.hpp"
#include "driver/base/read_preference.hpp"

namespace mongo {
namespace driver {

class read_preference;

namespace model {

class LIBMONGOCXX_EXPORT count {

   public:
    count(bson::document::view criteria = bson::document::view{});

    count& criteria(bson::document::view criteria);
    count& hint(bson::document::view hint);
    count& limit(std::int32_t limit);
    count& max_time_ms(std::int64_t max_time_ms);
    count& skip(std::int32_t skip);
    count& read_preference(class read_preference rp);

    bson::document::view criteria() const;
    const optional<bson::document::view>& hint() const;
    const optional<std::int32_t>& limit() const;
    const optional<std::int64_t>& max_time_ms() const;
    const optional<std::int32_t>& skip() const;
    const optional<class read_preference>& read_preference() const;

   private:
    bson::document::view _criteria;
    optional<bson::document::view> _hint;
    optional<std::int32_t> _limit;
    optional<std::int64_t> _max_time_ms;
    optional<std::int32_t> _skip;
    optional<class read_preference> _read_preference;
};

}  // namesapce model
}  // namespace driver
}  // namespace mongo

#include "driver/config/postlude.hpp"

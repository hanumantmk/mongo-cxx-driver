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

#include "driver/base/read_preference.hpp"
#include "bson/document.hpp"
#include "driver/util/optional.hpp"

namespace mongo {
namespace driver {

class read_preference;

namespace model {

class LIBMONGOCXX_EXPORT distinct {

   public:
    distinct(std::string field_name);

    distinct& criteria(bson::document::view criteria);
    distinct& max_time_ms(std::int64_t max_time_ms);
    distinct& read_preference(class read_preference rp);

    const std::string& field_name() const;

    const optional<bson::document::view>& criteria() const;
    const optional<std::int64_t>& max_time_ms() const;
    const optional<class read_preference>& read_preference() const;

   private:
    std::string _field_name;

    optional<bson::document::view> _criteria;
    optional<std::int64_t> _max_time_ms;
    optional<class read_preference> _read_preference;
};

}  // namespace model
}  // namespace driver
}  // namespace mongo

#include "driver/config/postlude.hpp"

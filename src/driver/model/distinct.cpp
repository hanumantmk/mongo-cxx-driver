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

#include "driver/model/distinct.hpp"

namespace mongo {
namespace driver {
namespace model {

distinct::distinct(std::string field_name) : _field_name(std::move(field_name)) {}

distinct& distinct::criteria(bson::document::view criteria) {
    _criteria = std::move(criteria);
    return *this;
}

distinct& distinct::max_time_ms(std::int64_t max_time_ms) {
    _max_time_ms = std::move(max_time_ms);
    return *this;
}

distinct& distinct::read_preference(class read_preference rp) {
    _read_preference = std::move(rp);
    return *this;
}

const std::string& distinct::field_name() const { return _field_name; }

const optional<bson::document::view>& distinct::criteria() const { return _criteria; }
const optional<std::int64_t>& distinct::max_time_ms() const { return _max_time_ms; }
const optional<class read_preference>& distinct::read_preference() const { return _read_preference; }

}  // namesapce model
}  // namespace driver
}  // namespace mongo

#include "driver/config/postlude.hpp"

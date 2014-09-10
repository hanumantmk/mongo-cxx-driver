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

#include "driver/model/count.hpp"

namespace mongo {
namespace driver {
namespace model {

count::count(bson::document::view criteria) : _criteria(std::move(criteria)) {}

count& count::criteria(bson::document::view criteria) {
    _criteria = std::move(criteria);

    return *this;
}

count& count::hint(bson::document::view hint) {
    _hint = std::move(hint);

    return *this;
}

count& count::limit(std::int32_t limit) {
    _limit = limit;

    return *this;
}

count& count::max_time_ms(std::int64_t max_time_ms) {
    _max_time_ms = max_time_ms;

    return *this;
}

count& count::skip(std::int32_t skip) {
    _skip = skip;

    return *this;
}

count& count::read_preference(class read_preference rp) {
    _read_preference = std::move(rp);
    return *this;
}

bson::document::view count::criteria() const { return _criteria; }

const optional<bson::document::view>& count::hint() const { return _hint; }

const optional<std::int32_t>& count::limit() const { return _limit; }

const optional<std::int64_t>& count::max_time_ms() const { return _max_time_ms; }

const optional<std::int32_t>& count::skip() const { return _skip; }

const optional<class read_preference>& count::read_preference() const { return _read_preference; }

}  // namesapce model
}  // namespace driver
}  // namespace mongo

#include "driver/config/postlude.hpp"

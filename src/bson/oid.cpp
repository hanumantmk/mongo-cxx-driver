/**
 * Copyright 2014 MongoDB Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "bson/oid.hpp"

#include <cstring>

#include "bson/string_or_literal.hpp"
#include "bson.h"

namespace bson {

oid::oid() : _is_valid(false) {}

oid::oid(init_tag_t) : _is_valid(true) {
    bson_oid_t oid;
    bson_oid_init(&oid, NULL);

    std::memcpy(_bytes, oid.bytes, sizeof(oid.bytes));
}

oid::oid(const string_or_literal& sol) : _is_valid(bson_oid_is_valid(sol.c_str(), sol.length())) {
    if (_is_valid) {
        bson_oid_t oid;
        bson_oid_init_from_string(&oid, sol.c_str());
    }
}

string_or_literal oid::to_string() const {
    bson_oid_t oid;
    std::memcpy(&oid.bytes, _bytes, sizeof(oid.bytes));
    char str[25];

    bson_oid_to_string(&oid, str);

    return string_or_literal(str);
}

oid::operator bool() const {
    return _is_valid;
}

std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> oid::get_time() const {
    return std::chrono::system_clock::from_time_t(get_time_t());
}

std::time_t oid::get_time_t() const {
    bson_oid_t oid;
    std::memcpy(&oid.bytes, _bytes, sizeof(oid.bytes));

    return bson_oid_get_time_t(&oid);
}

int oid_compare(const oid& lhs, const oid& rhs) {
    if (! lhs._is_valid || ! rhs._is_valid) {
        if (lhs._is_valid) {
            return 1;
        } else if (rhs._is_valid) {
            return -1;
        } else {
            return 0;
        }
    }

    bson_oid_t lhs_oid;
    bson_oid_t rhs_oid;

    std::memcpy(&lhs_oid.bytes, lhs, sizeof(lhs));
    std::memcpy(&rhs_oid.bytes, rhs, sizeof(rhs));

    return bson_oid_compare(&lhs_oid, &rhs_oid);
}

bool operator<(const oid& lhs, const oid& rhs) {
    return oid_compare(lhs, rhs) < 0;
}

bool operator>(const oid& lhs, const oid& rhs) {
    return oid_compare(lhs, rhs) > 0;
}

bool operator<=(const oid& lhs, const oid& rhs) {
    return oid_compare(lhs, rhs) <= 0;
}

bool operator>=(const oid& lhs, const oid& rhs) {
    return oid_compare(lhs, rhs) >= 0;
}

bool operator==(const oid& lhs, const oid& rhs) {
    return oid_compare(lhs, rhs) == 0;
}

bool operator!=(const oid& lhs, const oid& rhs) {
    return oid_compare(lhs, rhs) != 0;
}

std::ostream& operator<<(std::ostream& out, const oid& rhs) {
    out << rhs.to_string();

    return out;
}

} // namespace bson

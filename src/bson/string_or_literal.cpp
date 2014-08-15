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

#include "bson/string_or_literal.hpp"

namespace bson {

string_or_literal::string_or_literal() : _len(0), _is_owning(false), _string("") {}

string_or_literal::string_or_literal(std::string v)
    : _len(v.length()), _is_owning(true), _string(std::move(v)) {}

string_or_literal& string_or_literal::operator=(const string_or_literal& rhs) {
    _len = rhs._len;
    _is_owning = rhs._is_owning;

    if (_is_owning) {
        _string = rhs._string;
    } else {
        _literal = rhs._literal;
    }

    return *this;
}

string_or_literal::string_or_literal(const string_or_literal& rhs) { *this = rhs; }

string_or_literal& string_or_literal::operator=(string_or_literal&& rhs) {
    if (_is_owning && !rhs._is_owning) {
        using string = std::string;

        _string.~string();
    }

    _len = rhs._len;
    _is_owning = rhs._is_owning;

    if (_is_owning) {
        _string = std::move(rhs._string);
    } else {
        _literal = rhs._literal;
    }

    rhs._is_owning = false;
    rhs._literal = "";
    rhs._len = 0;

    return *this;
}

string_or_literal::string_or_literal(string_or_literal&& rhs) : _is_owning(false) {
    *this = std::move(rhs);
}

string_or_literal::~string_or_literal() {
    if (_is_owning) {
        using string = std::string;

        _string.~string();
    }
}

std::size_t string_or_literal::length() const { return _len; }

const char* string_or_literal::c_str() const {
    if (_is_owning) {
        return _string.c_str();
    } else {
        return _literal;
    }
}

}  // namespace bson

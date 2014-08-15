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

#include "bson/util/itoa.hpp"

namespace bson {
namespace util {

itoa::itoa(uint32_t val) {
    if (val) {
        int size = sizeof(_buf) - 1;
        int i = size;

        _buf[i] = '\0';

        while (val > 0) {
            i--;
            _buf[i] = (val % 10) + '0';
            val = val / 10;
        }

        _str = _buf + i;
        _len = size - i;
    } else {
        _str = "0";
        _len = 1;
    }
}

const char* itoa::c_str() const { return _str; }

std::size_t itoa::length() const { return _len; }

}  // namespace util
}  // namespace bson

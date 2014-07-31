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

#pragma once

#include <cstdint>
#include "util/optional.h"

namespace mongo {
namespace driver {

    class ReadPreference;

    template <class Derived>
    class ReadModel {

    public:
        Derived& max_time_ms(uint64_t max_time_ms) {
            _max_time_ms = max_time_ms;
            return *this;
        }

        optional<uint64_t> max_time_ms() const {
            return _max_time_ms;
        }

        Derived& read_preference(ReadPreference* read_preference) {
            _read_preference = read_preference;
        }

        optional<ReadPreference*> read_preference() const {
            return _read_preference;
        }

    protected:
        optional<uint64_t> _max_time_ms;
        optional<ReadPreference*> _read_preference;

    };

} // namespace driver
} // namespace mongo

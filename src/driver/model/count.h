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
#include <string>

#include "bson/document.h"
#include "driver/models/read.h"

namespace mongo {
namespace driver {
namespace model {

    class count : public ReadModel<count> {

    public:
        count(const bson::Document::View& filter);

        count& filter(const bson::Document::View& filter);
        count& hint(const bson::Document::View& hint);
        count& limit(int32_t limit);
        count& max_time_ms(int64_t max_time_ms);
        count& skip(int32_t skip);

    private:
        const bson::Document::View& _filter;

        bson::Document::View& _hint;
        int32_t _limit;
        int64_t _max_time_ms;
        int32_t _skip;
    };

} // namesapce model
} // namespace driver
} // namespace mongo
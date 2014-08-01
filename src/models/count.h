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
#include "models/read.h"

namespace mongo {
namespace driver {

    class CountModel : public ReadModel<CountModel> {

    public:
        CountModel(const bson::Document::View& filter);

        CountModel& filter(const bson::Document::View& filter);
        CountModel& hint(const bson::Document::View& hint);
        CountModel& limit(int32_t limit);
        CountModel& max_time_ms(int64_t max_time_ms);
        CountModel& skip(int32_t skip);

    private:
        const bson::Document::View& _filter;

        bson::Document::View& _hint;
        int32_t _limit;
        int64_t _max_time_ms;
        int32_t _skip;
    };

} // namespace driver
} // namespace mongo

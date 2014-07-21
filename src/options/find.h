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

namespace mongo {
namespace driver {

    class ReadPreference;

    class FindModel {

        friend class QueryOperation;

    public:
        FindModel(const bson::Document& filter);

        FindModel& batch_size(int32_t batch_size);
        FindModel& cursor_flags(int32_t cursor_flags);
        FindModel& limit(int32_t limit);
        FindModel& modifiers(const bson::Document& modifiers);
        FindModel& projection(const bson::Document& projection);
        FindModel& skip(int32_t skip);
        FindModel& sort(const bson::Document& sort);
        FindModel& max_time_ms(int64_t max_time_ms);

        // TODO: breakup modifiers in spec
        FindModel& min(const bson::Document& min);
        FindModel& max(const bson::Document& max);
        FindModel& hint(const bson::Document& hint);
        FindModel& returnKey(bool return_key);
        FindModel& snapshot(bool snapshot);
        FindModel& show_disk_loc(bool show_disk_loc);
        FindModel& comment(const std::string& comment);
        FindModel& max_scan(int64_t max_scan);

        // TODO: add read preference?
        FindModel& read_preference(const ReadPreference& read_preference);

    private:
        const bson::Document& _filter;
        int32_t _batch_size;
        int32_t _cursor_flags;
        int32_t _limit;
        bson::Document& _modifiers;
        bson::Document& _projection;
        int32_t _skip;
        bson::Document& _sort;
        int64_t _max_time_ms;
    };

} // namespace driver
} // namespace mongo

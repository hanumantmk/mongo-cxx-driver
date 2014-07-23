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
#include "bson/document.h"

namespace mongo {
namespace driver {

    class Pipeline;
    class ReadPreference;

    class AggregateModel {

        friend class CommandOperation;

    public:
        AggregateModel(const Pipeline& document);
        AggregateModel& allow_disk_use(bool allow_disk_use);
        AggregateModel& batch_size(int32_t batch_size);
        AggregateModel& use_cursor(bool use_cursor);
        AggregateModel& max_time_ms(int64_t max_time_ms);
        AggregateModel& read_preference(ReadPreference* read_preference);

    private:
        const Pipeline& _pipeline;
        bool _allow_disk_use;
        int32_t _batch_size;
        bool _use_cursor;
        int64_t _max_time_ms;
        const ReadPreference* _read_preference;

    }

} // namespace driver
} // namespace mongo

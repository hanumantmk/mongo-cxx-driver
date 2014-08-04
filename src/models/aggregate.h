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
#include "models/read.h"
#include "util/optional.h"

namespace mongo {
namespace driver {

    class Pipeline;

    class AggregateModel : public ReadModel<AggregateModel> {

    public:

        AggregateModel(Pipeline pipeline);

        AggregateModel& allow_disk_use(bool allow_disk_use);
        AggregateModel& batch_size(int32_t batch_size);
        AggregateModel& max_time_ms(int64_t max_time_ms);
        AggregateModel& use_cursor(bool use_cursor);

        optional<bool> allow_disk_use() const;
        optional<int32_t> batch_size() const;
        optional<int64_t> max_time_ms() const;
        optional<bool> use_cursor() const;

    private:

        Pipeline _pipeline;
        optional<bool> _allow_disk_use;
        optional<int32_t> _batch_size;
        optional<int64_t> _max_time_ms;
        optional<bool> _use_cursor;

    };

} // namespace driver
} // namespace mongo

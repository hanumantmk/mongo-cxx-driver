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

namespace mongo {
namespace driver {

    class Pipeline;

    class AggregateModel : public ReadModel<AggregateModel> {

    public:

        AggregateModel(const Pipeline& pipeline);

        /**
         * Enables writing to temporary files. When set to true, aggregation stages
         * can write data to the _tmp subdirectory in the dbPath directory. The
         * default is false.
         *
         * @see http://docs.mongodb.org/manual/reference/command/aggregate/
         */
        AggregateModel& allow_disk_use(bool allow_disk_use);

        /**
         * The number of documents to return per batch.
         *
         * @see http://docs.mongodb.org/manual/reference/command/aggregate/
         */
        AggregateModel& batch_size(int32_t batch_size);

        /**
         * The maximum amount of time to allow the query to run.
         *
         * @see http://docs.mongodb.org/manual/reference/command/aggregate/
         */
        AggregateModel& max_time_ms(int64_t max_time_ms);

        /**
         * Indicates if the results should be provided as a cursor. The default is false.
         *
         * @see http://docs.mongodb.org/manual/reference/command/aggregate/
         */
        AggregateModel& use_cursor(bool use_cursor);

    private:

        const Pipeline& _pipeline;
        bool _allow_disk_use;
        int32_t _batch_size;
        int64_t _max_time_ms;
        bool _use_cursor;

    };

} // namespace driver
} // namespace mongo

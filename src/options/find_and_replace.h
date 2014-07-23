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

#include "bson/document.h"

namespace mongo {
namespace driver {

    class WriteConcern;

    class FindAndReplaceModel {

        friend class CommandOperation;

    public:
        FindAndReplaceModel(
            const bson::Document& filter,
            const bson::Document& replacement
        );

        FindAndReplaceModel& projection(const bson::Document& projection);
        FindAndReplaceModel& return_replacement(bool multi);
        FindAndReplaceModel& sort(const bson::Document& sort);
        FindAndReplaceModel& upsert(bool upsert);
        FindAndReplaceModel& write_concern(const WriteConcern& write_concern);

    private:
        const bson::Document& _filter;
        const bson::Document& _replacement;
        const bson::Document& _projection;
        bool _return_replacement;
        const bson::Document& _sort;
        bool _upsert;
        WriteConcern& _write_concern;

    }

} // namespace driver
} // namespace mongo

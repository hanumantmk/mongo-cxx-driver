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
#include "models/write.h"

namespace mongo {
namespace driver {

    class FindAndUpdateModel : public WriteModel<FindAndUpdateModel> {

    public:
        FindAndUpdateModel(
            const bson::Document::View& filter,
            const bson::Document::View& update
        );

        FindAndUpdateModel& projection(const bson::Document::View& projection);
        FindAndUpdateModel& return_replacement(bool multi);
        FindAndUpdateModel& sort(const bson::Document::View& ordering);
        FindAndUpdateModel& upsert(bool upsert);

    private:
        const bson::Document::View& _filter;
        const bson::Document::View& _update;

        bson::Document::View& _projection;
        bool _return_replacement;
        bson::Document::View& _ordering;
        bool _upsert;

    };

} // namespace driver
} // namespace mongo

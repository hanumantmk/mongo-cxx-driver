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
#include "driver/model/write.h"

namespace mongo {
namespace driver {
namespace model {

    class find_one_and_remove : public write<find_one_and_remove> {

    public:
        find_one_and_remove(const bson::Document::View& filter);

        find_one_and_remove& projection(const bson::Document::View& projection);
        find_one_and_remove& sort(const bson::Document::View& ordering);

    private:
        const bson::Document::View& _filter;

        bson::Document::View& _projection;
        bson::Document::View& _ordering;

    };

} // namespace model
} // namespace driver
} // namespace mongo
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

    class find_one_and_replace : public write<find_one_and_replace> {

    public:
        find_one_and_replace(
            const bson::Document::View& filter,
            const bson::Document::View& replacement
        );

        find_one_and_replace& projection(const bson::Document::View& projection);
        find_one_and_replace& return_replacement(bool multi);
        find_one_and_replace& sort(const bson::Document::View& ordering);
        find_one_and_replace& upsert(bool upsert);

    private:
        const bson::Document::View& _filter;
        const bson::Document::View& _replacement;

        bson::Document::View& _projection;
        bool _return_replacement;
        bson::Document::View& _ordering;
        bool _upsert;

    };

} // namespace model
} // namespace driver
} // namespace mongo

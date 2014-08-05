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

#include "bson/document.hpp"
#include "driver/model/write.hpp"

namespace mongo {
namespace driver {
namespace model {

class find_one_and_update : public write<find_one_and_update> {

   public:
    find_one_and_update(const bson::document::view& filter,
                        const bson::document::view& update);

    find_one_and_update& projection(const bson::document::view& projection);
    find_one_and_update& return_replacement(bool multi);
    find_one_and_update& sort(const bson::document::view& ordering);
    find_one_and_update& upsert(bool upsert);

   private:
    const bson::document::view& _filter;
    const bson::document::view& _update;

    bson::document::view& _projection;
    bool _return_replacement;
    bson::document::view& _ordering;
    bool _upsert;
};

}  // namespace model
}  // namespace driver
}  // namespace mongo

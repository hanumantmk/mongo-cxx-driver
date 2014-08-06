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
#include <vector>

#include "bson/document.hpp"

#include "driver/model/find.hpp"
#include "driver/result/explain.hpp"

namespace mongo {
namespace driver {
namespace fluent {

class findable {

    friend class collection;

   public:
    findable& add_query_flag(const bson::document::view& group);
    findable& add_query_modifier(const std::string& name /*, bson value*/ );
    findable& batch_size(int32_t batch_size);
    findable& comment(const std::string& comment);
    findable& limit(int32_t limit);
    findable& max_time_ms(int64_t max_time_ms);
    findable& project(const bson::document::view& projection);
    findable& skip(int32_t skip);
    findable& sort(const bson::document::view& ordering);

    int64_t count();
    result::explain explain();

   private:
    findable(const bson::document::view& filter);
    model::find model;

};

} // namespace fluent
} // namespace driver
} // namespace mongo

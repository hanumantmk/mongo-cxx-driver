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

#include "driver/config/header_prelude.hpp"


#include <cstdint>

#include "bson/document.hpp"

namespace mongo {
namespace driver {
namespace model {

class MONGOCXX_EXPORT query {

    query& sort(const bson::document::view& ordering);
    bson::document::view sort() const;

    query& limit(std::int32_t limit);
    std::int32_t limit() const;

    query& skip(std::int32_t limit);
    std::int32_t skip() const;
};

}  // namespace model
}  // namespace driver
}  // namespace mongo

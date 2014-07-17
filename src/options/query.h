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

    class QueryOptions {

        QueryOptions& sort(const bson::Document& ordering);
        bson::Document sort() const;

        QueryOptions& limit(int32_t limit);
        int32_t limit() const;

        QueryOptions& skip(int32_t limit);
        int32_t skip() const;

    };

} // namespace driver
} // namespace mongo

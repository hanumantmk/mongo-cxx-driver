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

#include "bson/document.h"

namespace mongo {
namespace driver {

    class ExplainResult;

    class Pipeline {
    public:
        Pipeline& geoNear(/*something*/);
        Pipeline& group(const bson::Document& group);
        Pipeline& limit(int32_t limit);
        Pipeline& match(const bson::Document& filter);
        Pipeline& out(const std::string& collection_name);
        Pipeline& project(const bson::Document& projection);
        Pipeline& redact(const bson::Document& restrictions);
        Pipeline& skip(int32_t skip);
        Pipeline& sort(const bson::Document& sort);
        Pipeline& unwind(const std::string& field_name);

    private:
        std::vector<bson::Document> _pipeline;

    };

} // namespace driver
} // namespace mongo

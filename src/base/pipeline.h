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
        Pipeline& group(const bson::Document::View& group);
        Pipeline& limit(int32_t limit);
        Pipeline& match(const bson::Document::View& filter);
        Pipeline& out(std::string collection_name);
        Pipeline& project(const bson::Document::View& projection);
        Pipeline& redact(const bson::Document::View& restrictions);
        Pipeline& skip(int32_t skip);
        Pipeline& sort(const bson::Document::View& sort);
        Pipeline& unwind(std::string field_name);

        std::vector<ViewOrValue>& pipeline() const;

    private:
        std::vector<ViewOrValue> _pipeline;

    };

} // namespace driver
} // namespace mongo

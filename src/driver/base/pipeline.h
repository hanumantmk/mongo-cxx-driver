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

    class explain_result;

    class pipeline {
    public:
        pipeline& geoNear(/*something*/);
        pipeline& group(const bson::Document::View& group);
        pipeline& limit(int32_t limit);
        pipeline& match(const bson::Document::View& filter);
        pipeline& out(std::string collection_name);
        pipeline& project(const bson::Document::View& projection);
        pipeline& redact(const bson::Document::View& restrictions);
        pipeline& skip(int32_t skip);
        pipeline& sort(const bson::Document::View& sort);
        pipeline& unwind(std::string field_name);

        bson::Document::View operator[](int index) const;

    private:
        std::vector<bson::Document::View> _pipeline;

    };

} // namespace driver
} // namespace mongo

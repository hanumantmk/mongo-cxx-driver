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
#include <memory>
#include <set>
#include "base/cursor.h"
#include "bson/document.h"
#include "bson/element.h"

namespace mongo {
namespace driver {

    class Pipeline;
    class ExplainResult;
    class WriteResult;

    class Collection {
        WriteResult insert(const bson::Document& document);
        std::unique_ptr<Cursor> aggregate(const Pipeline& p);
        std::unique_ptr<Cursor> find(const bson::Document& filter);

        // This is dumb -- everything else takes a model why shouldn't these
        bson::Document find_one_and_replace();
        bson::Document find_one_and_update();
        bson::Document find_one_and_remove();

        // Why not just replace
        WriteResult replace_one(
            const bson::Document& filter,
            const bson::Document& replacement
        );

        WriteResult update(
            const bson::Document& filter,
            const bson::Document& update
        );

        WriteResult remove(
            const bson::Document& filter
        );

        ExplainResult explain();
        std::set<bson::Element> distinct(const bson::Document& d);
        uint64_t count();
    };

} // namespace driver
} // namespace mongo

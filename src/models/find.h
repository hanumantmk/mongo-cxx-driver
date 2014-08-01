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

#include "bson/document.h"
#include "models/read.h"
#include "util/optional.h"

namespace mongo {
namespace driver {

    enum class QueryFlags {
        TAILABLE,
        OPLOG_REPLAY,
        NO_CURSOR_TIMEOUT,
        AWAIT_DATA,
        EXHAUST,
        PARTIAL
    };

    class FindModel : public ReadModel<FindModel> {

    public:
        FindModel(const bson::Document::View& filter);

        FindModel& batch_size(int32_t batch_size);
        FindModel& cursor_flags(int32_t cursor_flags);
        FindModel& limit(int32_t limit);
        FindModel& modifiers(const bson::Document::View& modifiers);
        FindModel& projection(const bson::Document::View& projection);
        FindModel& skip(int32_t skip);
        FindModel& sort(const bson::Document::View& ordering);

        const bson::Document::View& filter() const;
        optional<int32_t> batch_size() const;
        optional<int32_t> cursor_flags() const;
        optional<int32_t> limit() const;
        optional<const bson::Document::View*> modifiers() const;
        optional<const bson::Document::View*> projection() const;
        optional<int32_t> skip() const;
        optional<const bson::Document::View*> sort() const;

    private:
        const bson::Document::View& _filter;

        optional<int32_t> _batch_size;
        optional<int32_t> _cursor_flags;
        optional<int32_t> _limit;
        optional<const bson::Document::View*> _modifiers;
        optional<const bson::Document::View*> _projection;
        optional<int32_t> _skip;
        optional<const bson::Document::View*> _ordering;
    };

} // namespace driver
} // namespace mongo

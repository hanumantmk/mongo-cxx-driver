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

#include "models/find.h"

namespace mongo {
namespace driver {


    FindModel::FindModel(const bson::Document& filter) 
        : _filter(filter)
    {}

    FindModel& FindModel::batch_size(int32_t batch_size) {
        _batch_size = batch_size;
        return *this;
    }

    FindModel& FindModel::cursor_flags(int32_t cursor_flags) {
        _cursor_flags = cursor_flags;
        return *this;
    }

    FindModel& FindModel::limit(int32_t limit) {
        _limit = limit;
        return *this;
    }

    FindModel& FindModel::modifiers(const bson::Document& modifiers) {
        _modifiers = &modifiers;
        return *this;
    }

    FindModel& FindModel::projection(const bson::Document& projection) {
        _projection = &projection;
        return *this;
    }

    FindModel& FindModel::skip(int32_t skip) {
        _skip = skip;
        return *this;
    }

    FindModel& FindModel::sort(const bson::Document& ordering) {
        _ordering = &ordering;
        return *this;
    }

    const bson::Document& FindModel::filter() const {
        return _filter;
    }

    optional<int32_t> FindModel::batch_size() const {
        return _batch_size;
    }

    optional<int32_t> FindModel::cursor_flags() const {
        return _cursor_flags;
    }

    optional<int32_t> FindModel::limit() const {
        return _limit;
    }

    optional<const bson::Document*> FindModel::modifiers() const {
        return _modifiers;
    }

    optional<const bson::Document*> FindModel::projection() const {
        return _projection;
    }

    optional<int32_t> FindModel::skip() const {
        return _skip;
    }

    optional<const bson::Document*> FindModel::sort() const {
        return _ordering;
    }

} // namespace driver
} // namespace mongo

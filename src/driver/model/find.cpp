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

#include "driver/model/find.hpp"

namespace mongo {
namespace driver {
namespace model {


    find::find(bson::document::view filter)
        : _filter(filter)
    {}

    find& find::batch_size(int32_t batch_size) {
        _batch_size = batch_size;
        return *this;
    }

    find& find::cursor_flags(int32_t cursor_flags) {
        _cursor_flags = cursor_flags;
        return *this;
    }

    find& find::limit(int32_t limit) {
        _limit = limit;
        return *this;
    }

    find& find::modifiers(bson::document::view modifiers) {
        _modifiers = modifiers;
        return *this;
    }

    find& find::projection(bson::document::view projection) {
        _projection = projection;
        return *this;
    }

    find& find::skip(int32_t skip) {
        _skip = skip;
        return *this;
    }

    find& find::sort(bson::document::view ordering) {
        _ordering = ordering;
        return *this;
    }

    bson::document::view find::filter() const {
        return _filter;
    }

    optional<int32_t> find::batch_size() const {
        return _batch_size;
    }

    optional<int32_t> find::cursor_flags() const {
        return _cursor_flags;
    }

    optional<int32_t> find::limit() const {
        return _limit;
    }

    optional<bson::document::view> find::modifiers() const {
        return _modifiers;
    }

    optional<bson::document::view> find::projection() const {
        return _projection;
    }

    optional<int32_t> find::skip() const {
        return _skip;
    }

    optional<bson::document::view> find::sort() const {
        return _ordering;
    }

} // namespace model
} // namespace driver
} // namespace mongo

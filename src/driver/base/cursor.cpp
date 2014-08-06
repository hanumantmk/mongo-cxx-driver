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

#include <cstdint>

#include "mongoc.h"
#include "bson.h"

#include "driver/base/cursor.hpp"

namespace mongo {
namespace driver {

cursor::cursor(mongoc_cursor_t* cursor) : _cursor(cursor) {}

cursor::cursor(cursor&& rhs) { _cursor = rhs._cursor; }

cursor& cursor::operator=(cursor&& rhs) {
    _cursor = rhs._cursor;
    return *this;
}

cursor::~cursor() {
    if (_cursor) mongoc_cursor_destroy(_cursor);
}

cursor::iterator& cursor::iterator::operator++() {
    const bson_t* out;
    if (mongoc_cursor_next(_cursor, &out)) {
        _doc = bson::document::view(bson_get_data(out), out->len);
    } else {
        _at_end = true;
    }

    return *this;
}

cursor::iterator cursor::begin() { return iterator(_cursor); }

cursor::iterator cursor::end() { return iterator(NULL); }

cursor::iterator::iterator(mongoc_cursor_t* cursor)
    : _cursor(cursor), _at_end(!cursor) {
    if (cursor) operator++();
}

const bson::document::view& cursor::iterator::operator*() const { return _doc; }

const bson::document::view* cursor::iterator::operator->() const {
    return &_doc;
}

bool cursor::iterator::operator==(const cursor::iterator& rhs) const {
    if (_at_end == rhs._at_end) return true;
    return this == &rhs;
}

bool cursor::iterator::operator!=(const cursor::iterator& rhs) const {
    return !(*this == rhs);
}

} // namespace driver
} // namespace mongo

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

#include "base/cursor.h"

namespace mongo {
namespace driver {

    Cursor::Cursor( mongoc_cursor_t* cursor ) :
        _cursor(cursor) {
    }

    Cursor::Cursor(Cursor&& rhs) {
        _cursor = rhs._cursor;
    }

    Cursor& Cursor::operator=(Cursor&& rhs) {
        _cursor = rhs._cursor;
        return *this;
    }

    Cursor::~Cursor() {
        if (_cursor) mongoc_cursor_destroy(_cursor);
    }

    Cursor::iterator& Cursor::iterator::operator++() {
        const bson_t* out;
        if (mongoc_cursor_next(_cursor, &out)) {
            _doc.setBuf(bson_get_data(out));
            _doc.setLen(out->len);
        } else {
            _at_end = true;
        }

        return *this;
    }

    Cursor::iterator Cursor::begin() {
        return iterator(_cursor);
    }

    Cursor::iterator Cursor::end() {
        return iterator(NULL);
    }

    Cursor::iterator::iterator(mongoc_cursor_t * cursor) : _cursor(cursor), _at_end(!cursor) {
        if (cursor) operator++();
    }

    const bson::Document& Cursor::iterator::operator*() const {
        return _doc;
    }

    const bson::Document* Cursor::iterator::operator->() const {
        return &_doc;
    }

    bool Cursor::iterator::operator==(const Cursor::iterator& rhs) const {
        if (_at_end == rhs._at_end) return true;
        return this == &rhs;
    }

    bool Cursor::iterator::operator!=(const Cursor::iterator& rhs) const {
        return ! (*this == rhs);
    }

} // namespace driver
} // namespace mongo

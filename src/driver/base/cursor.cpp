// Copyright 2014 MongoDB Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <cstdint>

#include "mongoc.h"
#include "bson.h"

#include "driver/base/cursor.hpp"
#include "driver/base/private/cursor.hpp"

namespace mongo {
namespace driver {

cursor::cursor(cursor&&) = default;
cursor& cursor::operator=(cursor&&) = default;
cursor::~cursor() = default;

cursor::cursor(void* cursor_ptr) : _impl(new impl{static_cast<mongoc_cursor_t*>(cursor_ptr)}) {}

cursor::iterator& cursor::iterator::operator++() {
    const bson_t* out;
    if (mongoc_cursor_next(_cursor->_impl->cursor_t, &out)) {
        _doc = bson::document::view(bson_get_data(out), out->len);
    } else {
        _at_end = true;
    }

    return *this;
}

cursor::iterator cursor::begin() { return iterator(this); }

cursor::iterator cursor::end() { return iterator(nullptr); }

cursor::iterator::iterator(cursor* cursor) : _cursor(cursor), _at_end(!cursor) {
    if (cursor) operator++();
}

const bson::document::view& cursor::iterator::operator*() const { return _doc; }

const bson::document::view* cursor::iterator::operator->() const { return &_doc; }

bool cursor::iterator::operator==(const cursor::iterator& rhs) const {
    if (_at_end == rhs._at_end) return true;
    return this == &rhs;
}

bool cursor::iterator::operator!=(const cursor::iterator& rhs) const { return !(*this == rhs); }

}  // namespace driver
}  // namespace mongo

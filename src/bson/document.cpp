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

#include <cstdlib>
#include <cstring>

#include "bson/document.hpp"

namespace bson {

element::element() {}

element::element(const bson_iter_t& i) { _iter = i; }

bool element::operator==(const element& rhs) const {
    return (_iter.raw == rhs._iter.raw && _iter.off == rhs._iter.off);
}

type element::type() const { return bson::type(bson_iter_type(&_iter)); }

const char* element::key() const { return bson_iter_key(&_iter); }

std::tuple<const char*, ustd::int32_t> element::get_string_w_len() const {
    ustd::int32_t len;
    const char* str = bson_iter_utf8(&_iter, &len);
    return std::tuple<const char*, ustd::int32_t>(str, len);
}

std::tuple<binary_sub_type, ustd::int32_t, const ustd::int8_t*> element::get_binary()
    const {
    bson_subtype_t type;
    ustd::int32_t len;
    const ustd::int8_t* binary;

    bson_iter_binary(&_iter, &type, &len, &binary);

    return std::tuple<binary_sub_type, ustd::int32_t, const ustd::int8_t*>(
        binary_sub_type(type), len, binary);
}

const char* element::get_string() const { return bson_iter_utf8(&_iter, nullptr); }
double element::get_double() const { return bson_iter_double(&_iter); }
std::int32_t element::get_int32() const { return bson_iter_int32(&_iter); }
std::int64_t element::get_int64() const { return bson_iter_int64(&_iter); }

namespace document {

view::iterator::iterator(const bson_iter_t& i) : iter(i), is_end(false) {}
view::iterator::iterator(bool is_end) : is_end(is_end) {}

const element& view::iterator::operator*() const { return iter; }
const element* view::iterator::operator->() const { return &iter; }

view::iterator& view::iterator::operator++() {
    is_end = !bson_iter_next(&iter._iter);
    return *this;
}

bool view::iterator::operator==(const iterator& rhs) const {
    if (is_end && rhs.is_end) return true;
    if (is_end || rhs.is_end) return false;
    return iter == rhs.iter;

    return false;
}

bool view::iterator::operator!=(const iterator& rhs) const {
    return !(*this == rhs);
}

view::iterator view::begin() const {
    bson_t b;
    bson_iter_t iter;

    bson_init_static(&b, buf, len);
    bson_iter_init(&iter, &b);
    bson_iter_next(&iter);

    return iterator(iter);
}

view::iterator view::end() const { return iterator(true); }

element view::operator[](const char* key) const {
    bson_t b;
    bson_iter_t iter;

    bson_init_static(&b, buf, len);
    bson_iter_init_find(&iter, &b, key);

    return element(iter);
}

view::view(const ustd::int8_t* b, std::size_t l) : buf(b), len(l) {}
view::view() : buf(nullptr), len(0) {}

const ustd::int8_t* view::get_buf() const { return buf; }
std::size_t view::get_len() const { return len; }

value::value(const ustd::int8_t* b, std::size_t l, std::function<void(void*)> dtor)
    : view(b, l), dtor(std::move(dtor)) {}

value::value(const view& view)
    : bson::document::view((ustd::int8_t*)malloc((std::size_t)view.get_len()),
                           view.get_len()),
      dtor(free) {
    std::memcpy((void*)buf, view.get_buf(), view.get_len());
}

value::value(value&& rhs) { *this = std::move(rhs); }

value& value::operator=(value&& rhs) {
    buf = rhs.buf;
    len = rhs.len;
    dtor = rhs.dtor;

    rhs.buf = nullptr;

    return *this;
}

value::~value() {
    if (buf) {
        dtor((void*)buf);
    }
}
}

document::view element::get_document() const {
    const ustd::int8_t* buf;
    ustd::int32_t len;

    bson_iter_document(&_iter, &len, &buf);

    return document::view(buf, len);
}

document::view element::get_array() const {
    const ustd::int8_t* buf;
    ustd::int32_t len;

    bson_iter_array(&_iter, &len, &buf);

    return document::view(buf, len);
}

}  // namespace bson

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

#include "bson/document.h"

namespace bson {

thing::thing() {}

thing::thing(const bson_iter_t& i) { iter = i; }

bool thing::operator==(const thing& rhs) const {
    return (iter.raw == rhs.iter.raw && iter.off == rhs.iter.off);
}

type thing::type() const { return bson::type(bson_iter_type(&iter)); }

const char* thing::key() const { return bson_iter_key(&iter); }

const char* thing::get_string() const { return bson_iter_utf8(&iter, NULL); }

std::tuple<const char*, uint32_t> thing::get_string_w_len() const {
    uint32_t len;
    const char* str = bson_iter_utf8(&iter, &len);
    return std::tuple<const char*, uint32_t>(str, len);
}

std::tuple<binary_sub_type, uint32_t, const uint8_t*> thing::get_binary()
    const {
    bson_subtype_t type;
    uint32_t len;
    const uint8_t* binary;

    bson_iter_binary(&iter, &type, &len, &binary);

    return std::tuple<binary_sub_type, uint32_t, const uint8_t*>(
        binary_sub_type(type), len, binary);
}

double thing::get_double() const { return bson_iter_double(&iter); }
int32_t thing::get_int_32() const { return bson_iter_int32(&iter); }
int64_t thing::get_int_64() const { return bson_iter_int64(&iter); }

namespace document {

view::iterator::iterator(const bson_iter_t& i) : iter(i), is_end(false) {}
view::iterator::iterator(bool is_end) : is_end(is_end) {}

const thing& view::iterator::operator*() const { return iter; }
const thing* view::iterator::operator->() const { return &iter; }

view::iterator& view::iterator::operator++() {
    is_end = !bson_iter_next(&iter.iter);
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

thing view::operator[](const char* key) const {
    bson_t b;
    bson_iter_t iter;

    bson_init_static(&b, buf, len);
    bson_iter_init_find(&iter, &b, key);

    return thing(iter);
}

view::view(const uint8_t* b, std::size_t l) : buf(b), len(l) {}
view::view() : buf(NULL), len(0) {}

const uint8_t* view::get_buf() const { return buf; }
std::size_t view::get_len() const { return len; }

value::value(const uint8_t* b, std::size_t l, std::function<void(void *)> dtor) : view(b, l), dtor(dtor) {
}

value::value(const view& view) : view((uint8_t *)malloc((std::size_t)view.get_len()), view.get_len()), dtor(free) {
    std::memcpy((void *)buf, view.get_buf(), view.get_len());
}

value::value(value&& rhs) {
    *this = std::move(rhs);
}

value& value::operator=(value&& rhs) {
    buf = rhs.buf;
    len = rhs.len;
    dtor = rhs.dtor;

    rhs.buf = NULL;

    return *this;
}

value::~value() {
    if (buf) {
        dtor((void *)buf);
    }
}

}

document::view thing::get_document() const {
    const uint8_t* buf;
    uint32_t len;

    bson_iter_document(&iter, &len, &buf);

    return document::view(buf, len);
}

document::view thing::get_array() const {
    const uint8_t* buf;
    uint32_t len;

    bson_iter_array(&iter, &len, &buf);

    return document::view(buf, len);
}

}  // namespace bson

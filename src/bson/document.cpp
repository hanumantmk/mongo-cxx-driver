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
#include "bson/types.hpp"

namespace bson {

element::element() {}

element::element(const bson_iter_t& i) { _iter = i; }

bool element::operator==(const element& rhs) const {
    return (_iter.raw == rhs._iter.raw && _iter.off == rhs._iter.off);
}

bson::type element::type() const { return static_cast<bson::type>(bson_iter_type(&_iter)); }

string_or_literal element::key() const {
    const char* key = bson_iter_key(&_iter);

    return string_or_literal{key, std::strlen(key)};
}

types::b_binary element::get_binary() const {
    bson_subtype_t type;
    std::uint32_t len;
    const std::uint8_t* binary;

    bson_iter_binary(&_iter, &type, &len, &binary);

    return types::b_binary{static_cast<binary_sub_type>(type), len, binary};
}

types::b_utf8 element::get_string() const {
    uint32_t len;
    const char* val = bson_iter_utf8(&_iter, &len);

    return types::b_utf8{string_or_literal{val, len}};
}

types::b_double element::get_double() const { return types::b_double{bson_iter_double(&_iter)}; }
types::b_int32 element::get_int32() const { return types::b_int32{bson_iter_int32(&_iter)}; }
types::b_int64 element::get_int64() const { return types::b_int64{bson_iter_int64(&_iter)}; }
types::b_undefined element::get_undefined() const { return types::b_undefined{}; }
types::b_oid element::get_oid() const {
    const bson_oid_t* boid = bson_iter_oid(&_iter);
    oid v(reinterpret_cast<const char*>(boid->bytes), sizeof(boid->bytes));

    return types::b_oid{v};
}

types::b_bool element::get_bool() const { return types::b_bool{bson_iter_bool(&_iter)}; }
types::b_date element::get_date() const { return types::b_date{bson_iter_date_time(&_iter)}; }
types::b_null element::get_null() const { return types::b_null{}; }

types::b_regex element::get_regex() const {
    const char* options;
    const char* regex = bson_iter_regex(&_iter, &options);

    return types::b_regex{string_or_literal{regex, std::strlen(regex)}, string_or_literal{options, std::strlen(options)}};
}

types::b_dbpointer element::get_dbpointer() const {
    uint32_t collection_len;
    const char* collection;
    const bson_oid_t* boid;
    bson_iter_dbpointer(&_iter, &collection_len, &collection, &boid);

    oid v{reinterpret_cast<const char*>(boid->bytes), sizeof(boid->bytes)};

    return types::b_dbpointer{string_or_literal{collection, collection_len}, v};
}

types::b_code element::get_code() const {
    uint32_t len;
    const char* code = bson_iter_code(&_iter, &len);

    return types::b_code{string_or_literal{code, len}};
}

types::b_symbol element::get_symbol() const {
    uint32_t len;
    const char* symbol = bson_iter_symbol(&_iter, &len);

    return types::b_symbol{string_or_literal{symbol, len}};
}

types::b_codewscope element::get_codewscope() const {
    uint32_t code_len;
    const uint8_t* scope_ptr;
    uint32_t scope_len;
    const char* code = bson_iter_codewscope(&_iter, &code_len, &scope_len, &scope_ptr);
    document::view view(scope_ptr, scope_len);

    return types::b_codewscope{string_or_literal{code, code_len}, view};
}

types::b_timestamp element::get_timestamp() const {
    uint32_t timestamp;
    uint32_t increment;
    bson_iter_timestamp(&_iter, &timestamp, &increment);

    return types::b_timestamp{timestamp, increment};
}

types::b_minkey element::get_minkey() const { return types::b_minkey{}; }
types::b_maxkey element::get_maxkey() const { return types::b_maxkey{}; }

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

bool view::iterator::operator!=(const iterator& rhs) const { return !(*this == rhs); }

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

view::view(const std::uint8_t* b, std::size_t l) : buf(b), len(l) {}
view::view() : buf(nullptr), len(0) {}

const std::uint8_t* view::get_buf() const { return buf; }
std::size_t view::get_len() const { return len; }

value::value(const std::uint8_t* b, std::size_t l, std::function<void(void*)> dtor)
    : view(b, l), dtor(std::move(dtor)) {}

value::value(const view& view)
    : bson::document::view((std::uint8_t*)malloc((std::size_t)view.get_len()), view.get_len()),
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

types::b_document element::get_document() const {
    const std::uint8_t* buf;
    std::uint32_t len;

    bson_iter_document(&_iter, &len, &buf);

    return types::b_document{document::view{buf, len}};
}

types::b_array element::get_array() const {
    const std::uint8_t* buf;
    std::uint32_t len;

    bson_iter_array(&_iter, &len, &buf);

    return types::b_array{document::view{buf, len}};
}

}  // namespace bson

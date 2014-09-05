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

#include "bson.h"
#include "bson/document.hpp"
#include "bson/types.hpp"
#include "bson/json.hpp"

#define CITER             \
    bson_iter_t iter;     \
    iter.raw = _raw;      \
    iter.len = _len;      \
    iter.next_off = _off; \
    bson_iter_next(&iter)

namespace bson {

element::element() : _raw(nullptr) {}

element::element(const void* iter_) {
    const bson_iter_t* iter = reinterpret_cast<const bson_iter_t*>(iter_);

    _raw = iter->raw;
    _len = iter->len;
    _off = iter->off;
}

bool element::operator==(const element& rhs) const {
    return (_raw == rhs._raw && _off == rhs._off);
}

bson::type element::type() const {
    if (_raw == NULL) {
        return bson::type::k_eod;
    }

    CITER;
    return static_cast<bson::type>(bson_iter_type(&iter));
}

string_or_literal element::key() const {
    if (_raw == NULL) {
        return string_or_literal{""};
    }

    CITER;

    const char* key = bson_iter_key(&iter);

    return string_or_literal{key, std::strlen(key)};
}

types::b_binary element::get_binary() const {
    CITER;

    bson_subtype_t type;
    std::uint32_t len;
    const std::uint8_t* binary;

    bson_iter_binary(&iter, &type, &len, &binary);

    return types::b_binary{static_cast<binary_sub_type>(type), len, binary};
}

types::b_eod element::get_eod() const {
    return types::b_eod{};
}

types::b_utf8 element::get_utf8() const {
    CITER;

    uint32_t len;
    const char* val = bson_iter_utf8(&iter, &len);

    return types::b_utf8{string_or_literal{val, len}};
}

types::b_double element::get_double() const {
    CITER;
    return types::b_double{bson_iter_double(&iter)};
}
types::b_int32 element::get_int32() const {
    CITER;
    return types::b_int32{bson_iter_int32(&iter)};
}
types::b_int64 element::get_int64() const {
    CITER;
    return types::b_int64{bson_iter_int64(&iter)};
}
types::b_undefined element::get_undefined() const {
    return types::b_undefined{};
}
types::b_oid element::get_oid() const {
    CITER;

    const bson_oid_t* boid = bson_iter_oid(&iter);
    oid v(reinterpret_cast<const char*>(boid->bytes), sizeof(boid->bytes));

    return types::b_oid{v};
}

types::b_bool element::get_bool() const {
    CITER;
    return types::b_bool{bson_iter_bool(&iter)};
}
types::b_date element::get_date() const {
    CITER;
    return types::b_date{bson_iter_date_time(&iter)};
}
types::b_null element::get_null() const {
    return types::b_null{};
}

types::b_regex element::get_regex() const {
    CITER;

    const char* options;
    const char* regex = bson_iter_regex(&iter, &options);

    return types::b_regex{string_or_literal{regex, std::strlen(regex)},
                          string_or_literal{options, std::strlen(options)}};
}

types::b_dbpointer element::get_dbpointer() const {
    CITER;

    uint32_t collection_len;
    const char* collection;
    const bson_oid_t* boid;
    bson_iter_dbpointer(&iter, &collection_len, &collection, &boid);

    oid v{reinterpret_cast<const char*>(boid->bytes), sizeof(boid->bytes)};

    return types::b_dbpointer{string_or_literal{collection, collection_len}, v};
}

types::b_code element::get_code() const {
    CITER;

    uint32_t len;
    const char* code = bson_iter_code(&iter, &len);

    return types::b_code{string_or_literal{code, len}};
}

types::b_symbol element::get_symbol() const {
    CITER;

    uint32_t len;
    const char* symbol = bson_iter_symbol(&iter, &len);

    return types::b_symbol{string_or_literal{symbol, len}};
}

types::b_codewscope element::get_codewscope() const {
    CITER;

    uint32_t code_len;
    const uint8_t* scope_ptr;
    uint32_t scope_len;
    const char* code = bson_iter_codewscope(&iter, &code_len, &scope_len, &scope_ptr);
    document::view view(scope_ptr, scope_len);

    return types::b_codewscope{string_or_literal{code, code_len}, view};
}

types::b_timestamp element::get_timestamp() const {
    CITER;

    uint32_t timestamp;
    uint32_t increment;
    bson_iter_timestamp(&iter, &timestamp, &increment);

    return types::b_timestamp{timestamp, increment};
}

types::b_minkey element::get_minkey() const {
    return types::b_minkey{};
}
types::b_maxkey element::get_maxkey() const {
    return types::b_maxkey{};
}

namespace document {

view::iterator::iterator(const void* i) : iter(i), is_end(false) {}
view::iterator::iterator(bool is_end) : is_end(is_end) {}

const element& view::iterator::operator*() const { return iter; }
const element* view::iterator::operator->() const { return &iter; }

view::iterator& view::iterator::operator++() {
    bson_iter_t i;
    i.raw = iter._raw;
    i.len = iter._len;
    i.next_off = iter._off;
    bson_iter_next(&i);

    is_end = !bson_iter_next(&i);

    iter._raw = i.raw;
    iter._len = i.len;
    iter._off = i.off;

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

    return iterator(&iter);
}

view::iterator view::end() const { return iterator(true); }

element view::operator[](const string_or_literal& key) const {
    bson_t b;
    bson_iter_t iter;

    bson_init_static(&b, buf, len);

    if (bson_iter_init_find(&iter, &b, key.c_str())) {
        return element(reinterpret_cast<const void*>(&iter));
    } else {
        return element{};
    }
}

view::view(const std::uint8_t* b, std::size_t l) : buf(b), len(l) {}

static uint8_t kDefaultView[5] = {5, 0, 0, 0, 0};

view::view() : buf(kDefaultView), len(5) {}

const std::uint8_t* view::get_buf() const { return buf; }
std::size_t view::get_len() const { return len; }

value::value(const std::uint8_t* b, std::size_t l, void (*dtor)(void*))
    : _buf((void*)b, dtor), _len(l) {}

value::value(const document::view& view)
    : _buf(malloc((std::size_t)view.get_len()), free), _len(view.get_len()) {
    std::memcpy(_buf.get(), view.get_buf(), view.get_len());
}

document::view value::view() const {
    return document::view{(uint8_t*)_buf.get(), _len};
}

value::operator document::view() const { return view(); }

view_or_value::view_or_value(bson::document::view view) : _is_view(true), _view(std::move(view)) {}
view_or_value::view_or_value(bson::document::value value)
    : _is_view(false), _value(std::move(value)) {}

view_or_value::view_or_value(view_or_value&& rhs) : _is_view(true) { *this = std::move(rhs); }

view_or_value& view_or_value::operator=(view_or_value&& rhs) {
    if (!_is_view) {
        rhs._value.~value();
    }

    if (_is_view) {
        _view = std::move(rhs._view);
    } else {
        _value = std::move(rhs._value);
    }

    _is_view = rhs._is_view;

    rhs._is_view = true;

    return *this;
}

view_or_value::~view_or_value() {
    if (!_is_view) {
        _value.~value();
    }
}

document::view view_or_value::view() const {
    if (_is_view) {
        return _view;
    } else {
        return _value.view();
    }
}

view_or_value::operator document::view() const { return view(); }

std::ostream& operator<<(std::ostream& out, const bson::document::view& view) {
    json_visitor v(out, false, 0);
    v.visit_value(types::b_document{view});

    return out;
}

}  // namespace document

types::b_document element::get_document() const {
    CITER;

    const std::uint8_t* buf;
    std::uint32_t len;

    bson_iter_document(&iter, &len, &buf);

    return types::b_document{document::view{buf, len}};
}

types::b_array element::get_array() const {
    CITER;

    const std::uint8_t* buf;
    std::uint32_t len;

    bson_iter_array(&iter, &len, &buf);

    return types::b_array{document::view{buf, len}};
}

std::ostream& operator<<(std::ostream& out, const element& element) {
    json_visitor v(out, false, 0);

    switch ((int)element.type()) {
#define MONGOCXX_ENUM(name, val)             \
    case val:                                \
        v.visit_key(element.key());          \
        v.visit_value(element.get_##name()); \
        break;
#include "bson/enums/type.hpp"
#undef MONGOCXX_ENUM
    }

    return out;
}

}  // namespace bson

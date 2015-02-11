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

#include <cstdlib>
#include <cstring>

#include <bson.h>

#include <bsoncxx/document/element.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/types.hpp>
#include <bsoncxx/types/value.hpp>

#define CITER               \
    bson_iter_t iter;       \
    iter.raw = raw;         \
    iter.len = length;      \
    iter.next_off = offset; \
    bson_iter_next(&iter)

#define BSONCXX_TYPE_CHECK(name) \
    do { \
        if (type() != bsoncxx::type::name) { \
            throw std::runtime_error("type is not " #name); \
        } \
    } while (0)

namespace bsoncxx {
BSONCXX_INLINE_NAMESPACE_BEGIN
namespace document {

element::element() : raw(nullptr), length(0), offset(0) {
}

element::element(const std::uint8_t* raw, std::uint32_t length, std::uint32_t offset)
    : raw(raw), length(length), offset(offset) {
}

bsoncxx::type element::type() const {
    if (raw == nullptr) {
        throw std::runtime_error("unset element");
    }

    CITER;
    return static_cast<bsoncxx::type>(bson_iter_type(&iter));
}

string_or_literal element::key() const {
    if (raw == nullptr) {
        throw std::runtime_error("unset element");
    }

    CITER;

    const char* key = bson_iter_key(&iter);

    return string_or_literal{key, std::strlen(key)};
}

types::b_binary element::get_binary() const {
    BSONCXX_TYPE_CHECK(k_binary);

    CITER;

    bson_subtype_t type;
    std::uint32_t len;
    const std::uint8_t* binary;

    bson_iter_binary(&iter, &type, &len, &binary);

    return types::b_binary{static_cast<binary_sub_type>(type), len, binary};
}

types::b_utf8 element::get_utf8() const {
    BSONCXX_TYPE_CHECK(k_utf8);

    CITER;

    uint32_t len;
    const char* val = bson_iter_utf8(&iter, &len);

    return types::b_utf8{string_or_literal{val, len}};
}

types::b_double element::get_double() const {
    BSONCXX_TYPE_CHECK(k_double);
    CITER;
    return types::b_double{bson_iter_double(&iter)};
}
types::b_int32 element::get_int32() const {
    BSONCXX_TYPE_CHECK(k_int32);
    CITER;
    return types::b_int32{bson_iter_int32(&iter)};
}
types::b_int64 element::get_int64() const {
    BSONCXX_TYPE_CHECK(k_int64);
    CITER;
    return types::b_int64{bson_iter_int64(&iter)};
}
types::b_undefined element::get_undefined() const {
    BSONCXX_TYPE_CHECK(k_undefined);
    return types::b_undefined{};
}
types::b_oid element::get_oid() const {
    BSONCXX_TYPE_CHECK(k_oid);
    CITER;

    const bson_oid_t* boid = bson_iter_oid(&iter);
    oid v(reinterpret_cast<const char*>(boid->bytes), sizeof(boid->bytes));

    return types::b_oid{v};
}

types::b_bool element::get_bool() const {
    BSONCXX_TYPE_CHECK(k_bool);
    CITER;
    return types::b_bool{bson_iter_bool(&iter)};
}
types::b_date element::get_date() const {
    BSONCXX_TYPE_CHECK(k_date);
    CITER;
    return types::b_date{bson_iter_date_time(&iter)};
}
types::b_null element::get_null() const {
    BSONCXX_TYPE_CHECK(k_null);
    return types::b_null{};
}

types::b_regex element::get_regex() const {
    BSONCXX_TYPE_CHECK(k_regex);
    CITER;

    const char* options;
    const char* regex = bson_iter_regex(&iter, &options);

    return types::b_regex{string_or_literal{regex, std::strlen(regex)},
                          string_or_literal{options, std::strlen(options)}};
}

types::b_dbpointer element::get_dbpointer() const {
    BSONCXX_TYPE_CHECK(k_dbpointer);
    CITER;

    uint32_t collection_len;
    const char* collection;
    const bson_oid_t* boid;
    bson_iter_dbpointer(&iter, &collection_len, &collection, &boid);

    oid v{reinterpret_cast<const char*>(boid->bytes), sizeof(boid->bytes)};

    return types::b_dbpointer{string_or_literal{collection, collection_len}, v};
}

types::b_code element::get_code() const {
    BSONCXX_TYPE_CHECK(k_code);
    CITER;

    uint32_t len;
    const char* code = bson_iter_code(&iter, &len);

    return types::b_code{string_or_literal{code, len}};
}

types::b_symbol element::get_symbol() const {
    BSONCXX_TYPE_CHECK(k_symbol);
    CITER;

    uint32_t len;
    const char* symbol = bson_iter_symbol(&iter, &len);

    return types::b_symbol{string_or_literal{symbol, len}};
}

types::b_codewscope element::get_codewscope() const {
    BSONCXX_TYPE_CHECK(k_codewscope);
    CITER;

    uint32_t code_len;
    const uint8_t* scope_ptr;
    uint32_t scope_len;
    const char* code = bson_iter_codewscope(&iter, &code_len, &scope_len, &scope_ptr);
    document::view view(scope_ptr, scope_len);

    return types::b_codewscope{string_or_literal{code, code_len}, view};
}

types::b_timestamp element::get_timestamp() const {
    BSONCXX_TYPE_CHECK(k_timestamp);
    CITER;

    uint32_t timestamp;
    uint32_t increment;
    bson_iter_timestamp(&iter, &timestamp, &increment);

    return types::b_timestamp{timestamp, increment};
}

types::b_minkey element::get_minkey() const {
    BSONCXX_TYPE_CHECK(k_minkey);
    return types::b_minkey{};
}
types::b_maxkey element::get_maxkey() const {
    BSONCXX_TYPE_CHECK(k_maxkey);
    return types::b_maxkey{};
}

types::b_document element::get_document() const {
    BSONCXX_TYPE_CHECK(k_document);
    CITER;

    const std::uint8_t* buf;
    std::uint32_t len;

    bson_iter_document(&iter, &len, &buf);

    return types::b_document{document::view{buf, len}};
}

types::b_array element::get_array() const {
    BSONCXX_TYPE_CHECK(k_array);
    CITER;

    const std::uint8_t* buf;
    std::uint32_t len;

    bson_iter_array(&iter, &len, &buf);

    return types::b_array{array::view{buf, len}};
}

types::value element::get_value() const {
    switch (static_cast<int>(type())) {
#define BSONCXX_ENUM(type, val) \
        case val: \
            return types::value{get_##type()};
#include <bsoncxx/enums/type.hpp>
#undef BSONCXX_ENUM
    }

    // shouldn't be reachable
    std::abort();
}

element::operator bool() const {
   return raw != nullptr;
}

}  // namespace document
BSONCXX_INLINE_NAMESPACE_END
}  // namespace bsoncxx

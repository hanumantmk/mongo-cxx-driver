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

#pragma once

#include "driver/config/prelude.hpp"


#include "driver/config/prelude.hpp"

#include <iostream>
#include <functional>
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <tuple>

#include "bson.h"

namespace bson {

enum class type : std::uint8_t {
    k_eod = 0x00,
    k_double = 0x01,
    k_utf8 = 0x02,
    k_document = 0x03,
    k_array = 0x04,
    k_binary = 0x05,
    k_undefined = 0x06,
    k_oid = 0x07,
    k_bool = 0x08,
    k_date = 0x09,
    k_null = 0x0A,
    k_regex = 0x0B,
    k_dbpointer = 0x0C,
    k_code = 0x0D,
    k_symbol = 0x0E,
    k_codewscope = 0x0F,
    k_int32 = 0x10,
    k_timestamp = 0x11,
    k_int64 = 0x12,
    k_maxkey = 0x7F,
    k_minkey = 0xFF
};

enum class binary_sub_type : std::uint8_t {
    k_binary = 0x00,
    k_function = 0x01,
    k_binary_deprecated = 0x02,
    k_uuid_deprecated = 0x03,
    k_uuid = 0x04,
    k_md5 = 0x05,
    k_user = 0x80
};

namespace document {
class view;
};

class MONGOCXX_EXPORT element {
    friend class document::view;

   public:
    element();
    element(const bson_iter_t& i);

    bool operator==(const element& rhs) const;

    bson::type type() const;

    const char* key() const;

    std::tuple<const char*, std::uint32_t> get_string_w_len() const;

    std::tuple<binary_sub_type, std::uint32_t, const std::uint8_t*> get_binary() const;

    const char* get_string() const;
    double get_double() const;
    std::int32_t get_int32() const;
    std::int64_t get_int64() const;

    document::view get_document() const;
    document::view get_array() const;

   private:
    bson_iter_t _iter;
};

namespace document {

class MONGOCXX_EXPORT view {
   public:
    class iterator : public std::iterator<std::forward_iterator_tag, element, std::ptrdiff_t,
                                          const element*, const element&> {
       public:
        iterator(const bson_iter_t& i);

        iterator(bool is_end);

        const element& operator*() const;
        const element* operator->() const;

        iterator& operator++();

        bool operator==(const iterator& rhs) const;

        bool operator!=(const iterator& rhs) const;

       private:
        element iter;
        bool is_end;
    };

    iterator begin() const;
    iterator end() const;

    element operator[](const char* key) const;

    view(const std::uint8_t* b, std::size_t l);
    view();

    const std::uint8_t* get_buf() const;
    std::size_t get_len() const;

   public:
    friend std::ostream& operator<<(std::ostream& out, const bson::document::view& doc) {
        bson_t b;
        bson_init_static(&b, doc.get_buf(), doc.get_len());
        char* json = bson_as_json(&b, nullptr);
        out << json;
        bson_free(json);
        return out;
    }

   protected:
    const std::uint8_t* buf;
    std::size_t len;
};

class MONGOCXX_EXPORT value : public view {
   public:
    using view::iterator;

    value(const std::uint8_t* b, std::size_t l, std::function<void(void*)> dtor = free);
    value(const view& view);
    value(value&& rhs);
    value& operator=(value&& rhs);
    ~value();

   private:
    value(const value& rhs) = delete;
    value& operator=(const value& rhs) = delete;

    std::function<void(void*)> dtor;
};

class MONGOCXX_EXPORT view_or_value {
   public:
    view_or_value(bson::document::view view);
    view_or_value(bson::document::value value);

    view_or_value(view_or_value&& rhs);
    view_or_value& operator=(view_or_value&& rhs);

    ~view_or_value();

   private:
    view_or_value(const bson::document::view_or_value& view) = delete;
    view_or_value& operator=(const bson::document::view_or_value& view) = delete;

    bool _is_view;
    union {
        bson::document::view view;
        bson::document::value value;
    };
};
}

}  // namespace bson

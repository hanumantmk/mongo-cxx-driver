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

#include <iostream>
#include <functional>
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <tuple>

#include "bson.h"

namespace bson {

enum class type : unsigned char {
    _eod = 0x00,
    _double = 0x01,
    _utf8 = 0x02,
    _document = 0x03,
    _array = 0x04,
    _binary = 0x05,
    _undefined = 0x06,
    _oid = 0x07,
    _bool = 0x08,
    _date = 0x09,
    _null = 0x0A,
    _regex = 0x0B,
    _dbpointer = 0x0C,
    _code = 0x0D,
    _symbol = 0x0E,
    _codewscope = 0x0F,
    _int32 = 0x10,
    _timestamp = 0x11,
    _int64 = 0x12,
    _maxkey = 0x7F,
    _minkey = 0xFF,
};

enum class binary_sub_type : unsigned char {
    _binary = 0x00,
    _function = 0x01,
    _binary_deprecated = 0x02,
    _uuid_deprecated = 0x03,
    _uuid = 0x04,
    _md5 = 0x05,
    _user = 0x80,
};

namespace document {
class view;
};

class element {
    friend class document::view;

   public:
    element();
    element(const bson_iter_t& i);

    bool operator==(const element& rhs) const;

    bson::type type() const;

    const char* key() const;

    std::tuple<const char*, uint32_t> get_string_w_len() const;

    std::tuple<binary_sub_type, uint32_t, const uint8_t*> get_binary() const;

    const char* get_string() const;
    double get_double() const;
    int32_t get_int_32() const;
    int64_t get_int_64() const;

    document::view get_document() const;
    document::view get_array() const;

   private:
    bson_iter_t _iter;
};

namespace document {

class view {
   public:
    class iterator
        : public std::iterator<std::forward_iterator_tag, element, std::ptrdiff_t,
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

    view(const uint8_t* b, std::size_t l);
    view();

    const uint8_t* get_buf() const;
    std::size_t get_len() const;

   public:
    friend std::ostream& operator<<(std::ostream& out,
                                    const bson::document::view& doc) {
        bson_t b;
        bson_init_static(&b, doc.get_buf(), doc.get_len());
        char* json = bson_as_json(&b, NULL);
        out << json;
        bson_free(json);
        return out;
    }

   protected:
    const uint8_t* buf;
    std::size_t len;
};

class value : public view {
   public:
    using view::iterator;

    value(const uint8_t* b, std::size_t l,
          std::function<void(void*)> dtor = free);
    value(const view& view);
    value(value&& rhs);
    value& operator=(value&& rhs);
    ~value();

   private:
    value(const value& rhs) = delete;
    value& operator=(const value& rhs) = delete;

    std::function<void(void*)> dtor;
};

class view_or_value {
   public:
    view_or_value(bson::document::view view);
    view_or_value(bson::document::value value);

    view_or_value(view_or_value&& rhs);
    view_or_value& operator=(view_or_value&& rhs);

    ~view_or_value();

   private:
    view_or_value(const bson::document::view_or_value& view) = delete;
    view_or_value& operator=(const bson::document::view_or_value& view) =
        delete;

    bool _is_view;
    union {
        bson::document::view view;
        bson::document::value value;
    };
};
}

}  // namespace bson

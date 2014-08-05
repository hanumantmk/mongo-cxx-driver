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

enum class type {
    EOD = 0x00,
    DOUBLE = 0x01,
    UTF8 = 0x02,
    DOCUMENT = 0x03,
    ARRAY = 0x04,
    BINARY = 0x05,
    UNDEFINED = 0x06,
    OID = 0x07,
    BOOL = 0x08,
    DATE_TIME = 0x09,
    NULL_TYPE = 0x0A,
    REGEX = 0x0B,
    DBPOINTER = 0x0C,
    CODE = 0x0D,
    SYMBOL = 0x0E,
    CODEWSCOPE = 0x0F,
    INT32 = 0x10,
    TIMESTAMP = 0x11,
    INT64 = 0x12,
    MAXKEY = 0x7F,
    MINKEY = 0xFF,
};

enum class binary_sub_type {
    BINARY = 0x00,
    FUNCTION = 0x01,
    BINARY_DEPRECATED = 0x02,
    UUID_DEPRECATED = 0x03,
    UUID = 0x04,
    MD5 = 0x05,
    USER = 0x80,
};

namespace document {
    class view;
};

class thing {
    friend class document::view;

   public:
    thing();
    thing(const bson_iter_t& i);

    bool operator==(const thing& rhs) const;

    bson::type type() const;

    const char* key() const;

    const char* get_string() const;

    std::tuple<const char*, uint32_t> get_string_w_len() const;

    std::tuple<binary_sub_type, uint32_t, const uint8_t*> get_binary() const;

    double get_double() const;
    int32_t get_int_32() const;
    int64_t get_int_64() const;

    document::view get_document() const;
    document::view get_array() const;

   private:
    bson_iter_t iter;
};

namespace document {

    class view {
       public:
        class iterator : public std::iterator<std::forward_iterator_tag, thing,
                                              std::ptrdiff_t, const thing*,
                                              const thing&> {
           public:
            iterator(const bson_iter_t& i);

            iterator(bool is_end);

            const thing& operator*() const;
            const thing* operator->() const;

            iterator& operator++();

            bool operator==(const iterator& rhs) const;

            bool operator!=(const iterator& rhs) const;

           private:
            thing iter;
            bool is_end;
        };

        iterator begin() const;
        iterator end() const;

        thing operator[](const char* key) const;

        view(const uint8_t* b, std::size_t l);
        view();

        const uint8_t* get_buf() const;
        std::size_t get_len() const;

       public:

       friend std::ostream& operator<<(std::ostream& out, const bson::document::view& doc) {
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

        value(const uint8_t* b, std::size_t l, std::function<void(void*)> dtor = free);
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
        view_or_value& operator=(const bson::document::view_or_value& view) = delete;

        bool _is_view;
        union {
            bson::document::view view;
            bson::document::value value;
        };
    };

}

}  // namespace bson

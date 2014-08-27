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

#include <iostream>
#include <functional>
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <tuple>

#include "bson.h"
#include "bson/string_or_literal.hpp"

namespace bson {

enum class type : std::uint8_t;

namespace types {
    struct b_binary;
    struct b_utf8;
    struct b_double;
    struct b_int32;
    struct b_int64;
    struct b_document;
    struct b_array;
}

namespace document {
class view;
}

class LIBMONGOCXX_EXPORT element {
    friend class document::view;

   public:
    element();
    element(const bson_iter_t& i);

    bool operator==(const element& rhs) const;

    bson::type type() const;

    string_or_literal key() const;

    types::b_binary get_binary() const;
    types::b_utf8 get_string() const;
    types::b_double get_double() const;
    types::b_int32 get_int32() const;
    types::b_int64 get_int64() const;
    types::b_document get_document() const;
    types::b_array get_array() const;

   private:
    bson_iter_t _iter;
};

namespace document {

class LIBMONGOCXX_EXPORT view {
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

class LIBMONGOCXX_EXPORT value : public view {
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

class LIBMONGOCXX_EXPORT view_or_value {
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

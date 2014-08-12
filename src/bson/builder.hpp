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

#include <type_traits>
#include <vector>

#include "bson.h"
#include "bson/document.hpp"
#include "bson/string_or_literal.hpp"
#include "bson/util/functor.hpp"

namespace bson {

class builder {

   public:
    template <class T>
    class array_ctx;
    template <class T>
    class document_ctx;
    template <class T>
    class key_ctx;

    struct open_doc_t {};
    static open_doc_t open_doc;

    struct open_array_t {};
    static open_array_t open_array;

    struct close_doc_t {};
    static close_doc_t close_doc;

    struct close_array_t {};
    static close_array_t close_array;

    struct closed_ctx {
        closed_ctx(builder*) {}
    };

    class invalid_state : public std::runtime_error {};

    class value_builder;
    typedef array_ctx<closed_ctx> array_builder;
    typedef key_ctx<closed_ctx> document_builder;

    template <class Base>
    class array_ctx {
       public:
        array_ctx(builder* builder) : _builder(builder) {}

        Base unwrap() { return Base(_builder); }

        array_ctx<array_ctx> wrap_array() { return array_ctx<array_ctx>(_builder); }
        key_ctx<array_ctx> wrap_document() { return key_ctx<array_ctx>(_builder); }

        template <class T>
        typename std::enable_if<!(util::is_functor<T, void(array_builder)>::value || util::is_functor<T, void(value_builder)>::value || std::is_same<T, close_doc_t>::value), array_ctx>::type& operator<<(
            const T& t) {
            _builder->nokey_append(t);
            return *this;
        }

        template <typename Func>
        typename std::enable_if<(util::is_functor<Func, void(array_builder)>::value || util::is_functor<Func, void(value_builder)>::value), array_ctx>::type& operator<<(
            Func func) {
            func(*this);
            return *this;
        }

        key_ctx<array_ctx> operator<<(open_doc_t) {
            _builder->nokey_append(open_doc);
            return wrap_document();
        }

        array_ctx<array_ctx> operator<<(open_array_t) {
            _builder->nokey_append(open_array);
            return wrap_array();
        }

        Base operator<<(close_array_t) {
            _builder->nokey_append(close_array);
            return unwrap();
        }

        operator array_builder() { return array_builder(_builder); }

        operator value_builder();

       private:
        builder* _builder;
    };

    template <class Base>
    class key_ctx {
       public:
        key_ctx(builder* builder) : _builder(builder) {}

        Base unwrap() { return Base(_builder); }

        document_ctx<key_ctx> operator<<(string_or_literal key) {
            return document_ctx<key_ctx>(_builder, std::move(key));
        }

        template <typename Func>
        typename std::enable_if<util::is_functor<Func, void(document_builder)>::value, key_ctx>::type& operator<<(
            Func func) {
            func(*this);
            return *this;
        }

        Base operator<<(close_doc_t) {
            _builder->nokey_append(close_doc);
            return unwrap();
        }

        operator document_builder() { return document_builder(_builder); }

       private:
        builder* _builder;
    };

    template <class Base>
    class document_ctx {
       public:
        document_ctx(builder* builder, string_or_literal key)
            : _builder(builder), _key(std::move(key)) {}

        Base unwrap() { return Base(_builder); }

        array_ctx<Base> wrap_array() { return array_ctx<Base>(_builder); }
        key_ctx<Base> wrap_document() { return key_ctx<Base>(_builder); }

        template <class T>
        typename std::enable_if<!util::is_functor<T, void(value_builder)>::value, Base>::type operator<<(
            const T& t) {
            _builder->key_append(_key, t);
            return unwrap();
        }

        template <typename Func>
        typename std::enable_if<util::is_functor<Func, void(value_builder)>::value, Base>::type operator<<(
            Func func) {
            func(*this);
            return unwrap();
        }

        key_ctx<Base> operator<<(open_doc_t) {
            _builder->key_append(_key, open_doc);
            return wrap_document();
        }

        array_ctx<Base> operator<<(open_array_t) {
            _builder->key_append(_key, open_array);
            return wrap_array();
        }

        operator value_builder();

       private:
        builder* _builder;
        string_or_literal _key;
    };

    class value_builder {
       public:
        value_builder(builder* builder) : _builder(builder), _is_array(true) {}

        value_builder(builder* builder, string_or_literal key)
            : _builder(builder), _is_array(false), _key(key) {}

        array_ctx<value_builder> wrap_array() { return array_ctx<value_builder>(_builder); }
        key_ctx<value_builder> wrap_document() { return key_ctx<value_builder>(_builder); }

        key_ctx<value_builder> operator<<(open_doc_t) {
            if (_is_array) {
                _builder->nokey_append(open_doc);
            } else {
                _builder->key_append(_key, open_doc);
            }

            return wrap_document();
        }

        array_ctx<value_builder> operator<<(open_array_t) {
            if (_is_array) {
                _builder->nokey_append(open_array);
            } else {
                _builder->key_append(_key, open_array);
            }

            return wrap_array();
        }

        template <class T>
        void operator<<(const T& t) {
            if (_is_array) {
                _builder->nokey_append(t);
            } else {
                _builder->key_append(_key, t);
            }
        }

       private:
        builder* _builder;
        bool _is_array;
        string_or_literal _key;
    };

    builder();

    builder(builder&& rhs);
    builder& operator=(builder&& rhs);

    ~builder();

    document_ctx<key_ctx<builder>> operator<<(string_or_literal rhs) {
        key_ctx<builder> ctx(this);

        return ctx << std::move(rhs);
    }

    operator document_builder() { return document_builder(this); }

    builder& key_append(const string_or_literal& key, int32_t i32);
    builder& key_append(const string_or_literal& key, open_doc_t);
    builder& key_append(const string_or_literal& key, open_array_t);

    builder& nokey_append(int32_t i32);
    builder& nokey_append(open_doc_t);
    builder& nokey_append(close_doc_t);
    builder& nokey_append(open_array_t);
    builder& nokey_append(close_array_t);

    document::view view() const;

   private:
    builder(const builder& rhs) = delete;
    builder& operator=(const builder& rhs) = delete;

    struct frame {
        frame(bool is_array) : n(0), is_array(is_array) {}

        std::size_t n;
        bool is_array;
        bson_t bson;
    };

    std::vector<frame> _stack;
};

template <class T>
builder::array_ctx<T>::operator value_builder() {
    return value_builder(_builder);
}

template <class T>
builder::document_ctx<T>::operator value_builder() {
    return value_builder(_builder, _key);
}

}  // namespace bson

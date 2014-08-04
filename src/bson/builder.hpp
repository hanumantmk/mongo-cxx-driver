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
#include "bson/util/functor.hpp"

namespace bson {

    class Builder {

    public:
        template <class T> class ArrayCtx;
        template <class T> class DocumentCtx;
        template <class T> class KeyCtx;

        struct open_doc_t {};
        static open_doc_t open_doc;

        struct open_array_t {};
        static open_array_t open_array;

        struct close_doc_t {};
        static close_doc_t close_doc;

        struct close_array_t {};
        static close_array_t close_array;

        struct ClosedCtx {
            ClosedCtx(Builder*) {}
        };

        class InvalidState : public std::runtime_error {
            
        };

        class ValueBuilder;
        typedef ArrayCtx<ClosedCtx> ArrayBuilder;
        typedef KeyCtx<ClosedCtx> DocumentBuilder;

        template <class Base>
        class ArrayCtx {
        public:
            ArrayCtx(Builder* builder) :
                _builder(builder) {}

            Base unwrap() { return Base(_builder); }

            ArrayCtx<ArrayCtx> wrapArray() { return ArrayCtx<ArrayCtx>(_builder); }
            KeyCtx<ArrayCtx> wrapDocument() { return KeyCtx<ArrayCtx>(_builder); }

            template <class T>
            typename std::enable_if<!
                (util::is_functor<T, void (ArrayBuilder)>::value ||
                 util::is_functor<T, void (ValueBuilder)>::value ||
                 std::is_same<T, close_doc_t>::value),
                ArrayCtx>::type&
            operator<<(const T& t) {
                _builder->nokey_append(t);
                return *this;
            }

            template <typename Func>
            typename std::enable_if<
                (util::is_functor<Func, void (ArrayBuilder)>::value ||
                 util::is_functor<Func, void (ValueBuilder)>::value),
                ArrayCtx>::type&
            operator<<(Func func) {
                func(*this);
                return *this;
            }

            KeyCtx<ArrayCtx> operator<<(open_doc_t) {
                _builder->nokey_append(open_doc);
                return wrapDocument();
            }

            ArrayCtx<ArrayCtx> operator<<(open_array_t) {
                _builder->nokey_append(open_array);
                return wrapArray();
            }

            Base operator<<(close_array_t) {
                _builder->nokey_append(close_array);
                return unwrap();
            }

            operator ArrayBuilder() {
                return ArrayBuilder(_builder);
            }

            operator ValueBuilder();

        private:
            Builder* _builder;
        };

        template <class Base>
        class KeyCtx {
        public:
            KeyCtx(Builder* builder) :
                _builder(builder) {}

            Base unwrap() { return Base(_builder); }

            DocumentCtx<KeyCtx> operator<<(const std::string& key) {
                return DocumentCtx<KeyCtx>(_builder, key);
            }

            template <typename Func>
            typename std::enable_if<util::is_functor<Func, void (DocumentBuilder)>::value, KeyCtx>::type&
            operator<<(Func func) {
                func(*this);
                return *this;
            }

            Base operator<<(close_doc_t) {
                _builder->nokey_append(close_doc);
                return unwrap();
            }

            operator DocumentBuilder() {
                return DocumentBuilder(_builder);
            }

        private:
            Builder* _builder;
        };

        template <class Base>
        class DocumentCtx {
        public:
            DocumentCtx(Builder* builder, std::string key) :
                _builder(builder),
                _key(std::move(key)) {}

            Base unwrap() { return Base(_builder); }

            ArrayCtx<Base> wrapArray() { return ArrayCtx<Base>(_builder); }
            KeyCtx<Base> wrapDocument() { return KeyCtx<Base>(_builder); }

            template <class T>
            typename std::enable_if<! util::is_functor<T, void (ValueBuilder)>::value, Base>::type
            operator<<(const T& t) {
                _builder->key_append(_key, t);
                return unwrap();
            }

            template <typename Func>
            typename std::enable_if<util::is_functor<Func, void (ValueBuilder)>::value, Base>::type
            operator<<(Func func) {
                func(*this);
                return unwrap();
            }

            KeyCtx<Base> operator<<(open_doc_t) {
                _builder->key_append(_key, open_doc);
                return wrapDocument();
            }

            ArrayCtx<Base> operator<<(open_array_t) {
                _builder->key_append(_key, open_array);
                return wrapArray();
            }

            operator ValueBuilder();

        private:
            Builder* _builder;
            std::string _key;
        };

        class ValueBuilder {
        public:
            ValueBuilder(Builder* builder) :
                _builder(builder),
                _is_array(true) {}

            ValueBuilder(Builder* builder, std::string key) :
                _builder(builder),
                _is_array(false),
                _key(key) {}

            ArrayCtx<ValueBuilder> wrapArray() { return ArrayCtx<ValueBuilder>(_builder); }
            KeyCtx<ValueBuilder> wrapDocument() { return KeyCtx<ValueBuilder>(_builder); }

            KeyCtx<ValueBuilder> operator<<(open_doc_t) {
                if (_is_array) {
                    _builder->nokey_append(open_doc);
                } else {
                    _builder->key_append(_key, open_doc);
                }

                return wrapDocument();
            }

            ArrayCtx<ValueBuilder> operator<<(open_array_t) {
                if (_is_array) {
                    _builder->nokey_append(open_array);
                } else {
                    _builder->key_append(_key, open_array);
                }

                return wrapArray();
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
            Builder* _builder;
            bool _is_array;
            std::string _key;
        };

        Builder();

        Builder(Builder&& rhs);
        Builder& operator=(Builder&& rhs);

        ~Builder();

        DocumentCtx<KeyCtx<Builder>> operator<<(const std::string& rhs) {
            KeyCtx<Builder> ctx(this);

            return ctx << rhs;
        }

        operator DocumentBuilder() {
            return DocumentBuilder(this);
        }

        Builder& key_append(const std::string& key, int32_t i32);
        Builder& key_append(const std::string& key, open_doc_t);
        Builder& key_append(const std::string& key, open_array_t);

        Builder& nokey_append(int32_t i32);
        Builder& nokey_append(open_doc_t);
        Builder& nokey_append(close_doc_t);
        Builder& nokey_append(open_array_t);
        Builder& nokey_append(close_array_t);

        document::view view() const;

    private:
        Builder(const Builder& rhs) = delete;
        Builder& operator=(const Builder& rhs) = delete;

        struct frame {
            frame(bool is_array) : n(0), is_array(is_array) {
            }

            std::size_t n;
            bool is_array;
            bson_t bson;
        };

        std::vector<frame> _stack;
    };

    template <class T>
    Builder::ArrayCtx<T>::operator ValueBuilder() {
        return ValueBuilder(_builder);
    }

    template <class T>
    Builder::DocumentCtx<T>::operator ValueBuilder() {
        return ValueBuilder(_builder, _key);
    }


}  // namespace bson

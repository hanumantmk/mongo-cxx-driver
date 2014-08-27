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

#include "bson/builder/concrete.hpp"
#include "bson/util/functor.hpp"

namespace bson {

template <class Base>
class builder::key_ctx {
   public:
    key_ctx(builder* builder) : _builder(builder) {}

    Base unwrap() { return Base(_builder); }

    document_ctx<key_ctx> operator<<(string_or_literal key) {
        _builder->key_append(std::move(key));
        return document_ctx<key_ctx>(_builder);
    }

    template <typename Func>
    typename std::enable_if<util::is_functor<Func, void(document_builder)>::value, key_ctx>::type& operator<<(
        Func func) {
        func(*this);
        return *this;
    }

    template <typename Func>
    typename std::enable_if<util::is_functor<Func, string_or_literal()>::value, document_ctx<key_ctx>>::type operator<<(
        Func func) {
        return (*this << func());
    }

    Base operator<<(builder_helpers::close_doc_t) {
        _builder->close_doc_append();
        return unwrap();
    }

    operator document_builder() { return document_builder(_builder); }

   private:
    builder* _builder;
};

}

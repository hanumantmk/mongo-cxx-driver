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

#pragma once

#include "bson/builder/concrete.hpp"
#include "bson/builder/closed_ctx.hpp"
#include "bson/builder/value_ctx.hpp"
#include "bson/util/functor.hpp"

namespace bson {
namespace builder {

template <class Base = closed_ctx>
class key_ctx {
   public:
    key_ctx(concrete* concrete) : _concrete(concrete) {}

    value_ctx<key_ctx> operator<<(string_or_literal key) {
        _concrete->key_append(std::move(key));
        return value_ctx<key_ctx>(_concrete);
    }

    template <typename Func>
    typename std::enable_if<util::is_functor<Func, void(key_ctx<>)>::value, key_ctx>::type& operator<<(
        Func func) {
        func(*this);
        return *this;
    }

    template <typename Func>
    typename std::enable_if<util::is_functor<Func, string_or_literal()>::value, value_ctx<key_ctx>>::type operator<<(
        Func func) {
        return (*this << func());
    }

    key_ctx operator<<(builder::helpers::concat concat) {
        _concrete->concat_append(concat);
        return *this;
    }

    Base operator<<(builder::helpers::close_doc_t) {
        _concrete->close_doc_append();
        return unwrap();
    }

    operator key_ctx<>() { return key_ctx<>(_concrete); }

   private:
    Base unwrap() { return Base(_concrete); }

    concrete* _concrete;
};

}  // namespace builder
}  // namespace bson

#include "driver/config/postlude.hpp"

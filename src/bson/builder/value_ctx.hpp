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
#include "bson/builder/array_ctx.hpp"
#include "bson/builder/document_ctx.hpp"
#include "bson/builder/key_ctx.hpp"

namespace bson {
namespace builder {

class value_ctx {
   public:
    value_ctx(concrete* concrete) : _concrete(concrete) {}

    array_ctx<value_ctx> wrap_array() { return array_ctx<value_ctx>(_concrete); }
    key_ctx<value_ctx> wrap_document() { return key_ctx<value_ctx>(_concrete); }

    key_ctx<value_ctx> operator<<(builder::helpers::open_doc_t) {
        _concrete->open_doc_append();

        return wrap_document();
    }

    array_ctx<value_ctx> operator<<(builder::helpers::open_array_t) {
        _concrete->open_array_append();

        return wrap_array();
    }

    template <class T>
    void operator<<(T&& t) {
        _concrete->value_append(std::forward<T>(t));
    }

   private:
    concrete* _concrete;
};
}
}

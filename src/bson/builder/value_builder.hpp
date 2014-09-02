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

class builder::value_builder {
   public:
    value_builder(builder* builder) : _builder(builder) {}

    array_ctx<value_builder> wrap_array() { return array_ctx<value_builder>(_builder); }
    key_ctx<value_builder> wrap_document() { return key_ctx<value_builder>(_builder); }

    key_ctx<value_builder> operator<<(builder_helpers::open_doc_t) {
        _builder->open_doc_append();

        return wrap_document();
    }

    array_ctx<value_builder> operator<<(builder_helpers::open_array_t) {
        _builder->open_array_append();

        return wrap_array();
    }

    template <class T>
    void operator<<(T&& t) {
        _builder->value_append(std::forward<T>(t));
    }

   private:
    builder* _builder;
};

}

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
    value_builder(builder* builder) : _builder(builder), _is_array(true) {}

    value_builder(builder* builder, string_or_literal key)
        : _builder(builder), _is_array(false), _key(std::move(key)) {}

    array_ctx<value_builder> wrap_array() { return array_ctx<value_builder>(_builder); }
    key_ctx<value_builder> wrap_document() { return key_ctx<value_builder>(_builder); }

    key_ctx<value_builder> operator<<(builder_helpers::open_doc_t) {
        if (_is_array) {
            _builder->nokey_append(builder_helpers::open_doc);
        } else {
            _builder->key_append(_key, builder_helpers::open_doc);
        }

        return wrap_document();
    }

    array_ctx<value_builder> operator<<(builder_helpers::open_array_t) {
        if (_is_array) {
            _builder->nokey_append(builder_helpers::open_array);
        } else {
            _builder->key_append(_key, builder_helpers::open_array);
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

}

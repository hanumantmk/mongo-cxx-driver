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

#include <memory>

#include "bson/document.hpp"
#include "bson/builder/helpers.hpp"
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

    class value_builder;
    class impl;

    struct closed_ctx {
        closed_ctx(builder*) {}
    };

    class invalid_state : public std::runtime_error {};

    builder();
    builder(builder&& rhs);
    builder& operator=(builder&& rhs);
    ~builder();

    document_ctx<key_ctx<builder>> operator<<(string_or_literal rhs);

    template <typename Func>
    typename std::enable_if<util::is_functor<Func, void(builder::key_ctx<builder::closed_ctx>)>::value, key_ctx<builder>>::type operator<<(
        Func func);

    operator key_ctx<closed_ctx>();

    builder& key_append(const string_or_literal& key, std::int32_t i32);
    builder& key_append(const string_or_literal& key, builder_helpers::open_doc_t);
    builder& key_append(const string_or_literal& key, builder_helpers::open_array_t);

    builder& nokey_append(std::int32_t i32);
    builder& nokey_append(builder_helpers::open_doc_t);
    builder& nokey_append(builder_helpers::close_doc_t);
    builder& nokey_append(builder_helpers::open_array_t);
    builder& nokey_append(builder_helpers::close_array_t);

    document::view view() const;

    void clear();

   private:

    std::unique_ptr<impl> _impl;
};

typedef builder::array_ctx<builder::closed_ctx> array_builder;
typedef builder::key_ctx<builder::closed_ctx> document_builder;
typedef builder::value_builder value_builder;

}  // namespace bson

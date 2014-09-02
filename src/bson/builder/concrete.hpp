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
#include "bson/types.hpp"
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

    builder& key_append(string_or_literal key);

    builder& open_doc_append();
    builder& open_array_append();
    builder& close_doc_append();
    builder& close_array_append();

    builder& value_append(const types::b_double& value);
    builder& value_append(const types::b_utf8& value);
    builder& value_append(const types::b_document& value);
    builder& value_append(const types::b_array& value);
    builder& value_append(const types::b_binary& value);
    builder& value_append(const types::b_undefined& value);
    builder& value_append(const types::b_oid& value);
    builder& value_append(const types::b_bool& value);
    builder& value_append(const types::b_date& value);
    builder& value_append(const types::b_null& value);
    builder& value_append(const types::b_regex& value);
    builder& value_append(const types::b_dbpointer& value);
    builder& value_append(const types::b_code& value);
    builder& value_append(const types::b_symbol& value);
    builder& value_append(const types::b_codewscope& value);
    builder& value_append(const types::b_int32& value);
    builder& value_append(const types::b_timestamp& value);
    builder& value_append(const types::b_int64& value);
    builder& value_append(const types::b_minkey& value);
    builder& value_append(const types::b_maxkey& value);

    builder& value_append(string_or_literal value);

    template <std::size_t n>
    builder& value_append(const char (&v)[n]) {
        return value_append(string_or_literal{v, n - 1});
    }

    builder& value_append(bool value);
    builder& value_append(double value);
    builder& value_append(std::int32_t value);
    builder& value_append(std::int64_t value);


    document::view view() const;
    document::value extract();

    void clear();

   private:

    std::unique_ptr<impl> _impl;
};

typedef builder::array_ctx<builder::closed_ctx> array_builder;
typedef builder::key_ctx<builder::closed_ctx> document_builder;
typedef builder::value_builder value_builder;

}  // namespace bson

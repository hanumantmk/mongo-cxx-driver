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

class LIBMONGOCXX_EXPORT builder {

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

    builder& operator<<(builder_helpers::concat concat);

    operator key_ctx<closed_ctx>();

    void key_append(string_or_literal key);

    void open_doc_append();
    void open_array_append();
    void close_doc_append();
    void close_array_append();
    void concat_append(const document::view& view);

    void value_append(const types::b_double& value);
    void value_append(const types::b_utf8& value);
    void value_append(const types::b_document& value);
    void value_append(const types::b_array& value);
    void value_append(const types::b_binary& value);
    void value_append(const types::b_undefined& value);
    void value_append(const types::b_oid& value);
    void value_append(const types::b_bool& value);
    void value_append(const types::b_date& value);
    void value_append(const types::b_null& value);
    void value_append(const types::b_regex& value);
    void value_append(const types::b_dbpointer& value);
    void value_append(const types::b_code& value);
    void value_append(const types::b_symbol& value);
    void value_append(const types::b_codewscope& value);
    void value_append(const types::b_int32& value);
    void value_append(const types::b_timestamp& value);
    void value_append(const types::b_int64& value);
    void value_append(const types::b_minkey& value);
    void value_append(const types::b_maxkey& value);

    void value_append(const element& value);

    void value_append(string_or_literal value);

    template <std::size_t n>
    void value_append(const char (&v)[n]) {
        value_append(string_or_literal{v, n - 1});
    }

    void value_append(bool value);
    void value_append(double value);
    void value_append(std::int32_t value);
    void value_append(std::int64_t value);
    void value_append(const oid& value);

    document::view view() const;
    document::value extract();

    void clear();

   private:

    std::unique_ptr<impl> _impl;
};

namespace builder_helpers {
    struct LIBMONGOCXX_EXPORT concat {
        document::view view;

        operator document::view() const {
            return view;
        }
    };
}

typedef builder::array_ctx<builder::closed_ctx> array_builder;
typedef builder::key_ctx<builder::closed_ctx> document_builder;
typedef builder::value_builder value_builder;

}  // namespace bson

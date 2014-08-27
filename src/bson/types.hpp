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

#include <chrono>
#include <ctime>

#include "bson/string_or_literal.hpp"
#include "bson/document.hpp"
#include "bson/oid.hpp"

namespace bson {

enum class type : std::uint8_t {
#define MONGOCXX_ENUM(name, val) name = val,
#include "bson/enums/type.hpp"
#undef MONGOCXX_ENUM
};

std::ostream& operator<<(std::ostream& out, type rhs);

enum class binary_sub_type : std::uint8_t {
#define MONGOCXX_ENUM(name, val) name = val,
#include "bson/enums/binary_sub_type.hpp"
#undef MONGOCXX_ENUM
};

std::ostream& operator<<(std::ostream& out, binary_sub_type rhs);

namespace types {

    struct b_double {
        static constexpr auto type_id = type::k_double;

        double value;

        operator double() {
            return value;
        }

        friend std::ostream& operator<<(std::ostream& out, const b_double& rhs) {
            out << "b_double{ value = " << rhs.value << " }";
            return out;
        }
    };

    struct b_utf8 {
        static constexpr auto type_id = type::k_utf8;

        string_or_literal value;

        template <std::size_t n>
        constexpr explicit b_utf8(const char (&v)[n])
            : value(v) {}

        explicit b_utf8(string_or_literal v) : value(std::move(v)) {}

        explicit b_utf8(std::string v) : value(std::move(v)) {}

        operator string_or_literal() {
            return value;
        }

        friend std::ostream& operator<<(std::ostream& out, const b_utf8& rhs) {
            out << "b_utf8{ value = " << rhs.value << " }";
            return out;
        }
    };
    
    struct b_document {
        static constexpr auto type_id = type::k_document;

        document::view value;

        operator document::view() {
            return value;
        }

        friend std::ostream& operator<<(std::ostream& out, const b_document& rhs) {
            out << "b_document{ value = " << rhs.value << " }";
            return out;
        }
    };

    struct b_array {
        static constexpr auto type_id = type::k_array;

        document::view value;

        operator document::view() {
            return value;
        }

        friend std::ostream& operator<<(std::ostream& out, const b_array& rhs) {
            out << "b_array{ value = " << rhs.value << " }";
            return out;
        }
    };

    struct b_binary {
        static constexpr auto type_id = type::k_binary;

        binary_sub_type sub_type;
        uint32_t size;
        const uint8_t* bytes;

        friend std::ostream& operator<<(std::ostream& out, const b_binary& rhs) {
            out << "b_binary{ size = " << rhs.size << ", sub_type = " << rhs.sub_type
                << ", bytes = " << static_cast<const void*>(rhs.bytes) << " }";
            return out;
        }
    };

    struct b_undefined {
        static constexpr auto type_id = type::k_undefined;

        friend std::ostream& operator<<(std::ostream& out, const b_undefined&) {
            out << "b_undefined{}";
            return out;
        }
    };

    struct b_oid {
        static constexpr auto type_id = type::k_oid;

        oid value;

        friend std::ostream& operator<<(std::ostream& out, const b_oid& rhs) {
            out << "b_oid{ " << rhs.value << " }";
            return out;
        }
    };

    struct b_bool {
        static constexpr auto type_id = type::k_bool;

        bool value;

        operator bool() {
            return value;
        }

        friend std::ostream& operator<<(std::ostream& out, const b_bool& rhs) {
            out << "b_bool{ " << rhs.value << " }";
            return out;
        }
    };

    struct b_date {
        static constexpr auto type_id = type::k_date;

        int64_t value;

        operator int64_t() {
            return value;
        }

        friend std::ostream& operator<<(std::ostream& out, const b_date& rhs) {
            out << "b_date{ " << std::ctime(&rhs.value) << " }";
            return out;
        }
    };

    struct b_null {
        static constexpr auto type_id = type::k_null;

        friend std::ostream& operator<<(std::ostream& out, const b_null&) {
            out << "b_null{}";
            return out;
        }
    };

    struct b_regex {
        static constexpr auto type_id = type::k_regex;

        string_or_literal regex;
        string_or_literal options;

        friend std::ostream& operator<<(std::ostream& out, const b_regex& rhs) {
            out << "b_regex{ regex = " << rhs.regex << ", options = " << rhs.options << " }";
            return out;
        }
    };

    struct b_dbpointer {
        static constexpr auto type_id = type::k_dbpointer;

        string_or_literal collection;
        oid value;

        friend std::ostream& operator<<(std::ostream& out, const b_dbpointer& rhs) {
            out << "b_dbpointer{ collection = " << rhs.collection << ", oid = " << rhs.value << " }";
            return out;
        }
    };

    struct b_code {
        static constexpr auto type_id = type::k_code;

        string_or_literal code;

        friend std::ostream& operator<<(std::ostream& out, const b_code& rhs) {
            out << "b_code{ code = " << rhs.code << " }";
            return out;
        }
    };

    struct b_symbol {
        static constexpr auto type_id = type::k_symbol;

        string_or_literal symbol;

        friend std::ostream& operator<<(std::ostream& out, const b_symbol& rhs) {
            out << "b_symbol{ symbol = " << rhs.symbol << " }";
            return out;
        }
    };

    struct b_codewscope {
        static constexpr auto type_id = type::k_codewscope;

        string_or_literal code;
        document::view scope;

        friend std::ostream& operator<<(std::ostream& out, const b_codewscope& rhs) {
            out << "b_codewscope{ code = " << rhs.code << ", scope = " << rhs.scope << " }";
            return out;
        }
    };

    struct b_int32 {
        static constexpr auto type_id = type::k_int32;

        int32_t value;

        operator int32_t() {
            return value;
        }

        friend std::ostream& operator<<(std::ostream& out, const b_int32& rhs) {
            out << "b_int32{ value = " << rhs.value << " }";
            return out;
        }
    };

    struct b_timestamp {
        static constexpr auto type_id = type::k_timestamp;

        uint32_t increment;
        uint32_t timestamp;

        friend std::ostream& operator<<(std::ostream& out, const b_timestamp& rhs) {
            out << "b_timestamp{ increment = " << rhs.increment << ", timestamp = " << rhs.timestamp
                << " }";
            return out;
        }
    };

    struct b_int64 {
        static constexpr auto type_id = type::k_int64;

        int64_t value;

        operator int64_t() {
            return value;
        }

        friend std::ostream& operator<<(std::ostream& out, const b_int64& rhs) {
            out << "b_int64{ value = " << rhs.value << " }";
            return out;
        }
    };

    struct b_minkey {
        static constexpr auto type_id = type::k_minkey;

        friend std::ostream& operator<<(std::ostream& out, const b_minkey&) {
            out << "b_minkey{}";
            return out;
        }
    };

    struct b_maxkey {
        static constexpr auto type_id = type::k_maxkey;

        friend std::ostream& operator<<(std::ostream& out, const b_maxkey&) {
            out << "b_maxkey{}";
            return out;
        }
    };

} // namespace types
} // namespace bson

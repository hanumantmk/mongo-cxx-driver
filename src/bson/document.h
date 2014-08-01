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

#include <cstddef>
#include <cstdint>
#include <iterator>
#include <tuple>
#include "bson.h"

namespace bson {

enum class Type {
    EOD = 0x00,
    DOUBLE = 0x01,
    UTF8 = 0x02,
    DOCUMENT = 0x03,
    ARRAY = 0x04,
    BINARY = 0x05,
    UNDEFINED = 0x06,
    OID = 0x07,
    BOOL = 0x08,
    DATE_TIME = 0x09,
    NULL_TYPE = 0x0A,
    REGEX = 0x0B,
    DBPOINTER = 0x0C,
    CODE = 0x0D,
    SYMBOL = 0x0E,
    CODEWSCOPE = 0x0F,
    INT32 = 0x10,
    TIMESTAMP = 0x11,
    INT64 = 0x12,
    MAXKEY = 0x7F,
    MINKEY = 0xFF,
};

enum class BinarySubtype {
    BINARY = 0x00,
    FUNCTION = 0x01,
    BINARY_DEPRECATED = 0x02,
    UUID_DEPRECATED = 0x03,
    UUID = 0x04,
    MD5 = 0x05,
    USER = 0x80,
};

class Document;

class Reference {
    friend class Document;

   public:
    Reference();
    Reference(const bson_iter_t& i);

    bool operator==(const Reference& rhs) const;

    Type type() const;

    const char* key() const;

    const char* getString() const;

    std::tuple<const char*, uint32_t> getStringWLen() const;

    std::tuple<BinarySubtype, uint32_t, const uint8_t*> getBinary() const;

    double getDouble() const;

    int32_t getInt32() const;

    int64_t getInt64() const;

    Document getDocument() const;
    Document getArray() const;

   private:
    bson_iter_t iter;
};

class Document {
   public:
    class iterator : public std::iterator<std::forward_iterator_tag, Reference,
                                          std::ptrdiff_t, const Reference*,
                                          const Reference&> {
       public:
        iterator(const bson_iter_t& i);

        iterator(bool is_end);

        const Reference& operator*() const;
        const Reference* operator->() const;

        iterator& operator++();

        bool operator==(const iterator& rhs) const;

        bool operator!=(const iterator& rhs) const;

       private:
        Reference iter;
        bool is_end;
    };

    iterator begin();

    iterator end();

    Reference operator[](const char* key) const;

    Document(const uint8_t* b, std::size_t l);
    Document();

    const uint8_t* getBuf() const;
    std::size_t getLen() const;
    void setBuf(const uint8_t* b);
    void setLen(std::size_t l);

    void print(std::ostream& out) const;

   private:
    const uint8_t* buf;
    std::size_t len;
};

std::ostream& operator<<(std::ostream& out, const Document& doc);

}  // namespace bson

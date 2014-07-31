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
        Reference() { }
        Reference(const bson_iter_t& i) {
            iter = i;
        }

        bool operator==(const Reference& rhs) const {
            return (iter.raw == rhs.iter.raw && iter.off == rhs.iter.off);
        }

        Type type() const {
            return Type(bson_iter_type(&iter));
        }

        const char* key() const {
            return bson_iter_key(&iter);
        }

        const char* getString() const {
            return bson_iter_utf8(&iter, NULL);
        }

        std::tuple<const char*, uint32_t> getStringWLen() const {
            uint32_t len;
            const char * str = bson_iter_utf8(&iter, &len);
            return std::tuple<const char *, uint32_t>(str, len);
        }

        std::tuple<BinarySubtype, uint32_t, const uint8_t *> getBinary() const {
            bson_subtype_t type;
            uint32_t len;
            const uint8_t* binary;

            bson_iter_binary(&iter, &type, &len, &binary);

            return std::tuple<BinarySubtype, uint32_t, const uint8_t *>(BinarySubtype(type), len, binary);
        }

        double getDouble() const {
            return bson_iter_double(&iter);
        }

        int32_t getInt32() const {
            return bson_iter_int32(&iter);
        }

        int64_t getInt64() const {
            return bson_iter_int64(&iter);
        }

        Document getDocument() const;
        Document getArray() const;

    private:
        bson_iter_t iter;
    };

    class Document {
    public:
        class iterator : public std::iterator<std::forward_iterator_tag, Reference, std::ptrdiff_t, const Reference*, const Reference&>{
        public:
            iterator(const bson_iter_t& i) : iter(i), is_end(false) {
            }

            iterator(bool is_end) : is_end(is_end) {
            }

            const Reference& operator*() const { return iter; }
            const Reference* operator->() const { return &iter; }

            iterator& operator++() {
                is_end = !bson_iter_next(&iter.iter);
                return *this;
            }

            bool operator==(const iterator& rhs) const {
                if (is_end && rhs.is_end) return true;
                return iter == rhs.iter;
            }
            
            bool operator!=(const iterator& rhs) const {
                return !(*this == rhs);
            }
            
        private:
            Reference iter;
            bool is_end;
        };

        iterator begin() {
            bson_t b;
            bson_iter_t iter;

            bson_init_static(&b, buf, len);
            bson_iter_init(&iter, &b);
            bson_iter_next(&iter);

            return iterator(iter);
        }

        iterator end() {
            return iterator(true);
        }

        Reference operator[](const char * key) const {
            bson_t b;
            bson_iter_t iter;

            bson_init_static(&b, buf, len);
            bson_iter_init_find(&iter, &b, key);

            return Reference(iter);
        }

        Document(const uint8_t * b, std::size_t l) : buf(b), len(l) {}
        Document() : buf(NULL), len(0) {}

        const uint8_t * getBuf() { return buf; }
        std::size_t getLen() { return len; }
        void setBuf(const uint8_t * b) { buf = b; }
        void setLen(std::size_t l) { len = l; }

        void print(std::ostream& out) const {
            bson_t b;
            bson_init_static(&b, buf, len);
            char * json = bson_as_json(&b, NULL);
            out << json;
            bson_free(json);
        }

    private:
        const uint8_t * buf;
        std::size_t len;
    };

    inline Document Reference::getDocument() const {
        const uint8_t * buf;
        uint32_t len;

        bson_iter_document(&iter, &len, &buf);

        return Document(buf, len);
    }

    inline Document Reference::getArray() const {
        const uint8_t * buf;
        uint32_t len;

        bson_iter_array(&iter, &len, &buf);

        return Document(buf, len);
    }

    std::ostream& operator<<(std::ostream& out, const Document& doc) {
        doc.print(out);
        return out;
    }

} // namespace bson

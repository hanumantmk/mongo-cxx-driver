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

#include "bson/document.h"

namespace bson {

Reference::Reference() {}

Reference::Reference(const bson_iter_t& i) { iter = i; }

bool Reference::operator==(const Reference& rhs) const {
    return (iter.raw == rhs.iter.raw && iter.off == rhs.iter.off);
}

Type Reference::type() const { return Type(bson_iter_type(&iter)); }

const char* Reference::key() const { return bson_iter_key(&iter); }

const char* Reference::getString() const { return bson_iter_utf8(&iter, NULL); }

std::tuple<const char*, uint32_t> Reference::getStringWLen() const {
    uint32_t len;
    const char* str = bson_iter_utf8(&iter, &len);
    return std::tuple<const char*, uint32_t>(str, len);
}

std::tuple<BinarySubtype, uint32_t, const uint8_t*> Reference::getBinary()
    const {
    bson_subtype_t type;
    uint32_t len;
    const uint8_t* binary;

    bson_iter_binary(&iter, &type, &len, &binary);

    return std::tuple<BinarySubtype, uint32_t, const uint8_t*>(
        BinarySubtype(type), len, binary);
}

double Reference::getDouble() const { return bson_iter_double(&iter); }

int32_t Reference::getInt32() const { return bson_iter_int32(&iter); }

int64_t Reference::getInt64() const { return bson_iter_int64(&iter); }

Document::iterator::iterator(const bson_iter_t& i) : iter(i), is_end(false) {}

Document::iterator::iterator(bool is_end) : is_end(is_end) {}

const Reference& Document::iterator::operator*() const { return iter; }
const Reference* Document::iterator::operator->() const { return &iter; }

Document::iterator& Document::iterator::operator++() {
    is_end = !bson_iter_next(&iter.iter);
    return *this;
}

bool Document::iterator::operator==(const iterator& rhs) const {
    if (is_end && rhs.is_end) return true;
    return iter == rhs.iter;
}

bool Document::iterator::operator!=(const iterator& rhs) const {
    return !(*this == rhs);
}

Document::iterator Document::begin() {
    bson_t b;
    bson_iter_t iter;

    bson_init_static(&b, buf, len);
    bson_iter_init(&iter, &b);
    bson_iter_next(&iter);

    return iterator(iter);
}

Document::iterator Document::end() { return iterator(true); }

Reference Document::operator[](const char* key) const {
    bson_t b;
    bson_iter_t iter;

    bson_init_static(&b, buf, len);
    bson_iter_init_find(&iter, &b, key);

    return Reference(iter);
}

Document::Document(const uint8_t* b, std::size_t l) : buf(b), len(l) {}
Document::Document() : buf(NULL), len(0) {}

const uint8_t* Document::getBuf() const { return buf; }
std::size_t Document::getLen() const { return len; }
void Document::setBuf(const uint8_t* b) { buf = b; }
void Document::setLen(std::size_t l) { len = l; }

void Document::print(std::ostream& out) const {
    bson_t b;
    bson_init_static(&b, buf, len);
    char* json = bson_as_json(&b, NULL);
    out << json;
    bson_free(json);
}

Document Reference::getDocument() const {
    const uint8_t* buf;
    uint32_t len;

    bson_iter_document(&iter, &len, &buf);

    return Document(buf, len);
}

Document Reference::getArray() const {
    const uint8_t* buf;
    uint32_t len;

    bson_iter_array(&iter, &len, &buf);

    return Document(buf, len);
}

std::ostream& operator<<(std::ostream& out, const Document& doc) {
    doc.print(out);
    return out;
}

}  // namespace bson

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

#include "bson/builder.hpp"

namespace bson {

Builder::open_doc_t Builder::open_doc;
Builder::close_doc_t Builder::close_doc;
Builder::open_array_t Builder::open_array;
Builder::close_array_t Builder::close_array;

Builder::Builder()
{
    _stack.reserve(100);
    _stack.emplace_back(false);
    bson_init(&_stack.back().bson);
}

Builder::~Builder() {
    for (auto&& x : _stack) {
        bson_destroy(&x.bson);
    }
}

Builder& Builder::key_append(const std::string& key, int32_t i32) {
    if (_stack.back().is_array) {
        throw(std::runtime_error("in subarray"));
    }

    bson_append_int32(&_stack.back().bson, key.c_str(), key.length(), i32);
    return *this;
}

Builder& Builder::key_append(const std::string& key, open_doc_t) {
    if (_stack.back().is_array) {
        throw(std::runtime_error("in subarray"));
    }

    bson_t* parent = &_stack.back().bson;
    _stack.emplace_back(false);
    bson_t* child = &_stack.back().bson;

    bson_append_document_begin(parent, key.c_str(), key.length(), child);
    return *this;
}

Builder& Builder::key_append(const std::string& key, open_array_t) {
    if (_stack.back().is_array) {
        throw(std::runtime_error("in subarray"));
    }

    bson_t* parent = &_stack.back().bson;
    _stack.emplace_back(true);
    bson_t* child = &_stack.back().bson;

    bson_append_array_begin(parent, key.c_str(), key.length(), child);
    return *this;
}

Builder& Builder::nokey_append(int32_t i32) {
    if (! _stack.back().is_array) {
        throw(std::runtime_error("in subdocument"));
    }

    std::string key = std::to_string(_stack.back().n);
    bson_append_int32(&_stack.back().bson, key.c_str(), key.length(), i32);
    return *this;
}

Builder& Builder::nokey_append(open_doc_t) {
    if (! _stack.back().is_array) {
        throw(std::runtime_error("in subdocument"));
    }

    bson_t* parent = &_stack.back().bson;
    _stack.emplace_back(false);
    bson_t* child = &_stack.back().bson;

    std::string key = std::to_string(_stack.back().n);

    bson_append_document_begin(parent, key.c_str(), key.length(), child);
    return *this;
}

Builder& Builder::nokey_append(close_doc_t) {
    if (_stack.back().is_array || _stack.size() < 2) {
        throw(std::runtime_error("in subdocument or insufficient stack"));
    }

    bson_t* child = &_stack.back().bson;
    bson_t* parent = &_stack[_stack.size() - 2].bson;

    bson_append_document_end(parent, child);

    _stack.pop_back();

    return *this;
}

Builder& Builder::nokey_append(open_array_t) {
    if (! _stack.back().is_array) {
        throw(std::runtime_error("in subdocument"));
    }

    bson_t* parent = &_stack.back().bson;
    _stack.emplace_back(true);
    bson_t* child = &_stack.back().bson;

    std::string key = std::to_string(_stack.back().n);

    bson_append_array_begin(parent, key.c_str(), key.length(), child);
    return *this;
}

Builder& Builder::nokey_append(close_array_t) {
    if (! _stack.back().is_array || _stack.size() < 2) {
        throw(std::runtime_error("in subdocument or insufficient stack"));
    }

    bson_t* child = &_stack.back().bson;
    bson_t* parent = &_stack[_stack.size() - 2].bson;

    bson_append_array_end(parent, child);

    _stack.pop_back();

    return *this;
}

document::view Builder::view() const {
    return document::view(bson_get_data(&_stack.front().bson), _stack.front().bson.len);
}

}  // namespace bson

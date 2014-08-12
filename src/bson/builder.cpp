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
#include "bson/util/itoa.hpp"

namespace bson {

builder::open_doc_t builder::open_doc;
builder::close_doc_t builder::close_doc;
builder::open_array_t builder::open_array;
builder::close_array_t builder::close_array;

builder::builder() {
    _stack.reserve(100);
    _stack.emplace_back(false);
    bson_init(&_stack.back().bson);
}

builder::~builder() {
    for (auto&& x : _stack) {
        bson_destroy(&x.bson);
    }
}

builder& builder::key_append(const string_or_literal& key, int32_t i32) {
    if (_stack.back().is_array) {
        throw(std::runtime_error("in subarray"));
    }

    bson_append_int32(&_stack.back().bson, key.c_str(), key.length(), i32);
    return *this;
}

builder& builder::key_append(const string_or_literal& key, open_doc_t) {
    if (_stack.back().is_array) {
        throw(std::runtime_error("in subarray"));
    }

    bson_t* parent = &_stack.back().bson;
    _stack.emplace_back(false);
    bson_t* child = &_stack.back().bson;

    bson_append_document_begin(parent, key.c_str(), key.length(), child);
    return *this;
}

builder& builder::key_append(const string_or_literal& key, open_array_t) {
    if (_stack.back().is_array) {
        throw(std::runtime_error("in subarray"));
    }

    bson_t* parent = &_stack.back().bson;
    _stack.emplace_back(true);
    bson_t* child = &_stack.back().bson;

    bson_append_array_begin(parent, key.c_str(), key.length(), child);
    return *this;
}

builder& builder::nokey_append(int32_t i32) {
    if (!_stack.back().is_array) {
        throw(std::runtime_error("in subdocument"));
    }

    util::itoa key(_stack.back().n++);
    bson_append_int32(&_stack.back().bson, key.c_str(), key.length(), i32);

    return *this;
}

builder& builder::nokey_append(open_doc_t) {
    if (!_stack.back().is_array) {
        throw(std::runtime_error("in subdocument"));
    }

    bson_t* parent = &_stack.back().bson;
    _stack.emplace_back(false);
    bson_t* child = &_stack.back().bson;

    util::itoa key(_stack.back().n++);
    bson_append_document_begin(parent, key.c_str(), key.length(), child);

    return *this;
}

builder& builder::nokey_append(close_doc_t) {
    if (_stack.back().is_array || _stack.size() < 2) {
        throw(std::runtime_error("in subdocument or insufficient stack"));
    }

    bson_t* child = &_stack.back().bson;
    bson_t* parent = &_stack[_stack.size() - 2].bson;

    bson_append_document_end(parent, child);

    _stack.pop_back();

    return *this;
}

builder& builder::nokey_append(open_array_t) {
    if (!_stack.back().is_array) {
        throw(std::runtime_error("in subdocument"));
    }

    bson_t* parent = &_stack.back().bson;
    _stack.emplace_back(true);
    bson_t* child = &_stack.back().bson;

    util::itoa key(_stack.back().n++);
    bson_append_array_begin(parent, key.c_str(), key.length(), child);

    return *this;
}

builder& builder::nokey_append(close_array_t) {
    if (!_stack.back().is_array || _stack.size() < 2) {
        throw(std::runtime_error("in subdocument or insufficient stack"));
    }

    bson_t* child = &_stack.back().bson;
    bson_t* parent = &_stack[_stack.size() - 2].bson;

    bson_append_array_end(parent, child);

    _stack.pop_back();

    return *this;
}

document::view builder::view() const {
    return document::view(bson_get_data(&_stack.front().bson),
                          _stack.front().bson.len);
}

}  // namespace bson

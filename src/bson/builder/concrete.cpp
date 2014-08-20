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

class builder::impl {
   public:
    impl() {
        _stack.reserve(100);
        _stack.emplace_back(false);
        bson_init(&_stack.back().bson);
    }

    ~impl() { bson_destroy(&_stack[0].bson); }

    struct frame {
        frame(bool is_array) : n(0), is_array(is_array) {}

        std::size_t n;
        bool is_array;
        bson_t bson;
    };

    std::vector<frame> _stack;
};

namespace builder_helpers {
open_doc_t open_doc;
close_doc_t close_doc;
open_array_t open_array;
close_array_t close_array;
}

builder::builder() : _impl(new impl()) {}
builder::builder(builder&&) = default;
builder& builder::operator=(builder&&) = default;
builder::~builder() = default;

builder::operator key_ctx<closed_ctx>() { return key_ctx<closed_ctx>(this); }

builder::document_ctx<builder::key_ctx<builder>> builder::operator<<(string_or_literal rhs) {
    key_ctx<builder> ctx(this);

    return ctx << std::move(rhs);
}

builder& builder::key_append(const string_or_literal& key, std::int32_t i32) {
    if (_impl->_stack.back().is_array) {
        throw(std::runtime_error("in subarray"));
    }

    bson_append_int32(&_impl->_stack.back().bson, key.c_str(), key.length(), i32);
    return *this;
}

builder& builder::key_append(const string_or_literal& key, builder_helpers::open_doc_t) {
    if (_impl->_stack.back().is_array) {
        throw(std::runtime_error("in subarray"));
    }

    bson_t* parent = &_impl->_stack.back().bson;
    _impl->_stack.emplace_back(false);
    bson_t* child = &_impl->_stack.back().bson;

    bson_append_document_begin(parent, key.c_str(), key.length(), child);
    return *this;
}

builder& builder::key_append(const string_or_literal& key, builder_helpers::open_array_t) {
    if (_impl->_stack.back().is_array) {
        throw(std::runtime_error("in subarray"));
    }

    bson_t* parent = &_impl->_stack.back().bson;
    _impl->_stack.emplace_back(true);
    bson_t* child = &_impl->_stack.back().bson;

    bson_append_array_begin(parent, key.c_str(), key.length(), child);
    return *this;
}

builder& builder::nokey_append(std::int32_t i32) {
    if (!_impl->_stack.back().is_array) {
        throw(std::runtime_error("in subdocument"));
    }

    util::itoa key(_impl->_stack.back().n++);
    bson_append_int32(&_impl->_stack.back().bson, key.c_str(), key.length(), i32);

    return *this;
}

builder& builder::nokey_append(builder_helpers::open_doc_t) {
    if (!_impl->_stack.back().is_array) {
        throw(std::runtime_error("in subdocument"));
    }

    bson_t* parent = &_impl->_stack.back().bson;
    _impl->_stack.emplace_back(false);
    bson_t* child = &_impl->_stack.back().bson;

    util::itoa key(_impl->_stack.back().n++);
    bson_append_document_begin(parent, key.c_str(), key.length(), child);

    return *this;
}

builder& builder::nokey_append(builder_helpers::close_doc_t) {
    if (_impl->_stack.back().is_array || _impl->_stack.size() < 2) {
        throw(std::runtime_error("in subdocument or insufficient stack"));
    }

    bson_t* child = &_impl->_stack.back().bson;
    bson_t* parent = &_impl->_stack[_impl->_stack.size() - 2].bson;

    bson_append_document_end(parent, child);

    _impl->_stack.pop_back();

    return *this;
}

builder& builder::nokey_append(builder_helpers::open_array_t) {
    if (!_impl->_stack.back().is_array) {
        throw(std::runtime_error("in subdocument"));
    }

    bson_t* parent = &_impl->_stack.back().bson;
    _impl->_stack.emplace_back(true);
    bson_t* child = &_impl->_stack.back().bson;

    util::itoa key(_impl->_stack.back().n++);
    bson_append_array_begin(parent, key.c_str(), key.length(), child);

    return *this;
}

builder& builder::nokey_append(builder_helpers::close_array_t) {
    if (!_impl->_stack.back().is_array || _impl->_stack.size() < 2) {
        throw(std::runtime_error("in subdocument or insufficient stack"));
    }

    bson_t* child = &_impl->_stack.back().bson;
    bson_t* parent = &_impl->_stack[_impl->_stack.size() - 2].bson;

    bson_append_array_end(parent, child);

    _impl->_stack.pop_back();

    return *this;
}

document::view builder::view() const {
    return document::view(bson_get_data(&_impl->_stack.front().bson),
                          _impl->_stack.front().bson.len);
}

}  // namespace bson

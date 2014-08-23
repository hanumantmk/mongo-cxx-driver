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
#include "bson/util/stack.hpp"

#include <vector>

namespace bson {

class builder::impl {
   public:
    impl()
        : _buf_ptr(reinterpret_cast<uint8_t*>(bson_malloc(256))),
          _buf_len(256),
          _writer(bson_writer_new(&_buf_ptr, &_buf_len, 0, &bson_realloc_ctx, NULL)) {
        bson_writer_begin(_writer, &_root);
    }

    ~impl() {
        _stack.~stack();
        bson_writer_destroy(_writer);
        bson_free(_buf_ptr);
    }

    void clear() {
        while (!_stack.empty()) {
            _stack.pop_back();
        }

        bson_writer_rollback(_writer);
        bson_writer_begin(_writer, &_root);
    }

    bson_t* back() {
        if (_stack.empty()) {
            return _root;
        } else {
            return &_stack.back().bson;
        }
    }

    void push_back_document(const char* key, std::size_t len) {
        if (_stack.empty()) {
            _stack.emplace_back(_root, key, len, false);
        } else {
            _stack.emplace_back(back(), key, len, false);
        }
    }

    void push_back_array(const char* key, std::size_t len) {
        if (_stack.empty()) {
            _stack.emplace_back(_root, key, len, true);
        } else {
            _stack.emplace_back(back(), key, len, true);
        }
    }

    void pop_back() { _stack.pop_back(); }

    int next_key() { return _stack.back().n++; }

    bson_t* root() { return _root; }
    bool is_array() {
        if (_stack.empty()) {
            return false;
        } else {
            return _stack.back().is_array;
        }
    }

   private:
    struct frame {
        frame(bson_t* parent, const char* key, std::size_t len, bool is_array)
            : n(0), is_array(is_array), parent(parent) {
            if (is_array) {
                bson_append_array_begin(parent, key, len, &bson);
            } else {
                bson_append_document_begin(parent, key, len, &bson);
            }
        }

        ~frame() {
            if (is_array) {
                bson_append_array_end(parent, &bson);
            } else {
                bson_append_document_end(parent, &bson);
            }
        }

        std::size_t n;
        bool is_array;
        bson_t bson;
        bson_t* parent;
    };

    util::stack<frame, 4> _stack;

    uint8_t* _buf_ptr;
    size_t _buf_len;

    bson_writer_t* _writer;

    bson_t* _root;
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
    if (_impl->is_array()) {
        throw(std::runtime_error("in subarray"));
    }

    bson_append_int32(_impl->back(), key.c_str(), key.length(), i32);
    return *this;
}

builder& builder::key_append(const string_or_literal& key, builder_helpers::open_doc_t) {
    if (_impl->is_array()) {
        throw(std::runtime_error("in subarray"));
    }

    _impl->push_back_document(key.c_str(), key.length());

    return *this;
}

builder& builder::key_append(const string_or_literal& key, builder_helpers::open_array_t) {
    if (_impl->is_array()) {
        throw(std::runtime_error("in subarray"));
    }

    _impl->push_back_array(key.c_str(), key.length());

    return *this;
}

builder& builder::nokey_append(std::int32_t i32) {
    if (!_impl->is_array()) {
        throw(std::runtime_error("in subdocument"));
    }

    util::itoa key(_impl->next_key());
    bson_append_int32(_impl->back(), key.c_str(), key.length(), i32);

    return *this;
}

builder& builder::nokey_append(builder_helpers::open_doc_t) {
    if (!_impl->is_array()) {
        throw(std::runtime_error("in subdocument"));
    }

    util::itoa key(_impl->next_key());
    _impl->push_back_document(key.c_str(), key.length());

    return *this;
}

builder& builder::nokey_append(builder_helpers::close_doc_t) {
    if (_impl->is_array()) {
        // TODO handle insufficient stack
        throw(std::runtime_error("in subdocument or insufficient stack"));
    }

    _impl->pop_back();

    return *this;
}

builder& builder::nokey_append(builder_helpers::open_array_t) {
    if (!_impl->is_array()) {
        throw(std::runtime_error("in subdocument"));
    }

    util::itoa key(_impl->next_key());
    _impl->push_back_array(key.c_str(), key.length());

    return *this;
}

builder& builder::nokey_append(builder_helpers::close_array_t) {
    if (!_impl->is_array()) {
        // TODO handle stack
        throw(std::runtime_error("in subdocument or insufficient stack"));
    }

    _impl->pop_back();

    return *this;
}

document::view builder::view() const {
    return document::view(bson_get_data(_impl->root()), _impl->root()->len);
}

void builder::clear() { _impl->clear(); }

}  // namespace bson

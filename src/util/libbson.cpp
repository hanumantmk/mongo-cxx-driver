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

#include "util/libbson.h"

namespace bson {
namespace libbson {

    static void doc_to_bson_t(const bson::Document::View& doc, bson_t* bson) {
        bson_init_static(bson, doc.getBuf(), doc.getLen());
    }

    static void optional_doc_to_bson_t(const mongo::driver::optional<bson::Document::View>& doc, bson_t* bson) {
        if (doc) {
            doc_to_bson_t(*doc, bson);
        }
    }

    scoped_bson_t::scoped_bson_t(const mongo::driver::optional<bson::Document::View>& doc) : _is_initialized(doc) {
        optional_doc_to_bson_t(doc, &_bson);
    }

    scoped_bson_t::scoped_bson_t(const bson::Document::View& doc) : _is_initialized(true) {
        doc_to_bson_t(doc, &_bson);
    }

    void scoped_bson_t::init_from_static(const mongo::driver::optional<bson::Document::View>& doc) {
        _is_initialized = static_cast<bool>(doc);
        optional_doc_to_bson_t(doc, &_bson);
    }

    void scoped_bson_t::init_from_static(const bson::Document::View& doc) {
        _is_initialized = true;
        doc_to_bson_t(doc, &_bson);
    }

    void scoped_bson_t::init() {
        _is_initialized = true;
        bson_init(&_bson);
    }

    scoped_bson_t::scoped_bson_t() : _is_initialized(false) {
    }

    scoped_bson_t::~scoped_bson_t() {
        if (_is_initialized) {
            bson_destroy(&_bson);
        }
    }

    bson_t* scoped_bson_t::bson() {
        return _is_initialized ? &_bson : NULL;
    }

    bson::Document::View scoped_bson_t::view() {
        return _is_initialized ? bson::Document::View(bson_get_data(bson()), bson()->len) : bson::Document::View();
    }

} // namespace libbson
} // namespace bson

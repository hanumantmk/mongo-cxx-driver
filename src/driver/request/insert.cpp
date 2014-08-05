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

#include "driver/request/insert_request.h"
#include "driver/util/libbson.h"

namespace mongo {
namespace driver {
namespace model {

insert_request::insert_request(const bson::Document::View& doc) : _doc(doc) {
}

insert_request::insert_request(const insert& model) : _doc(model.document()) {
}

void insert_request::add(mongoc_bulk_operation_t* bulk) const {
    bson::libbson::scoped_bson_t to_insert(_doc);
    mongoc_bulk_operation_insert(bulk, to_insert.bson());
}

} // namespace model
} // namespace driver
} // namespace mongo

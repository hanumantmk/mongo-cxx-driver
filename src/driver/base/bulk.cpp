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

#include "driver/base/bulk.hpp"
#include "driver/base/collection.hpp"
#include "driver/request/write.hpp"
#include "driver/util/libbson.hpp"

namespace mongo {
namespace driver {

/*
 *    BulkOperationBuilder::BulkOperationBuilder(const Collection * collection,
 *bool is_ordered)
 *        :
 *_bulk_operation(mongoc_collection_create_bulk_operation(collection->_collection,
 *is_ordered, NULL))
 *    {}
 *
 *    BulkOperationBuilder::BulkOperationBuilder(BulkOperationBuilder&& rhs) {
 *        *this = std::move(rhs);
 *    }
 *
 *    BulkOperationBuilder&
 *BulkOperationBuilder::operator=(BulkOperationBuilder&& rhs) {
 *        _bulk_operation = rhs._bulk_operation;
 *        rhs._bulk_operation = NULL;
 *        return *this;
 *    }
 *
 *    BulkOperationBuilder::~BulkOperationBuilder() {
 *        if (_bulk_operation) {
 *            mongoc_bulk_operation_destroy(_bulk_operation);
 *        }
 *    }
 *
 *    void BulkOperationBuilder::add(const WriteRequest& req) {
 *        req.add(_bulk_operation);
 *    }
 *
 *    WriteResult BulkOperationBuilder::execute() {
 *        bson_error_t error;
 *        bson::libbson::scoped_bson_t reply;
 *        reply.init();
 *
 *        mongoc_bulk_operation_execute(_bulk_operation, reply.bson(), &error);
 *
 *        return WriteResult(reply.view());
 *    }
 */
}
}

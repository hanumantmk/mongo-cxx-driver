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

#include "mongoc.h"

#include "driver/result/write.hpp"

namespace mongo {
namespace driver {

/*
 *    class WriteRequest;
 *    class Collection;
 *
 *    class BulkOperationBuilder {
 *
 *        friend class Collection;
 *
 *    public:
 *        BulkOperationBuilder(BulkOperationBuilder&& rhs);
 *        BulkOperationBuilder& operator=(BulkOperationBuilder&& rhs);
 *        ~BulkOperationBuilder();
 *
 *    private:
 *        BulkOperationBuilder(const Collection * collection, bool is_ordered);
 *        void add(const WriteRequest& req);
 *        WriteResult execute();
 *
 *        BulkOperationBuilder(const BulkOperationBuilder& rhs) = delete;
 *        BulkOperationBuilder& operator=(const BulkOperationBuilder& rhs) =
 *delete;
 *
 *        mongoc_bulk_operation_t* _bulk_operation;
 *    };
 */

}  // namespace driver
}  // namespace mongo

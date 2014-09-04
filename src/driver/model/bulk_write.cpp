// Copyright 2014 MongoDB Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "driver/model/bulk_write.hpp"

#include "mongoc.h"
#include "driver/private/cast.hpp"

namespace mongo {
namespace driver {
namespace model {

namespace {
static void mongoc_bulk_operation_dtor(void* bulk_operation_ptr) noexcept {
    mongoc_bulk_operation_destroy(static_cast<mongoc_bulk_operation_t*>(bulk_operation_ptr));
}
}  // namespace

bulk_write::bulk_write(bool ordered) :
    _impl(mongoc_bulk_operation_new(ordered), mongoc_bulk_operation_dtor) {}


bulk_write& bulk_write::append(const write& operation) {
    mongoc_bulk_operation_util::cast<mongoc_bulk_operation_t>(_impl)
}

bool ordered() const;


}  // namespace model
}  // namespace driver
}  // namespace mongo

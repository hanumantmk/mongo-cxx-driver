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
#include "driver/model/private/bulk_write.hpp"
#include "driver/util/libbson.hpp"

namespace mongo {
namespace driver {
namespace model {

using namespace bson::libbson;

bulk_write::bulk_write(bulk_write&&) = default;
bulk_write& bulk_write::operator=(bulk_write&&) = default;
bulk_write::~bulk_write() = default;

bulk_write::bulk_write(bool ordered) :
    _impl(new impl{ordered, mongoc_bulk_operation_new(ordered)})
{}

bulk_write& bulk_write::append(write operation_t) {

    switch (operation_t.type()) {
        case write_type::kInsertOne: {
            scoped_bson_t doc(operation_t.get_insert_one().document());

            mongoc_bulk_operation_insert(_impl->operation_t, doc.bson());
            break;
        }
        case write_type::kInsertMany: {
            for (auto&& x : operation_t.get_insert_many().documents()) {
                scoped_bson_t doc(x);

                mongoc_bulk_operation_insert(_impl->operation_t, doc.bson());
            }
            break;
        }
        case write_type::kUpdateOne: {
            scoped_bson_t criteria(operation_t.get_update_one().criteria());
            scoped_bson_t update(operation_t.get_update_one().update());
            bool upsert = operation_t.get_update_one().upsert().value_or(false);

            mongoc_bulk_operation_update_one(_impl->operation_t, criteria.bson(), update.bson(), upsert);
            break;
        }
        case write_type::kUpdateMany: {
            scoped_bson_t criteria(operation_t.get_update_many().criteria());
            scoped_bson_t update(operation_t.get_update_many().update());
            bool upsert = operation_t.get_update_many().upsert().value_or(false);

            mongoc_bulk_operation_update(_impl->operation_t, criteria.bson(), update.bson(), upsert);
            break;
        }
        case write_type::kRemoveOne: {
            scoped_bson_t criteria(operation_t.get_remove_one().criteria());

            mongoc_bulk_operation_remove_one(_impl->operation_t, criteria.bson());

            break;
        }
        case write_type::kRemoveMany: {
            scoped_bson_t criteria(operation_t.get_remove_many().criteria());

            mongoc_bulk_operation_remove(_impl->operation_t, criteria.bson());

            break;
        }
        case write_type::kReplaceOne: {
            scoped_bson_t criteria(operation_t.get_replace_one().criteria());
            scoped_bson_t replace(operation_t.get_replace_one().replacement());
            bool upsert = operation_t.get_replace_one().upsert().value_or(false);

            mongoc_bulk_operation_replace_one(_impl->operation_t, criteria.bson(), replace.bson(), upsert);
            break;
        }
        case write_type::kUninitialized: break; // TODO: something exceptiony
    }

    return *this;
}

bool bulk_write::ordered() const {
    return _impl->ordered;
}

}  // namespace model
}  // namespace driver
}  // namespace mongo

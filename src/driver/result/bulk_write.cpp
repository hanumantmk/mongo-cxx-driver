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

#include "driver/result/bulk_write.hpp"

namespace mongo {
namespace driver {
namespace result {

std::int64_t bulk_write::inserted_count() const {
    return _view()["nInserted"].get_int64();
}

std::int64_t bulk_write::matched_count() const {
    return _view()["nMatched"].get_int64();
}

std::int64_t bulk_write::modified_count() const {
    return _view()["nModified"].get_int64();
};

std::int64_t bulk_write::deleted_count() const {
    return _view()["nRemoved"].get_int64();
}

std::int64_t bulk_write::upserted_count() const {
    return _view()["nUpserted"].get_int64();
}

bson::document::view bulk_write::inserted_ids() const {
    return _view()["inserted_ids"].get_array();
}

bson::document::view bulk_write::upserted_ids() const {
    return _view()["upserted_ids"].get_array();
}

}  // namespace result
}  // namespace driver
}  // namespace mongo

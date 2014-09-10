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

#include "driver/model/find_one_and_delete.hpp"

namespace mongo {
namespace driver {
namespace model {

find_one_and_delete::find_one_and_delete(bson::document::view criteria)
    : _criteria(std::move(criteria)) {}

find_one_and_delete& find_one_and_delete::projection(bson::document::view projection) {
    _projection = projection;
    return *this;
}

find_one_and_delete& find_one_and_delete::sort(bson::document::view ordering) {
    _ordering = ordering;
    return *this;
}

find_one_and_delete& find_one_and_delete::write_concern(class write_concern wc) {
    _write_concern = std::move(wc);
    return *this;
}

const bson::document::view& find_one_and_delete::criteria() const { return _criteria; }

const optional<bson::document::view>& find_one_and_delete::projection() const { return _projection; }

const optional<bson::document::view>& find_one_and_delete::sort() const { return _ordering; }

const optional<class write_concern>& find_one_and_delete::write_concern() const { return _write_concern; }

}  // namespace model
}  // namespace driver
}  // namespace mongo

#include "driver/config/postlude.hpp"

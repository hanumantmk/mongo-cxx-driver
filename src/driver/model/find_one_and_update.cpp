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

#include "driver/model/find_one_and_update.hpp"

namespace mongo {
namespace driver {
namespace model {

find_one_and_update::find_one_and_update(bson::document::view criteria, bson::document::view update)
    : _criteria(std::move(criteria)), _update(std::move(update)) {}

find_one_and_update& find_one_and_update::projection(bson::document::view projection) {
    _projection = projection;

    return *this;
}

find_one_and_update& find_one_and_update::return_replacement(bool return_replacement) {
    _return_replacement = return_replacement;

    return *this;
}
find_one_and_update& find_one_and_update::sort(bson::document::view ordering) {
    _ordering = ordering;

    return *this;
}
find_one_and_update& find_one_and_update::upsert(bool upsert) {
    _upsert = upsert;

    return *this;
}
find_one_and_update& find_one_and_update::write_concern(class write_concern wc) {
    _write_concern = std::move(wc);
    return *this;
}

const bson::document::view& find_one_and_update::criteria() const { return _criteria; }
const bson::document::view& find_one_and_update::update() const { return _update; }

const optional<bson::document::view>& find_one_and_update::projection() const { return _projection; }
const optional<bool>& find_one_and_update::return_replacement() const { return _return_replacement; }
const optional<bson::document::view>& find_one_and_update::sort() const { return _ordering; }
const optional<bool>& find_one_and_update::upsert() const { return _upsert; }
const optional<class write_concern>& find_one_and_update::write_concern() const { return _write_concern; }

}  // namespace model
}  // namespace driver
}  // namespace mongo

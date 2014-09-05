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

#include "driver/model/find_one_and_replace.hpp"

namespace mongo {
namespace driver {
namespace model {

find_one_and_replace::find_one_and_replace(bson::document::view criteria, bson::document::view replacement)
    : _criteria(criteria)
    , _replacement(replacement)
{}

find_one_and_replace& find_one_and_replace::projection(bson::document::view projection) {
    _projection = projection;
    return *this;
}

find_one_and_replace& find_one_and_replace::return_replacement(bool return_replacement) {
    _return_replacement = return_replacement;
    return *this;
}

find_one_and_replace& find_one_and_replace::sort(bson::document::view ordering) {
    _ordering = ordering;
    return *this;
}

find_one_and_replace& find_one_and_replace::upsert(bool upsert) {
    _upsert = upsert;
    return *this;
}

bson::document::view find_one_and_replace::criteria() const {
    return _criteria;
}

bson::document::view find_one_and_replace::replacement() const {
    return _replacement;
}

optional<bson::document::view> find_one_and_replace::projection() const {
    return _projection;
}

optional<bool> find_one_and_replace::return_replacement() const {
    return _return_replacement;
}

optional<bson::document::view> find_one_and_replace::sort() const {
    return _ordering;
}

optional<bool> find_one_and_replace::upsert() const {
    return _upsert;
}

}  // namespace model
}  // namespace driver
}  // namespace mongo

#include "driver/config/postlude.hpp"

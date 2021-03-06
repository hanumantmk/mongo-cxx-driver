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

#include "driver/model/replace_one.hpp"

namespace mongo {
namespace driver {
namespace model {

replace_one::replace_one(bson::document::view criteria, bson::document::view replacement)
    : _criteria(std::move(criteria)), _replacement(std::move(replacement)) {}

replace_one& replace_one::upsert(bool upsert) {
    _upsert = upsert;

    return *this;
}

replace_one& replace_one::write_concern(class write_concern wc) {
    _write_concern = std::move(wc);
    return *this;
}

const bson::document::view& replace_one::criteria() const { return _criteria; }

const bson::document::view& replace_one::replacement() const { return _replacement; }

const optional<bool>& replace_one::upsert() const { return _upsert; }

const optional<class write_concern>& replace_one::write_concern() const { return _write_concern; }

}  // namespace model
}  // namespace driver
}  // namespace mongo

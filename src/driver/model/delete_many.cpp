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

#include "driver/model/delete_many.hpp"

namespace mongo {
namespace driver {
namespace model {

delete_many::delete_many(bson::document::view criteria) : _criteria(std::move(criteria)) {}

delete_many& delete_many::write_concern(class write_concern wc) {
    _write_concern = std::move(wc);
    return *this;
}

const bson::document::view& delete_many::criteria() const { return _criteria; }

const optional<class write_concern>& delete_many::write_concern() const { return _write_concern; }

}  // namespace model
}  // namespace driver
}  // namespace mongo

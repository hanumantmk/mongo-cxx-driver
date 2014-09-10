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

#include "driver/model/insert_one.hpp"

namespace mongo {
namespace driver {
namespace model {

insert_one::insert_one(bson::document::view document) : _document(std::move(document)) {}

insert_one& insert_one::write_concern(class write_concern wc) {
    _write_concern = std::move(wc);
    return *this;
}

const bson::document::view& insert_one::document() const { return _document; }

const optional<class write_concern>& insert_one::write_concern() const { return _write_concern; }

}  // namespace model
}  // namespace driver
}  // namespace mongo

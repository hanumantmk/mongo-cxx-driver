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

#pragma once

#include "driver/config/prelude.hpp"

#include <iostream>

#include "bson/document.hpp"

namespace mongo {
namespace driver {
namespace result {

class LIBMONGOCXX_EXPORT write {
   public:
    write(const bson::document::view& view);
    write(bson::document::value value);

    /* TODO replace this: */
    write();

    friend std::ostream& operator<<(std::ostream& out, const write& doc) {
        out << doc._value.view();
        return out;
    }

   private:
    bson::document::view_or_value _value;
};

}  // namespace result
}  // namespace driver
}  // namespace mongo

#include "driver/config/postlude.hpp"

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

#include "driver/base/write_concern.hpp"
#include "bson/document.hpp"
#include "driver/util/optional.hpp"

namespace mongo {
namespace driver {
namespace model {

class LIBMONGOCXX_EXPORT insert_one {

   public:
    insert_one(bson::document::view document);

    insert_one& write_concern(class write_concern wc);

    const bson::document::view& document() const;
    const optional<class write_concern>& write_concern() const;

   private:
    bson::document::view _document;
    optional<class write_concern> _write_concern;
};

}  // namespace model
}  // namespace driver
}  // namespace mongo

#include "driver/config/postlude.hpp"

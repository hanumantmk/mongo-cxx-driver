/**
 * Copyright 2014 MongoDB Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include "preamble.h"


#include "bson/document.hpp"
#include "driver/model/write.hpp"
#include "driver/util/optional.hpp"

namespace mongo {
namespace driver {
namespace model {

class MONGOCXX_EXPORT remove : write<remove> {

   public:
    remove(const bson::document::view& filter);

    remove& multi(bool multi);
    optional<bool> multi();

   private:
    bson::document::view _filter;

    optional<bool> _multi;
};

}  // namespace model
}  // namespace driver
}  // namespace mongo

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

#include "bson/document.hpp"
#include "driver/model/write.hpp"
#include "driver/util/optional.hpp"

namespace mongo {
namespace driver {
namespace model {

namespace details {

class LIBMONGOCXX_EXPORT xupdate : public write<xupdate> {

   public:
    xupdate(bson::document::view criteria, bson::document::view update);

    bson::document::view criteria() const;
    bson::document::view update() const;

    xupdate& multi(bool multi);
    xupdate& upsert(bool upsert);

    optional<bool> multi() const;
    optional<bool> upsert() const;

   private:
    bson::document::view _criteria;
    bson::document::view _update;

    optional<bool> _multi;
    optional<bool> _upsert;
};

}  // namespace details

using update = details::xupdate;

}  // namespace model
}  // namespace driver
}  // namespace mongo

#include "driver/config/postlude.hpp"

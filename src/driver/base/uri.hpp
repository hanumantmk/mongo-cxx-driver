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

#include <memory>
#include <string>
#include <vector>

#include "bson/document.hpp"

#include "driver/base/host.hpp"
#include "driver/base/read_preference.hpp"
#include "driver/base/write_concern.hpp"

namespace mongo {
namespace driver {

class uri {

    class impl;

    friend class client;

   public:
    // TODO: document the default is localhost:27017...
    uri(const std::string& uri_string="mongodb://localhost:27017/");

    uri(uri&& other) noexcept;
    uri& operator=(uri&& rhs) noexcept;

    ~uri();

    const std::string auth_mechanism() const;
    const std::string auth_source() const;
    const std::vector<host> hosts() const;
    const std::string database() const;
    bson::document::view options() const;
    const std::string username() const;
    const std::string password() const;
    const class read_preference read_preference() const;
    const std::string replica_set() const;
    bool ssl() const;
    const class write_concern write_concern() const;

   private:
    std::unique_ptr<impl> _impl;

}; // class uri

}  // namespace driver
}  // namespace mongo

#include "driver/config/postlude.hpp"

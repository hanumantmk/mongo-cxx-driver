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

#include "driver/base/collection.hpp"
#include "driver/base/write_concern.hpp"
#include "driver/base/read_preference.hpp"

namespace mongo {
namespace driver {

class client;
class collection;

/// The database class serves as a representation of a MongoDB database. It acts as a gateway
/// for accessing collections that are contained within the particular database that an instance
/// of the class represents. It inherets all of its default settings from the client that calls
/// it's constructor.
class LIBMONGOCXX_EXPORT database {

    friend class client;
    friend class collection;

    class impl;

   public:
    class collection operator[](const std::string& collection_name);
    class collection collection(const std::string& collection_name);

    const std::string& name() const;

    void read_preference(class read_preference rp);
    const class read_preference& read_preference() const;

    void write_concern(class write_concern wc);
    const class write_concern& write_concern() const;

    database(database&& rhs);
    database& operator=(database&& rhs);
    ~database();

   private:
    database(const class client& client, const std::string& database_name);

    std::unique_ptr<impl> _impl;
};

}  // namespace driver
}  // namespace mongo

#include "driver/config/postlude.hpp"

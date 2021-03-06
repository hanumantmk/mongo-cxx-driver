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

#include "driver/libmongoc.hpp"

#include "driver/base/database.hpp"
#include "driver/base/client.hpp"
#include "driver/base/private/database.hpp"
#include "driver/base/private/client.hpp"

namespace mongo {
namespace driver {

database::database(database&&) = default;
database& database::operator=(database&&) = default;
database::~database() = default;

database::database(const class client& client, const std::string& database_name)
    : _impl(new impl{mongoc_client_get_database(client._impl->client_t, database_name.c_str()),
                     &client, database_name.c_str()}) {}

const std::string& database::name() const { return _impl->name; }

void database::read_preference(class read_preference rp) { _impl->read_preference(std::move(rp)); }
const class read_preference& database::read_preference() const { return _impl->read_preference(); }

void database::write_concern(class write_concern wc) { _impl->write_concern(std::move(wc)); }
const class write_concern& database::write_concern() const { return _impl->write_concern(); }

collection database::collection(const std::string& collection_name) {
    return mongo::driver::collection(*this, collection_name);
}

collection database::operator[](const std::string& collection_name) {
    return collection(collection_name);
}

}  // namespace driver
}  // namespace mongo

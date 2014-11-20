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

#include "private/preamble.hpp"

#include "driver/base/client.hpp"
#include "driver/base/settings.hpp"
#include "driver/base/private/client.hpp"

namespace mongo {
namespace driver {

client::client() : client("mongodb://localhost:27017") {}

client::client(client&&) = default;

client::client(const std::string& mongodb_uri)
    : _impl(new impl{mongoc_client_new(mongodb_uri.c_str())}) {}

client::client(const settings& settings) : client(settings._mongodb_uri.c_str()) {}

client& client::operator=(client&&) = default;

client::~client() = default;

void client::read_preference(class read_preference rp) { _impl->read_preference(std::move(rp)); }
const class read_preference& client::read_preference() const { return _impl->read_preference(); }

void client::write_concern(class write_concern wc) { _impl->write_concern(std::move(wc)); }
const class write_concern& client::write_concern() const { return _impl->write_concern(); }

class database client::database(const std::string& database_name) {
    return mongo::driver::database(*this, database_name);
}

class database client::operator[](const std::string& database_name) {
    return database(database_name);
}

}  // namespace driver
}  // namespace mongo

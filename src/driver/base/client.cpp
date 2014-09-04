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
#include "driver/base/options.hpp"
#include "driver/private/cast.hpp"

namespace mongo {
namespace driver {

namespace {
static void mongoc_client_dtor(void* client_ptr) noexcept {
    mongoc_client_destroy(static_cast<mongoc_client_t*>(client_ptr));
}
}  // namespace

client::client()
    : _client(mongoc_client_new("localhost:27017"), mongoc_client_dtor) {}

client::client(const std::string& mongodb_uri)
    : _client(mongoc_client_new(mongodb_uri.c_str()), mongoc_client_dtor) {}

client::client(const options& options)
    : _client(mongoc_client_new(options._mongodb_uri.c_str()), mongoc_client_dtor) {}

class database client::database(const std::string& database_name) {
    return mongo::driver::database(*this, database_name);
}

class database client::operator[](const std::string& database_name) {
    return database(database_name);
}

}  // namespace driver
}  // namespace mongo

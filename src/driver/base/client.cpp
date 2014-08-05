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

#include "driver/base/client.hpp"

namespace mongo {
namespace driver {

    client::client(client&& rhs) {
        _client = rhs._client;
        rhs._client = NULL;
    }

    client& client::operator=(client&& rhs) {
        _client = rhs._client;
        rhs._client = NULL;
        return *this;
    }

    client::client(std::string uri) {
        _client = mongoc_client_new(uri.c_str());
    }

    client::~client() {
        mongoc_client_destroy(_client);
    }

    class database client::database(std::string database_name) {
        return mongo::driver::database(this, std::move(database_name));
    }

    class database client::operator[](std::string database_name) {
        return database(database_name);
    }

} // namespace driver
} // namespace mongo

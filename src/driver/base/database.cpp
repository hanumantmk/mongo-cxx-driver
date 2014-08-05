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

#include "driver/base/database.h"
#include "driver/base/client.h"

namespace mongo {
namespace driver {

    Database::Database( Client* client, std::string name) :
        _client(client), _name(name) {
        _database = mongoc_client_get_database(_client->_client, name.c_str());
    }

    Database::Database(Database&& rhs) {
        _database = rhs._database;
        _client = rhs._client;
        _name = std::move(rhs._name);
    }

    Database& Database::operator=(Database&& rhs) {
        _database = rhs._database;
        _client = rhs._client;
        _name = std::move(rhs._name);
        return *this;
    }

    Database::~Database() {
        mongoc_database_destroy(_database);
    }

    Collection Database::collection(std::string name) {
        return Collection(_client, this, std::move(name));
    }

    Collection Database::operator[](std::string name) {
        return collection(name);
    }

} // namespace driver
} // namespace mongo

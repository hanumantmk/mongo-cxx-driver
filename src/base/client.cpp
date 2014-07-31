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

#include "base/client.h"

namespace mongo {
namespace driver {

    Client::Client(Client&& rhs) {
        _client = rhs._client;
        rhs._client = NULL;
    }

    Client& Client::operator=(Client&& rhs) {
        _client = rhs._client;
        rhs._client = NULL;
        return *this;
    }

    Client::Client(std::string uri) {
        _client = mongoc_client_new(uri.c_str());
    }

    Client::~Client() {
        mongoc_client_destroy(_client);
    }

    Database Client::database(std::string db) {
        return Database(this, std::move(db));
    }

} // namespace driver
} // namespace mongo

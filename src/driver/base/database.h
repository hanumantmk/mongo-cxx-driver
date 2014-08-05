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

#include <string>

#include "mongoc.h"

#include "driver/base/collection.h"

namespace mongo {
namespace driver {

    class Client;
    class Collection;

    class Database {

        friend class Client;
        friend class Collection;

    public:
        Database(Database&& client);
        ~Database();

        Database& operator=(Database&& client);

        Collection collection(std::string name);
        Collection operator[](std::string name);

    private:
        Database(const Database& client) = delete;
        Database& operator=(const Database& client) = delete;

        Database(Client* client, std::string name);

        Client* _client;
        std::string _name;
        mongoc_database_t* _database;

    };

} // namespace driver
} // namespace mongo

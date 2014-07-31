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
#include "base/collection.h"

namespace mongo {
namespace driver {

    class Client;

    class Database {

        friend class Client;

    public:
        Collection collection(std::string name);
        Collection operator[](std::string name);

    private:
        Database(
            Client* client,
            std::string name
        ) : _client(client), _name(name) {}

        Client* _client;
        std::string _name;

    };

} // namespace driver
} // namespace mongo

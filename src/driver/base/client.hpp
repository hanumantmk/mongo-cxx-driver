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

#include "driver/config/header_prelude.hpp"

#include "driver/base/database.hpp"

namespace mongo {
namespace driver {

class options;

/**
 * The client class is the entrypoint into the MongoDB driver. It acts as a logical gateway for
 * accessing the databases of MongoDB clusters. Databases that are accessed via a client inherit
 * all of the options specified on the client.
 */
class MONGOCXX_EXPORT client {
    friend class database;
    friend class collection;

   public:
    client(options options);

    client(const client&) = delete;
    explicit client(client&& client);

    client& operator=(const client&) = delete;
    client& operator=(client&& client);

    ~client();

    class database operator[](std::string database_name);
    class database database(std::string database_name);

   private:
    mongoc_client_t* _client;
};

}  // namespace driver
}  // namespace mongo

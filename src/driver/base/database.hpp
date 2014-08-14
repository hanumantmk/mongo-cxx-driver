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

#include "driver/config/prelude.hpp"


#include <string>

#include "mongoc.h"

#include "driver/base/collection.hpp"

namespace mongo {
namespace driver {

class client;
class collection;

/**
 * The database class serves as a representation of a MongoDB database. It acts as a gateway
 * for accessing collections that are contained within the particular database that an instance
 * of
 * the class represents. It inherets all of its default settings from the client that calls it's
 * constructor.
 */
class MONGOCXX_EXPORT database {

    friend class client;
    friend class collection;

   public:
    database(const database&) = delete;
    database(database&& client);

    database& operator=(const database&) = delete;
    database& operator=(database&& client);

    ~database();


    class collection operator[](std::string collection_name);
    class collection collection(std::string collection_name);

   private:
    database(client* client, std::string name);

    client* _client;

    std::string _name;
    mongoc_database_t* _database;
};

}  // namespace driver
}  // namespace mongo

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

#include "driver/libmongoc.hpp"

#include "driver/base/database.hpp"
#include "driver/base/client.hpp"
#include "driver/private/cast.hpp"

namespace mongo {
namespace driver {

namespace {
static void mongoc_database_dtor(void* database_ptr) noexcept {
    mongoc_database_destroy(static_cast<mongoc_database_t*>(database_ptr));
}
}  // namespace

database::database(const client& client, const std::string& database_name)
    : _database(mongoc_client_get_database(util::cast<mongoc_client_t>(client._client),
                                           database_name.c_str()),
                mongoc_database_dtor) {}

collection database::collection(const std::string& collection_name) {
    return mongo::driver::collection(*this, collection_name);
}

collection database::operator[](const std::string& collection_name) {
    return collection(collection_name);
}

}  // namespace driver
}  // namespace mongo

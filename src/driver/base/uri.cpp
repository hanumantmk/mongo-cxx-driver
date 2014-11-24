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

#include "driver/libmongoc.hpp"

#include "driver/base/uri.hpp"
#include "driver/base/private/uri.hpp"

namespace mongo {
namespace driver {

uri::uri(uri&&) = default;
uri& uri::operator=(uri&&) = default;
uri::~uri() = default;

uri::uri(const std::string& uri_string)
    : _impl(new impl{mongoc_uri_new(uri_string.c_str())})
{}

const std::string uri::auth_mechanism() const {
    return mongoc_uri_get_auth_mechanism(_impl->uri_t);
}

const std::string uri::auth_source() const {
    return mongoc_uri_get_auth_source(_impl->uri_t);
}

const std::string uri::database() const {
    return mongoc_uri_get_database(_impl->uri_t);
}

const std::vector<host> uri::hosts() const {
    std::vector<host> result;

    const mongoc_host_list_t* host_list = mongoc_uri_get_hosts(_impl->uri_t);

    while (host_list) {
        result.push_back(
            host {
                host_list->host,
                host_list->port,
                host_list->family
            }
        );
        host_list = host_list->next;
    }

    return result;
}

const std::string uri::replica_set() const {
    return mongoc_uri_get_replica_set(_impl->uri_t);
}

bool uri::ssl() const {
    return mongoc_uri_get_ssl(_impl->uri_t);
}

const std::string uri::username() const {
    return mongoc_uri_get_username(_impl->uri_t);
}

const std::string uri::password() const {
    return mongoc_uri_get_password(_impl->uri_t);
}

}  // namespace driver
}  // namespace mongo

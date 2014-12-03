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

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "driver/libmongoc.hpp"

#include "driver/base/client.hpp"
#include "driver/base/uri.hpp"

using namespace mongo::driver;

TEST_CASE("A client connects to a provided mongodb uri", "[client][base]") {
    auto client_new = libmongoc::client_new_from_uri.create_instance();
    std::string expected_url("mongodb://mongodb.example.com:9999");
    uri mongodb_uri(expected_url);
    std::string actual_url{};
    bool called = false;

    client_new->interpose([&](const mongoc_uri_t* url) {
        called = true;
        actual_url = std::move(std::string(mongoc_uri_get_string(url)));
        return nullptr;
    });

    client{mongodb_uri};

    REQUIRE(called);
    REQUIRE(expected_url == actual_url);
}

TEST_CASE("A client cleans up its underlying mongoc client on destruction", "[client][base]") {
    auto client_new = libmongoc::client_new_from_uri.create_instance();
    auto client_destroy = libmongoc::client_destroy.create_instance();
    bool destroy_called = false;

    client_new->interpose([](const mongoc_uri_t* url) { return nullptr; });

    client_destroy->interpose([&](mongoc_client_t* client) { destroy_called = true; });

    {
        client object{};
        REQUIRE(!destroy_called);
    }

    REQUIRE(destroy_called);
}

TEST_CASE("A client supports move operations", "[client][base]") {
    auto client_new = libmongoc::client_new_from_uri.create_instance();
    auto client_destroy = libmongoc::client_destroy.create_instance();
    client_new->interpose([](const mongoc_uri_t*){return nullptr;}).forever();
    client_destroy->interpose([](mongoc_client_t*){}).forever();
    client a;

    bool called = false;
    client_new->interpose([&](const mongoc_uri_t* url) {
        called = true;
        return nullptr;
    });

    client b{std::move(a)};
    REQUIRE(!called);

    client c = std::move(b);
    REQUIRE(!called);
}

TEST_CASE("A client's read preferences may be set and obtained", "[client][base]") {
    auto client_new = libmongoc::client_new_from_uri.create_instance();
    client_new->interpose([](const mongoc_uri_t*){return nullptr;}).forever();
    auto client_destroy = libmongoc::client_destroy.create_instance();
    client_destroy->interpose([](mongoc_client_t*){}).forever();
    auto client_set_preference = libmongoc::client_set_read_prefs.create_instance();
    client_set_preference->interpose([](mongoc_client_t*, const mongoc_read_prefs_t*){}).forever();
    auto client_set_concern = libmongoc::client_set_write_concern.create_instance();
    client_set_concern->interpose([](mongoc_client_t*, const mongoc_write_concern_t*){}).forever();

    client mongo_client;
    read_preference preference{read_mode::k_secondary_preferred};

    bool called = false;
    client_set_preference->interpose(
        [&](mongoc_client_t* client, const mongoc_read_prefs_t* read_prefs) {
            called = true;
            REQUIRE(mongoc_read_prefs_get_mode(read_prefs) ==
                    static_cast<mongoc_read_mode_t>(read_mode::k_secondary_preferred));
        });
    mongo_client.read_preference(preference);
    REQUIRE(called);

    REQUIRE(preference.mode() == mongo_client.read_preference().mode());
}

TEST_CASE("A client's write concern may be set and obtained", "[client][base]") {
    auto client_new = libmongoc::client_new_from_uri.create_instance();
    client_new->interpose([](const mongoc_uri_t*){return nullptr;}).forever();
    auto client_destroy = libmongoc::client_destroy.create_instance();
    client_destroy->interpose([](mongoc_client_t*){}).forever();
    auto client_set_preference = libmongoc::client_set_read_prefs.create_instance();
    client_set_preference->interpose([](mongoc_client_t*, const mongoc_read_prefs_t*){}).forever();
    auto client_set_concern = libmongoc::client_set_write_concern.create_instance();
    client_set_concern->interpose([](mongoc_client_t*, const mongoc_write_concern_t*){}).forever();

    client mongo_client;
    write_concern concern{};
    concern.confirm_from(majority);

    bool called = false;
    client_set_concern->interpose([&](mongoc_client_t* client, const mongoc_write_concern_t* concern) {
        called = true;
        REQUIRE(mongoc_write_concern_get_wmajority(concern));
    });
    mongo_client.write_concern(concern);
    REQUIRE(called);

    REQUIRE(concern.confirm_from().majority() ==
            mongo_client.write_concern().confirm_from().majority());
}

TEST_CASE("A client can create a named database object", "[client][base]") {
    auto client_new = libmongoc::client_new_from_uri.create_instance();
    client_new->interpose([](const mongoc_uri_t*){return nullptr;}).forever();
    auto client_destroy = libmongoc::client_destroy.create_instance();
    client_destroy->interpose([](mongoc_client_t*){}).forever();
    auto client_set_preference = libmongoc::client_set_read_prefs.create_instance();
    client_set_preference->interpose([](mongoc_client_t*, const mongoc_read_prefs_t*){}).forever();
    auto client_set_concern = libmongoc::client_set_write_concern.create_instance();
    client_set_concern->interpose([](mongoc_client_t*, const mongoc_write_concern_t*){}).forever();

    auto database_get = libmongoc::client_get_database.create_instance();
    database_get->interpose([](mongoc_client_t*, const char*){return nullptr;}).forever();
    auto database_destroy = libmongoc::database_destroy.create_instance();
    database_destroy->interpose([](mongoc_database_t*){}).forever();
    auto database_set_preference = libmongoc::database_set_read_prefs.create_instance();
    database_set_preference->interpose([](mongoc_database_t*, const mongoc_read_prefs_t*){}).forever();
    auto database_set_concern = libmongoc::database_set_write_concern.create_instance();
    database_set_concern->interpose([](mongoc_database_t*, const mongoc_write_concern_t*){}).forever();

    const std::string name("database");

    client mongo_client;
    database obtained_database = mongo_client[name];
    REQUIRE(obtained_database.name() == name);
}

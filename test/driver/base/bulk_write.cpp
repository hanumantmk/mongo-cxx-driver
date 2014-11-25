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
#include "helpers.hpp"

#include "bson/builder.hpp"
#include "bson/types.hpp"

#include "driver/libmongoc.hpp"
#include "driver/base/bulk_write.hpp"
#include "driver/base/write_concern.hpp"

using namespace mongo::driver;

TEST_CASE("a bulk_write will setup a mongoc bulk operation", "[bulk_write][base]") {
    auto construct = libmongoc::bulk_operation_new.create_instance();
    bool construct_called = false;
    bool ordered_value = false;
    construct->visit([&](bool ordered) {
        construct_called = true;
        ordered_value = ordered;
    });

    SECTION("with an ordered bulk write") {
        bulk_write(true);
        REQUIRE(construct_called);
        REQUIRE(ordered_value);
    }

    SECTION("with an unordered bulk write") {
        bulk_write(false);
        REQUIRE(construct_called);
        REQUIRE(!ordered_value);
    }

}
TEST_CASE("the destruction of a bulk_write will destroy the mongoc operation", "[bulk_write][base]") {
    auto destruct = libmongoc::bulk_operation_destroy.create_instance();
    bool destruct_called = false;
    destruct->visit([&destruct_called]() {
        destruct_called = true;
    });
    bulk_write(true);
    REQUIRE(destruct_called);
}

TEST_CASE("bulk_write has a write_concern", "[bulk_write][base]") {
    bulk_write bw(true);
    CHECK_OPTIONAL_ARGUMENT_WITHOUT_EQUALITY(bw, write_concern, write_concern());
}

TEST_CASE("passing write operations to append calls the corresponding C function", "[bulk_write][base]") {
    bulk_write bw(true);

    SECTION("insert_one invokes mongoc_bulk_operation_insert") {
        bson::builder::document b1;

        b1 << "_id" << 1;
        auto bulk_insert = libmongoc::bulk_operation_insert.create_instance();
        bool bulk_insert_called = false;
        bulk_insert->visit([&bulk_insert_called]() {
            bulk_insert_called = true;
        });

        bw.append(model::insert_one(b1.view()));
        REQUIRE(bulk_insert_called);
    }
}

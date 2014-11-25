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

TEST_CASE("passing valid write operations to append calls the corresponding C function", "[bulk_write][base]") {
    //auto construct = libmongoc::bulk_operation_new.create_instance();
    //construct.interpose
    bulk_write bw(true);
    bson::builder::document filter_builder, doc_builder;
    filter_builder << "_id" << 1;
    doc_builder << "_id" << 2;
    bson::document::view filter = filter_builder.view();
    bson::document::view doc = doc_builder.view();
    const uint8_t* filter_buffer = nullptr;
    const uint8_t* doc_buffer = nullptr;
    bool upsert_value = false;

    SECTION("insert_one invokes mongoc_bulk_operation_insert") {
        auto bulk_insert = libmongoc::bulk_operation_insert.create_instance();
        bool bulk_insert_called = false;
        bulk_insert->visit([&](
                    mongoc_bulk_operation_t* bulk,
                    const bson_t* document) {
            bulk_insert_called = true;
            doc_buffer = bson_get_data(document);
        });

        bw.append(model::insert_one(doc));
        REQUIRE(bulk_insert_called);
        REQUIRE(doc_buffer == doc.get_buf());
    }

    SECTION("update_one invokes mongoc_bulk_operation_update_one") {
        auto bulk_insert = libmongoc::bulk_operation_update_one.create_instance();
        bool bulk_update_one_called = false;
        bulk_insert->visit([&](
                    mongoc_bulk_operation_t* bulk,
                    const bson_t* filter,
                    const bson_t* update,
                    bool upsert) {
            bulk_update_one_called = true;
            filter_buffer = bson_get_data(filter);
            doc_buffer = bson_get_data(update);
            upsert_value = upsert;
        });

        bw.append(model::update_one(filter, doc));
        REQUIRE(bulk_update_one_called);
        REQUIRE(filter_buffer == filter.get_buf());
        REQUIRE(doc_buffer == doc.get_buf());
        REQUIRE(!upsert_value);
    }

    SECTION("update_one with upsert invokes mongoc_bulk_operation_update_one with upsert true") {
        auto bulk_insert = libmongoc::bulk_operation_update_one.create_instance();
        bool bulk_update_one_called = false;
        bulk_insert->visit([&](
                    mongoc_bulk_operation_t* bulk,
                    const bson_t* filter,
                    const bson_t* update,
                    bool upsert) {
            bulk_update_one_called = true;
            filter_buffer = bson_get_data(filter);
            doc_buffer = bson_get_data(update);
            upsert_value = upsert;
        });

        model::update_one uo(filter, doc);
        uo.upsert(true);
        bw.append(uo);
        REQUIRE(bulk_update_one_called);
        REQUIRE(filter_buffer == filter.get_buf());
        REQUIRE(doc_buffer == doc.get_buf());
        REQUIRE(upsert_value);
    }

    SECTION("update_many invokes mongoc_bulk_operation_update") {
        auto bulk_insert = libmongoc::bulk_operation_update.create_instance();
        bool bulk_update_called = false;
        bulk_insert->visit([&](
                    mongoc_bulk_operation_t* bulk,
                    const bson_t* filter,
                    const bson_t* update,
                    bool upsert) {
            bulk_update_called = true;
            filter_buffer = bson_get_data(filter);
            doc_buffer = bson_get_data(update);
            upsert_value = upsert;
        });

        bw.append(model::update_many(filter, doc));
        REQUIRE(bulk_update_called);
        REQUIRE(filter_buffer == filter.get_buf());
        REQUIRE(doc_buffer == doc.get_buf());
        REQUIRE(!upsert_value);
    }

    SECTION("update_many with upsert invokes mongoc_bulk_operation_update with upsert true") {
        auto bulk_insert = libmongoc::bulk_operation_update.create_instance();
        bool bulk_update_called = false;
        bulk_insert->visit([&](
                    mongoc_bulk_operation_t* bulk,
                    const bson_t* filter,
                    const bson_t* update,
                    bool upsert) {
            bulk_update_called = true;
            filter_buffer = bson_get_data(filter);
            doc_buffer = bson_get_data(update);
            upsert_value = upsert;
        });

        model::update_many um(filter, doc);
        um.upsert(true);
        bw.append(um);
        REQUIRE(bulk_update_called);
        REQUIRE(filter_buffer == filter.get_buf());
        REQUIRE(doc_buffer == doc.get_buf());
        REQUIRE(upsert_value);
    }

    SECTION("delete_one invokes mongoc_bulk_operation_remove_one") {
        auto bulk_insert = libmongoc::bulk_operation_remove_one.create_instance();
        bool bulk_remove_one_called = false;
        bulk_insert->visit([&](
                    mongoc_bulk_operation_t* bulk,
                    const bson_t* filter) {
            bulk_remove_one_called = true;
            filter_buffer = bson_get_data(filter);
        });

        bw.append(model::delete_one(filter));
        REQUIRE(bulk_remove_one_called);
        REQUIRE(filter_buffer == filter.get_buf());
    }

    SECTION("delete_many invokes mongoc_bulk_operation_remove") {
        auto bulk_insert = libmongoc::bulk_operation_remove.create_instance();
        bool bulk_remove_called = false;
        bulk_insert->visit([&](
                    mongoc_bulk_operation_t* bulk,
                    const bson_t* filter) {
            bulk_remove_called = true;
            filter_buffer = bson_get_data(filter);
        });

        bw.append(model::delete_many(filter));
        REQUIRE(bulk_remove_called);
        REQUIRE(filter_buffer == filter.get_buf());
    }

    SECTION("replace_one invokes mongoc_bulk_operation_replace_one") {
        auto bulk_insert = libmongoc::bulk_operation_replace_one.create_instance();
        bool bulk_replace_one_called = false;
        bulk_insert->visit([&](
                    mongoc_bulk_operation_t* bulk,
                    const bson_t* filter,
                    const bson_t* replace,
                    bool upsert) {
            bulk_replace_one_called = true;
            filter_buffer = bson_get_data(filter);
            doc_buffer = bson_get_data(replace);
            upsert_value = upsert;
        });

        bw.append(model::replace_one(filter, doc));
        REQUIRE(bulk_replace_one_called);
        REQUIRE(filter_buffer == filter.get_buf());
        REQUIRE(doc_buffer == doc.get_buf());
        REQUIRE(!upsert_value);
    }

    SECTION("replace_one with upsert invokes mongoc_bulk_operation_replace_one with upsert true") {
        auto bulk_insert = libmongoc::bulk_operation_replace_one.create_instance();
        bool bulk_replace_one_called = false;
        bulk_insert->visit([&](
                    mongoc_bulk_operation_t* bulk,
                    const bson_t* filter,
                    const bson_t* replace,
                    bool upsert) {
            bulk_replace_one_called = true;
            filter_buffer = bson_get_data(filter);
            doc_buffer = bson_get_data(replace);
            upsert_value = upsert;
        });

        model::replace_one ro(filter, doc);
        ro.upsert(true);
        bw.append(ro);
        REQUIRE(bulk_replace_one_called);
        REQUIRE(filter_buffer == filter.get_buf());
        REQUIRE(doc_buffer == doc.get_buf());
        REQUIRE(upsert_value);
    }
}

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

#include "driver/base/write_concern.hpp"

using namespace mongo::driver;

TEST_CASE("a default write_concern", "[write_concern][base]") {
    write_concern wc{};

    SECTION("doesn't require the server to fsync") { REQUIRE(wc.fsync() == false); }

    SECTION("doesn't require the server to journal") { REQUIRE(wc.journal() == false); }

    SECTION("will not timeout") {
        auto timeout = wc.timeout();
        REQUIRE(timeout == decltype(timeout)::zero());
    }

    SECTION("will require confirmation from just the primary or standalone mongod") {
        REQUIRE(1 == wc.confirm_from().number().value());
    }

    SECTION("has empty tag set") { REQUIRE(!wc.confirm_from().tag()); }
}

TEST_CASE("write_concern fields may be set and retrieved", "[write_concern][base]") {
    write_concern wc{};

    SECTION("fsync may be configured") {
        wc.fsync(true);
        REQUIRE(wc.fsync() == true);
    }

    SECTION("journal may be configured") {
        wc.journal(true);
        REQUIRE(wc.journal() == true);
    }

    SECTION("timeout may be configured") {
        wc.timeout(std::chrono::seconds(10));
        REQUIRE(wc.timeout() == std::chrono::seconds(10));
        wc.timeout(std::chrono::milliseconds(250));
        REQUIRE(wc.timeout() == std::chrono::milliseconds(250));
    }

    SECTION("a tag may be set") {
        const std::string tag{"MultipleDC"};
        wc.confirm_from(tag);
        REQUIRE(tag == wc.confirm_from().tag().value());
    }

    SECTION("the number of nodes requiring confirmation may be set to a number") {
        wc.confirm_from(10);
        REQUIRE(wc.confirm_from().number().value() == 10);
    }

    SECTION("the number of nodes requiring confirmation may be set to the majority") {
        wc.confirm_from(majority);
        REQUIRE(wc.confirm_from().majority());
    }

    SECTION("the number of nodes requring confirmation may not be negative") {
        write_concern wc{};
        REQUIRE_THROWS_AS(wc.confirm_from(-20), std::invalid_argument);
    }
}

TEST_CASE("confirmation from tags, a repl-member count, and majority are mutually exclusive",
          "[write_concern][base]") {
    SECTION("setting the confirmation number unsets the confirmation tag") {
        write_concern wc{};
        wc.confirm_from("MultipleDC");
        wc.confirm_from(10);
        REQUIRE(!wc.confirm_from().tag());
    }
    SECTION("setting the confirmation number unsets majority") {
        write_concern wc{};
        wc.confirm_from(majority);
        wc.confirm_from(10);
        REQUIRE(!wc.confirm_from().majority());
    }

    SECTION("setting the tag unsets the confirmation number") {
        write_concern wc{};
        wc.confirm_from(10);
        wc.confirm_from("MultipleDC");
        REQUIRE(!wc.confirm_from().number());
    }

    SECTION("setting the tag unsets majority") {
        write_concern wc{};
        wc.confirm_from(majority);
        wc.confirm_from("MultipleDC");
        REQUIRE(!wc.confirm_from().majority());
    }

    SECTION("setting the majority unsets the confirmation number") {
        write_concern wc{};
        wc.confirm_from(10);
        wc.confirm_from(majority);
        REQUIRE(!wc.confirm_from().number());
    }

    SECTION("setting majority unsets the tag") {
        write_concern wc{};
        wc.confirm_from("MultipleDC");
        wc.confirm_from(majority);
        REQUIRE(!wc.confirm_from().tag());
    }
}

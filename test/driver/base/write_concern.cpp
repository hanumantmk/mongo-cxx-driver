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

#include "mongocxx.hpp"

using namespace mongo::driver;

TEST_CASE("a default write_concern", "[write_concern][base]") {
    write_concern wc{};

    SECTION("doesn't require the server to fsync") {
        REQUIRE(wc.fsync() == false);
    }

    SECTION("doesn't require the server to journal") {
        REQUIRE(wc.journal() == false);
    }

    SECTION("will not timeout") {
        REQUIRE(wc.timeout() == 0);
    }

    SECTION("will require confirmation from just the primary or standalone mongod") {
        REQUIRE(wc.confirm_from() == 1);
    }

    SECTION("has empty tag set") {
        REQUIRE(wc.tag().empty() == true);
    }
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
        wc.timeout(100);
        REQUIRE(wc.timeout() == 100);
    }

    SECTION("a tag may be set") {
        const std::string tag{"MultipleDC"};
        wc.tag(tag);
        REQUIRE(wc.tag() == tag);
    }

    SECTION("the number of nodes requiring confirmation may be set to a number") {
        wc.confirm_from(10);
        REQUIRE(wc.confirm_from() == 10);
    }

    SECTION("the number of nodes requiring confirmation may be set to the majority") {
        wc.confirm_from(write_concern::MAJORITY);
        REQUIRE(wc.confirm_from() == write_concern::MAJORITY);
    }
}

TEST_CASE("confirmation from tags, a repl-member count, and majority are mutually exclusive",
          "[write_concern][base]") {

    SECTION("setting the confirmation number unsets the confirmation tag") {
        write_concern wc{};
        wc.tag("MultipleDC");
        wc.confirm_from(10);
        REQUIRE(wc.tag().empty() == true);
    }
    SECTION("setting the confirmation number unsets majority") {
        write_concern wc{};
        wc.confirm_from(write_concern::MAJORITY);
        wc.confirm_from(10);
        REQUIRE(wc.confirm_from() != write_concern::MAJORITY);
    }

    SECTION("setting the tag unsets the confirmation number") {
        write_concern wc{};
        wc.confirm_from(10);
        wc.tag("MultipleDC");
        REQUIRE(wc.confirm_from() == write_concern::TAG);
    }

    SECTION("it is impossible to set confirm_from to the special value indicating a tag") {
        write_concern wc{};
        REQUIRE_THROWS_AS(wc.confirm_from(write_concern::TAG), std::invalid_argument);
    }

    SECTION("setting the tag unsets majority") {
        write_concern wc{};
        wc.confirm_from(write_concern::MAJORITY);
        wc.tag("MultipleDC");
        REQUIRE(wc.confirm_from() != write_concern::MAJORITY);
    }

    SECTION("setting the majority unsets the confirmation number") {
        write_concern wc{};
        wc.confirm_from(10);
        wc.confirm_from(write_concern::MAJORITY);
        REQUIRE(wc.confirm_from() == write_concern::MAJORITY);
    }

    SECTION("setting majority unsets the tag") {
        write_concern wc{};
        wc.tag("MultipleDC");
        wc.confirm_from(write_concern::MAJORITY);
        REQUIRE(wc.tag().empty());
    }

}

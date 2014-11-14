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

TEST_CASE("Create a default write_concern", "[write_concern][base]") {
    write_concern wc{};

    SECTION("has fsync enabled") {
        REQUIRE(wc.fsync() == false);
    }

    SECTION("has journal enabled") {
        REQUIRE(wc.journal() == false);
    }

    SECTION("has w:1") {
        REQUIRE(wc.w() == 1);
    }

    SECTION("has wtimeout: 0") {
        REQUIRE(wc.wtimeout() == 0);
    }

    SECTION("has empty wtag") {
        REQUIRE(wc.wtag().empty() == true);
    }
}

TEST_CASE("write_concern's fields may be set through a fluent api", "[write_concern][base]") {
    write_concern wc{};

    SECTION("fsync may be set fluently") {
        write_concern wc2 = wc;
        REQUIRE(&wc2 == &wc2.fsync(true));
        REQUIRE(wc2.fsync() == true);
    }

    SECTION("journal may be set fluently") {
        write_concern wc2 = wc;
        REQUIRE(&wc2 == &wc2.journal(true));
        REQUIRE(wc2.journal() == true);
    }

    SECTION("w may be set fluently") {
        write_concern wc2 = wc;
        REQUIRE(&wc2 == &wc2.w(10));
        REQUIRE(wc2.w() == 10);
    }

    SECTION("wtimeout may be set fluently") {
        write_concern wc2 = wc;
        REQUIRE(&wc2 == &wc2.wtimeout(100));
        REQUIRE(wc2.wtimeout() == 100);
    }

    SECTION("wtag may be set fluently") {
        write_concern wc2 = wc;
        REQUIRE(&wc2 == &wc2.wtag("disk:SSD"));
        REQUIRE(wc2.wtag() == "disk:SSD");
    }
}

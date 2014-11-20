#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "mongocxx.hpp"

using namespace mongo::driver;

TEST_CASE("update_many", "[update_many][model]") {
    const bson::document::view a((std::uint8_t *)"", 0);
    const bson::document::view b((std::uint8_t *)"", 0);

    model::update_many um(a, b);

    SECTION("stores required arguments") {
        REQUIRE(um.filter().get_buf() == a.get_buf());
        REQUIRE(um.update().get_buf() == b.get_buf());
    }

    SECTION("has upsert disengaged") {
        REQUIRE(um.upsert().operator bool() == false);
    }

    SECTION("has a fluent method to set the upsert") {
        REQUIRE(&um == &um.upsert(true));
        REQUIRE(static_cast<bool>(um.upsert()) == true);
        REQUIRE(um.upsert().value() == true);
    }
}

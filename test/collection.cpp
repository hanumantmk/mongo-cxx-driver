#include "catch.hpp"

#include "bson/builder.hpp"
#include "mongocxx.hpp"

using namespace mongo::driver;

TEST_CASE("CRUD functionality", "[driver::collection]") {

    mongoc_init();
    client mongodb_client;
    database db = mongodb_client["test"];
    collection coll = db["mongo-cxx-driver"];

    SECTION("insert and read single document", "[collection]") {
        bson::builder b;
        b << "_id" << bson::oid{}
          << "x" << 1;

        result::insert_one result = coll.insert_one(b.view());

        REQUIRE(result.is_acknowledged == true);
        //REQUIRE(result.inserted_id.type() == bson::type::k_oid);

        auto cursor = coll.find(b.view());

        std::size_t i = 0;
        for (auto&& x: cursor) {
            REQUIRE(x["_id"].get_oid().value == b.view()["_id"].get_oid().value);
            i++;
        }

        REQUIRE(i == 1);
    }

    SECTION("insert and read multiple documents", "[collection]") {
        bson::builder b;
        b << "_id" << bson::oid{}
          << "x" << 1;
    }
}

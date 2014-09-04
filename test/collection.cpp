#include "catch.hpp"

#include "bson/builder.hpp"
#include "mongocxx.hpp"

using namespace mongo::driver;

TEST_CASE("collection CRUD functionality", "[driver::collection]") {

    mongoc_init();
    client mongodb_client;
    database db = mongodb_client["test"];
    collection coll = db["mongo-cxx-driver"];

    SECTION("insert and read single document", "[collection]") {
        bson::builder b;
        b << "x" << 1;

        model::insert_one single = model::insert_one(b.view());
        result::insert_one result = coll.insert_one(single);

        REQUIRE(result.is_acknowledged == true);
        REQUIRE(result.inserted_id.type() == bson::type::k_oid);
    }
}

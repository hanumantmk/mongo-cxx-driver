#include "catch.hpp"

#include "bson/builder.hpp"
#include "mongocxx.hpp"

using namespace mongo::driver;

TEST_CASE("CRUD functionality", "[driver::collection]") {

    mongoc_init();
    client mongodb_client;
    database db = mongodb_client["test"];
    collection coll = db["mongo-cxx-driver"];
    coll.drop();

    SECTION("insert and read single document", "[collection]") {
        bson::builder::document b;
        b << "_id" << bson::oid{bson::oid::init_tag} << "x" << 1;

        result::insert_one result = coll.insert_one(b.view());

        REQUIRE(result.is_acknowledged == true);
        // REQUIRE(result.inserted_id.type() == bson::type::k_oid);

        auto cursor = coll.find(b.view());

        std::size_t i = 0;
        for (auto&& x : cursor) {
            REQUIRE(x["_id"].get_oid().value == b.view()["_id"].get_oid().value);
            i++;
        }

        REQUIRE(i == 1);
    }

    SECTION("insert and read multiple documents", "[collection]") {
        bson::builder::document b1, b2;

        b1 << "_id" << 1;
        b2 << "_id" << 2;

        std::vector<bson::document::view> inserts{b1, b2};
        result::insert_many result = coll.insert_many(inserts);

        REQUIRE(result.is_acknowledged == true);

        auto cursor = coll.find();

        std::int32_t sum = 0;
        for (auto&& doc : cursor) {
            sum += doc["_id"].get_int32();
        }

        REQUIRE(sum == 3);
    }

    SECTION("insert and update single document", "[collection]") {
        using namespace bson::builder::helpers;
        bson::builder::document b1;
        b1 << "_id" << 1;

        coll.insert_one(b1.view());

        auto doc = coll.find_one();
        REQUIRE(doc);
        REQUIRE(doc->view()["_id"].get_int32() == 1);

        bson::builder::document update_doc;
        update_doc << "$set" << open_doc << "changed" << true << close_doc;

        coll.update_one(model::update_one(b1, update_doc));

        auto updated = coll.find_one();
        REQUIRE(updated);
        REQUIRE(updated->view()["changed"].get_bool() == true);
    }

    SECTION("non-matching upsert creates document", "[collection]") {
        using namespace bson::builder::helpers;
        bson::builder::document b1;
        b1 << "_id" << 1;

        bson::builder::document update_doc;
        update_doc << "$set" << open_doc << "changed" << true << close_doc;

        coll.update_one(model::update_one(b1, update_doc).upsert(true));

        auto updated = coll.find_one();
        REQUIRE(updated);
        REQUIRE(updated->view()["changed"].get_bool() == true);
        REQUIRE(coll.count() == 1);
    }

    SECTION("matching upsert updates document", "[collection]") {
        using namespace bson::builder::helpers;
        bson::builder::document b1;
        b1 << "_id" << 1;

        coll.insert_one(b1.view());

        bson::builder::document update_doc;
        update_doc << "$set" << open_doc << "changed" << true << close_doc;

        coll.update_one(model::update_one(b1, update_doc).upsert(true));

        auto updated = coll.find_one();
        REQUIRE(updated);
        REQUIRE(updated->view()["changed"].get_bool() == true);
        REQUIRE(coll.count() == 1);
    }

    SECTION("matching upsert updates document", "[collection]") {
        bson::builder::document b1;
        b1 << "x" << 1;
        model::insert_many docs{std::initializer_list<bson::document::view>{b1, b1, b1}};
        coll.insert_many(docs);

        coll.insert_one(bson::document::view{});
        REQUIRE(coll.count(b1.view()) == 3);
        REQUIRE(coll.count() == 4);
    }

    SECTION("document replacement", "[collection]") {
        bson::builder::document b1;
        b1 << "x" << 1;
        coll.insert_one(b1.view());

        bson::builder::document b2;
        b2 << "x" << 2;

        coll.replace_one(model::replace_one(b1, b2));

        auto replaced = coll.find_one(b2.view());

        REQUIRE(replaced);
        REQUIRE(coll.count() == 1);
    }

    SECTION("filtered document remove one works", "[collection]") {
        bson::builder::document b1;
        b1 << "x" << 1;

        coll.insert_one(b1.view());

        bson::builder::document b2;
        b2 << "x" << 2;

        coll.insert_one(b2.view());
        coll.insert_one(b2.view());

        REQUIRE(coll.count() == 3);

        coll.remove_one(b2.view());

        REQUIRE(coll.count() == 2);

        auto cursor = coll.find();

        unsigned seen = 0;
        for (auto&& x : cursor) {
            seen |= x["x"].get_int32();
        }

        REQUIRE(seen == 3);

        coll.remove_one(b2.view());

        REQUIRE(coll.count() == 1);

        cursor = coll.find();

        seen = 0;
        for (auto&& x : cursor) {
            seen |= x["x"].get_int32();
        }

        REQUIRE(seen == 1);

        coll.remove_one(b2.view());

        REQUIRE(coll.count() == 1);

        cursor = coll.find();

        seen = 0;
        for (auto&& x : cursor) {
            seen |= x["x"].get_int32();
        }

        REQUIRE(seen == 1);
    }

    SECTION("remove many works", "[collection]") {
        bson::builder::document b1;
        b1 << "x" << 1;

        coll.insert_one(b1.view());

        bson::builder::document b2;
        b2 << "x" << 2;

        coll.insert_one(b2.view());
        coll.insert_one(b2.view());

        REQUIRE(coll.count() == 3);

        coll.remove_many(b2.view());

        REQUIRE(coll.count() == 1);

        auto cursor = coll.find();

        unsigned seen = 0;
        for (auto&& x : cursor) {
            seen |= x["x"].get_int32();
        }

        REQUIRE(seen == 1);

        coll.remove_many(b2.view());

        REQUIRE(coll.count() == 1);

        cursor = coll.find();

        seen = 0;
        for (auto&& x : cursor) {
            seen |= x["x"].get_int32();
        }

        REQUIRE(seen == 1);
    }

    SECTION("find_one_and_replace works", "[collection]") {
        bson::builder::document b1;
        b1 << "x" << 1;

        coll.insert_one(b1.view());
        coll.insert_one(b1.view());

        REQUIRE(coll.count() == 2);

        bson::builder::document criteria;
        bson::builder::document replacement;

        criteria << "x" << 1;
        replacement << "x" << 2;

        SECTION("without return replacement returns original") {
            auto doc =
                coll.find_one_and_replace(model::find_one_and_replace{criteria, replacement});

            REQUIRE(doc);

            REQUIRE(doc->view()["x"].get_int32() == 1);
        }

        SECTION("with return replacement returns new") {
            auto doc = coll.find_one_and_replace(
                model::find_one_and_replace { criteria, replacement }.return_replacement(true));

            REQUIRE(doc);
            REQUIRE(doc->view()["x"].get_int32() == 2);
        }

        SECTION("bad criteria returns negative optional") {
            bson::builder::document bad_criteria;
            bad_criteria << "x" << 3;

            auto doc =
                coll.find_one_and_replace(model::find_one_and_replace{bad_criteria, replacement});

            REQUIRE(!doc);
        }
    }

    SECTION("find_one_and_update works", "[collection]") {
        using namespace bson::builder::helpers;

        bson::builder::document b1;
        b1 << "x" << 1;

        coll.insert_one(b1.view());
        coll.insert_one(b1.view());

        REQUIRE(coll.count() == 2);

        bson::builder::document criteria;
        bson::builder::document update;

        criteria << "x" << 1;
        update << "$set" << open_doc << "x" << 2 << close_doc;

        SECTION("without return update returns original") {
            auto doc = coll.find_one_and_update(model::find_one_and_update{criteria, update});

            REQUIRE(doc);

            REQUIRE(doc->view()["x"].get_int32() == 1);
        }

        SECTION("with return update returns new") {
            auto doc = coll.find_one_and_update(
                model::find_one_and_update { criteria, update }.return_replacement(true));

            REQUIRE(doc);
            REQUIRE(doc->view()["x"].get_int32() == 2);
        }

        SECTION("bad criteria returns negative optional") {
            bson::builder::document bad_criteria;
            bad_criteria << "x" << 3;

            auto doc = coll.find_one_and_update(model::find_one_and_update{bad_criteria, update});

            REQUIRE(!doc);
        }
    }

    SECTION("find_one_and_remove works", "[collection]") {
        using namespace bson::builder::helpers;

        bson::builder::document b1;
        b1 << "x" << 1;

        coll.insert_one(b1.view());
        coll.insert_one(b1.view());

        REQUIRE(coll.count() == 2);

        bson::builder::document criteria;

        criteria << "x" << 1;

        SECTION("remove one removes one and returns it") {
            auto doc = coll.find_one_and_remove(model::find_one_and_remove{criteria});

            REQUIRE(doc);

            REQUIRE(doc->view()["x"].get_int32() == 1);
            REQUIRE(coll.count() == 1);
        }
    }

    SECTION("aggregate some shit", "[collection]") {
        bson::builder::document b1;
        b1 << "x" << 1;

        bson::builder::document b2;
        b2 << "x" << 2;

        coll.insert_one(b1.view());
        coll.insert_one(b2.view());
        coll.insert_one(b2.view());

        pipeline p;
        p.match(b1.view());

        model::aggregate aggregation(std::move(p));
        auto results = coll.aggregate(aggregation);
    }
}

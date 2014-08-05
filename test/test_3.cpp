#include "mongoc.h"
#include <iostream>
#include <memory>
#include <cstring>
#include <vector>

#include "bson/document.h"
#include "driver/base/client.h"
#include "driver/base/database.h"
#include "driver/base/collection.h"
#include "driver/base/cursor.h"
#include "driver/model/bulk.h"
#include "driver/model/find.h"
#include "driver/model/insert.h"
#include "driver/request/insert.h"
#include "driver/result/write.h"
#include "driver/util/adapter.h"

using namespace mongo::driver;

int main() {
    mongoc_init();

    bson_t * foo = bson_new();

    bson::Document::View doc(bson_get_data(foo), foo->len);

    Client client("mongodb://localhost");
    Collection col(client["test"]["test"]);

    col.drop();

    bson_t bson;
    bson_init(&bson);
    for (int i = 0; i < 10; i++) {
        bson_reinit(&bson);

        BSON_APPEND_INT32(&bson, "foo", i);
    }

/*
 *        std::cout << "individual write is: " << col.insert(InsertModel(bson::Document::View(bson_get_data(&bson), bson.len))) << std::endl;
 *    }
 *    bson_destroy(&bson);
 *
 *    std::vector<InsertRequest> requests;
 *
 *    bson_t bsons[10];
 *
 *    for (int i = 0; i < 10; i++) {
 *        bson_init(bsons + i);
 *
 *        BSON_APPEND_INT32(bsons + i, "foo", i + 10);
 *
 *        requests.emplace_back(bson::Document::View(bson_get_data(bsons + i), bsons[i].len));
 *    }
 *
 *    std::cout << "bulk write is: " << col.bulk_write(make_bulk_write_model(requests, false)) << std::endl;
 *
 *    for (int i = 0; i < 10; i++) {
 *        bson_destroy(bsons + i);
 *    }
 *
 *    bson_init(&bson);
 *    for (int i = 0; i < 10; i++) {
 *        bson_t child;
 *        bson_append_document_begin(&bson, "-", 1, &child);
 *        BSON_APPEND_INT32(&child, "foo", i + 20);
 *        bson_append_document_end(&bson, &child);
 *    }
 *    bson::Document::View bson_array(bson_get_data(&bson), bson.len);
 *
 *    auto adapter = make_adapter(&bson_array, [] (const bson::Reference& ref) {
 *         return InsertRequest(ref.getDocument());
 *    });
 *
 *    std::cout << "bulk write w/ adapter is: " << col.bulk_write(make_bulk_write_model(adapter, false)) << std::endl;
 *
 *    Cursor cursor(col.find(FindModel(doc)));
 *
 *    for (auto x : cursor) {
 *        std::cout << "bson is: " << x["foo"].getInt32() << std::endl;
 *    }
 */

            /*
    for (; x != col.end(); ++x) {
        std::cout << "bson is: " << *x << std::endl;
    }
    */

    bson_destroy(foo);

    mongoc_cleanup();
    return 0;
}

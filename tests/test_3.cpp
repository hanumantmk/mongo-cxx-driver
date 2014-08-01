#include "mongoc.h"
#include <iostream>
#include <memory>
#include <cstring>

#include "bson/document.h"
#include "base/client.h"
#include "base/database.h"
#include "base/collection.h"
#include "base/cursor.h"
#include "models/bulk.h"
#include "models/find.h"
#include "models/insert.h"
#include "models/insert_request.h"
#include "results/write.h"

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

        std::cout << "individual write is: " << col.insert(InsertModel(bson::Document::View(bson_get_data(&bson), bson.len))) << std::endl;
    }
    bson_destroy(&bson);

    std::vector<WriteRequest*> requests;

    bson_t bsons[10];

    for (int i = 0; i < 10; i++) {
        bson_init(bsons + i);

        BSON_APPEND_INT32(bsons + i, "foo", i + 10);

        requests.push_back(new InsertRequest(bson::Document::View(bson_get_data(bsons + i), bsons[i].len)));
    }

    std::cout << "bulk write is: " << col.bulk_write( BulkWriteModel<decltype(requests)>(requests, false)) << std::endl;

    for (int i = 0; i < 10; i++) {
        bson_destroy(bsons + i);
    }

    Cursor cursor(col.find(FindModel(doc)));

    for (auto x : cursor) {
        std::cout << "bson is: " << x["foo"].getInt32() << std::endl;
    }

            /*
    for (; x != col.end(); ++x) {
        std::cout << "bson is: " << *x << std::endl;
    }
    */

    bson_destroy(foo);

    mongoc_cleanup();
    return 0;
}

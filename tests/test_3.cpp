#include "mongoc.h"
#include <iostream>
#include <memory>
#include <cstring>

#include "bson/document.h"
#include "base/client.h"
#include "base/database.h"
#include "base/collection.h"
#include "base/cursor.h"
#include "models/find.h"

using namespace mongo::driver;

int main() {
    mongoc_init();

    bson_t * foo = bson_new();

    bson::Document doc(bson_get_data(foo), foo->len);

    Client client("mongodb://localhost");
    Collection col(client["test"]["test"]);
    Cursor cursor(col.find(FindModel(doc)));

    for (auto x : cursor) {
        std::cout << "bson is: " << x["hello"].getString() << std::endl;
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

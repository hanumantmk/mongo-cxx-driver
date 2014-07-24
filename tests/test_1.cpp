#include "mongoc.h"
#include <iostream>
#include <memory>
#include <cstring>

#include "bson/document.h"

int main(int argc, char ** argv) {
    mongoc_init();

    bson_t * foo = BCON_NEW(
        "hello", "world",
        "bar", BCON_INT32(10)
    );

    bson::Document doc(bson_get_data(foo), foo->len);

    for (auto x : doc) {
        std::cout << "type is: " << (int)(x.type()) << std::endl;
    }

    std::cout << "type is: " << (int)(doc["bar"].type()) << std::endl;

    bson_destroy(foo);

    mongoc_cleanup();
    return 0;
}

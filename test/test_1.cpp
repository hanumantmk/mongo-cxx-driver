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

    bson::Document::View doc(bson_get_data(foo), foo->len);

    std::cout << "Doc: " << doc << std::endl;

    for (auto x : doc) {
        std::cout << "type is: " << (int)(x.type()) << std::endl;
        std::cout << "value is: ";
        
        if (x.type() == bson::Type::INT32 ) {
            std::cout << x.getInt32();
        } else {
            std::cout << x.getString();
        }

        std::cout << std::endl;
    }

    std::cout << "key: " << doc["hello"].key() << std::endl;

    bson_destroy(foo);

    mongoc_cleanup();
    return 0;
}

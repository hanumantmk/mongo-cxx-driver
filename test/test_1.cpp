#include <iostream>
#include <memory>
#include <cstring>

#include "mongoc.h"
#include "bson/document.hpp"

int main() {
    mongoc_init();

    bson_t* foo = BCON_NEW("hello", "world", "bar", BCON_INT32(10));

    bson::document::view doc(bson_get_data(foo), foo->len);

    std::cout << "Doc: " << doc << std::endl;

    for (auto x : doc) {
        std::cout << "type is: " << (int)(x.type()) << std::endl;
        std::cout << "value is: ";

        if (x.type() == bson::type::_int32) {
            std::cout << x.get_int_32();
        } else {
            std::cout << x.get_string();
        }

        std::cout << std::endl;
    }

    std::cout << "key: " << doc["hello"].key() << std::endl;

    bson_destroy(foo);

    mongoc_cleanup();
    return 0;
}

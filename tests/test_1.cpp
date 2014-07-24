#include "mongoc.h"
#include <iostream>
#include <memory>

int main(int argc, char ** argv) {
    mongoc_init();
    std::cout << "initialized mongo" << std::endl;

    bson_t * foo = BCON_NEW("hello", "world");
    std::unique_ptr<char> out(bson_as_json(foo, NULL));
    std::cout << "bson: " << out.get() << std::endl;

    mongoc_cleanup();
    return 0;
}

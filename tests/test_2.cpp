#include <iostream>

#include "models/update.h"
#include "bson/document.h"

using namespace mongo::driver;

int main(int argc, char ** argv) {

    bson::Document::View a((uint8_t *)"", 0);
    bson::Document::View b((uint8_t *)"", 0);

    UpdateModel u(a, b);
    u.multi(true);

    auto upsert = u.upsert();
    auto multi = u.multi();

    std::cout << "upsert is: " << upsert.operator bool() << "  value is: " << upsert.value_or(true) << std::endl;
    std::cout << "multi is: " << multi.operator bool() << "  value is: " << multi.value_or(false) << std::endl;

    std::swap(upsert, multi);

    upsert.value();

    return 0;
}

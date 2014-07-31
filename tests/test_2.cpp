#include <iostream>

#include "models/update.h"
#include "bson/document.h"

int main(int argc, char ** argv) {
    using namespace mongo::driver;

    bson::Document a((uint8_t *)"", 0);
    bson::Document b((uint8_t *)"", 0);

    UpdateModel u(a, b);
    u.multi(true);

    std::cout << "upsert is: " << u.upsert().operator bool() << "  value is: " << u.upsert().value_or(true) << std::endl;
    std::cout << "multi is: " << u.multi().operator bool() << "  value is: " << u.multi().value_or(false) << std::endl;

    u.upsert().value();

    return 0;
}

#include <iostream>

#include "mongocxx.hpp"

using namespace mongo::driver;

int main(int argc, char **argv) {

    bson::document::view a((std::uint8_t *)"", 0);
    bson::document::view b((std::uint8_t *)"", 0);

    model::update u(a, b);
    u.multi(true);

    auto upsert = u.upsert();
    auto multi = u.multi();

    std::cout << "upsert is: " << upsert.operator bool()
              << "  value is: " << upsert.value_or(true) << std::endl;
    std::cout << "multi is: " << multi.operator bool()
              << "  value is: " << multi.value_or(false) << std::endl;

    std::swap(upsert, multi);

    upsert.value();

    return 0;
}

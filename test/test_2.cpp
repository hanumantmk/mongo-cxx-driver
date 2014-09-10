#include <iostream>

#include "mongocxx.hpp"

using namespace mongo::driver;

int main() {
    bson::document::view a((std::uint8_t *)"", 0);
    bson::document::view b((std::uint8_t *)"", 0);

    model::update_many u(a, b);

    auto upsert = u.upsert();

    std::cout << "upsert is: " << upsert.operator bool() << "  value is: " << upsert.value_or(true)
              << std::endl;

    upsert.value();

    return 0;
}

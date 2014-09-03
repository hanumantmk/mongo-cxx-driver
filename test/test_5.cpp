#include <iostream>
#include <cstdlib>
#include <chrono>

#include <bson.h>
#include "bson/builder.hpp"

int main(int argc, char** argv) {

    if (argc != 2) {
        std::cerr << "usage - " << argv[0] << " ITERATIONS" << std::endl;
        return 1;
    }

    long iterations = atol(argv[1]);

    for (long i = 0; i < iterations; i++) {

    }

    return 0;
}

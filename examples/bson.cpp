#include <chrono>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

using namespace bsoncxx;
using namespace bsoncxx::builder::stream;

void print_stream(builder::stream::document& x) {
    x <<
        "key" << "value" <<
        "document" << open_document <<
            "int64" << types::b_int64{10} <<
            "bool" << false <<
        close_document <<
        "array" << open_array <<
            1 << 2 << 3 <<
        close_array;

//    std::cout << to_json(x) << std::endl;
}

void print_append(builder::stream::document& x) {
    x.append(
        "key", "value",
        "document", sub_document(
            "int64", types::b_int64{10},
            "bool", false
        ),
        "array", sub_array(
            1, 2, 3
        ));

//    std::cout << to_json(x) << std::endl;
}

int main(int, char**) {
    builder::stream::document x, y;

    int iterations = 1 << 24;

    auto start_stream = std::chrono::system_clock::now();
    for (int i = 0; i < iterations; i++) {
        print_stream(x);
        x.clear();
    }
    auto end_stream = std::chrono::system_clock::now();

    auto start_append = std::chrono::system_clock::now();
    for (int i = 0; i < iterations; i++) {
        print_append(y);
        y.clear();
    }
    auto end_append = std::chrono::system_clock::now();

    std::cout << "stream: " << ((end_stream - start_stream).count() / iterations) << " append: " << ((end_append - start_append).count() / iterations) << std::endl;
}

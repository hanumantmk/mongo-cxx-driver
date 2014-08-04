#include "bson/document.hpp"
#include "bson/builder.hpp"

using namespace bson;

void add_value(Builder::ValueBuilder builder) {
    builder << 4;
}

void add_array(Builder::ArrayBuilder builder) {
    builder << 1 << 2 << 3 << add_value;
}

void add_doc(Builder::DocumentBuilder builder) {
    builder <<
        "last" << add_value <<
        "array" << Builder::open_array <<
            add_array <<
        Builder::close_array;
}

struct my_functor {
    void operator()(Builder::DocumentBuilder builder) {
        builder << "my_functor" << 42;
    }
};

int main() {
    Builder builder;

    add_doc(builder);

    int x = 10;

    builder <<
        "foo" << 35 <<
        "bar" << Builder::open_doc <<
            "baz" << Builder::open_array <<
                add_array <<
            Builder::close_array <<
            add_doc <<
            [&](Builder::DocumentBuilder builder) { builder << "lambda" << x++; } <<
            [=](Builder::DocumentBuilder builder) { builder << "lambda" << x; } <<
            [](Builder::DocumentBuilder builder) { builder << "lambda" << 12; } <<
            my_functor() <<
        Builder::close_doc;

    std::cout << builder.view() << std::endl;

    static_assert(util::is_functor<my_functor, void(Builder::DocumentBuilder)>::value, "types should match");
    static_assert(! util::is_functor<my_functor, void(int)>::value, "types shouldn't match");
    static_assert(! util::is_functor<my_functor, int(Builder::DocumentBuilder)>::value, "types shouldn't match");

    static_assert(util::is_functor<decltype(add_doc), void(Builder::DocumentBuilder)>::value, "types should match");
    static_assert(! util::is_functor<decltype(add_doc), void(int)>::value, "types shouldn't match");
    static_assert(! util::is_functor<decltype(add_doc), int(Builder::DocumentBuilder)>::value, "types shouldn't match");

    try {
        builder << "foo" << Builder::open_array;

        builder << "bar" << 12;
    } catch (const std::runtime_error& re) {
        std::cout << "caught \"" << re.what() << "\"" << std::endl;
    }

    return 0;
}

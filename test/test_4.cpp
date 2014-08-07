#include "bson/document.hpp"
#include "bson/builder.hpp"

using namespace bson;

void add_value(builder::value_builder builder) {
    builder << 4;
}

void add_array(builder::array_builder builder) {
    builder << 1 << 2 << 3 << add_value;
}

void add_doc(builder::document_builder builder) {
    builder <<
        "last" << add_value <<
        "array" << builder::open_array <<
            add_array <<
        builder::close_array;
}

struct my_functor {
    void operator()(builder::document_builder builder) {
        builder << "my_functor" << 42;
    }
};

int main() {
    builder builder;

    add_doc(builder);

    int x = 10;

    builder <<
        "foo" << 35 <<
        "bar" << builder::open_doc <<
            "baz" << builder::open_array <<
                add_array <<
            builder::close_array <<
            add_doc <<
            [&](builder::document_builder builder) { builder << "lambda" << x++; } <<
            [=](builder::document_builder builder) { builder << "lambda" << x; } <<
            [](builder::document_builder builder) { builder << "lambda" << 12; } <<
            my_functor() <<
        builder::close_doc;

    std::cout << builder.view() << std::endl;

    static_assert(util::is_functor<my_functor, void(builder::document_builder)>::value, "types should match");
    static_assert(! util::is_functor<my_functor, void(int)>::value, "types shouldn't match");
    static_assert(! util::is_functor<my_functor, int(builder::document_builder)>::value, "types shouldn't match");

    static_assert(util::is_functor<decltype(add_doc), void(builder::document_builder)>::value, "types should match");
    static_assert(! util::is_functor<decltype(add_doc), void(int)>::value, "types shouldn't match");
    static_assert(! util::is_functor<decltype(add_doc), int(builder::document_builder)>::value, "types shouldn't match");

    try {
        builder << "foo" << builder::open_array;

        builder << "bar" << 12;
    } catch (const std::runtime_error& re) {
        std::cout << "caught \"" << re.what() << "\"" << std::endl;
    }

    return 0;
}

#include "bson/document.hpp"
#include "bson/builder.hpp"

using namespace bson;

void add_value(value_builder builder) { builder << 4; }

void add_array(array_builder builder) { builder << 1 << 2 << 3 << add_value; }

void add_doc(document_builder builder) {
    using namespace builder_helpers;
    builder << "last" << add_value << "array" << open_array << add_array << close_array;
}

struct my_functor {
    void operator()(document_builder builder) { builder << "my_functor" << 42; }
};

int main() {
    using namespace builder_helpers;
    using namespace types;

    builder builder;

    add_doc(builder);

    builder << "hello"
            << "world";
    builder << "hello" << b_utf8{"world"};

    int x = 10;

    builder << "foo" << 35 << "bar" << open_doc << "baz" << open_array << add_array << close_array
            << add_doc << [&](document_builder builder) { builder << "lambda" << x++; }
            << [=](document_builder builder) { builder << "lambda" << x; }
            << [](document_builder builder) { builder << "lambda" << 12; } << my_functor()
            << close_doc;

    builder << add_doc;

    std::cout << builder.view() << std::endl;
    builder.clear();

#include "bson/builder/macros_on.hpp"
    builder << "doc_macro" << DOC("baz" << ARRAY(DOC("quz" << ARRAY(1 << 2 << 3 << 4))));
#include "bson/builder/macros_off.hpp"

    std::cout << builder.view() << std::endl;

    static_assert(util::is_functor<my_functor, void(document_builder)>::value,
                  "types should match");
    static_assert(!util::is_functor<my_functor, void(int)>::value, "types shouldn't match");
    static_assert(!util::is_functor<my_functor, int(document_builder)>::value,
                  "types shouldn't match");

    static_assert(util::is_functor<decltype(add_doc), void(document_builder)>::value,
                  "types should match");
    static_assert(!util::is_functor<decltype(add_doc), void(int)>::value, "types shouldn't match");
    static_assert(!util::is_functor<decltype(add_doc), int(document_builder)>::value,
                  "types shouldn't match");

    try {
        builder << "foo" << open_array;

        builder << "bar" << 12;
    }
    catch (const std::runtime_error& re) {
        std::cout << "caught \"" << re.what() << "\"" << std::endl;
    }

    return 0;
}

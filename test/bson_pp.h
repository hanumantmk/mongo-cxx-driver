#include "bson_gen_macros.h"

#define BSON_MACRO_MAP(m, sep,...) BSON_MACRO_MAP_(BSON_MACRO_COUNT(__VA_ARGS__), m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_(...) BSON_MACRO_MAP__(__VA_ARGS__)
#define BSON_MACRO_MAP__(N, m, sep, ...) BSON_MACRO_MAP_ ## N(m, sep, __VA_ARGS__)
#define BSON_MACRO_CONCAT(...) __VA_ARGS__
#define BSON_MACRO_MAP_1(m, sep, v) m(v)
#define BSON_MACRO_MAP_0(...)

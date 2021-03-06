// Copyright 2014 MongoDB Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "libmongoc.hpp"

namespace mongo {
namespace driver {
namespace libmongoc {

//#ifdef MONGOCXX_DEBUG
#if 0
#define MONGOCXX_LIBMONGOC_SYMBOL(name) util::mock<decltype(&mongoc_##name)> name(mongoc_##name);
#include "libmongoc_symbols.hpp"
#undef MONGOCXX_LIBMONGOC_SYMBOL
#endif  // MONGOCXX_DEBUG

}  // namespace libmongoc
}  // namespace driver
}  // namespace mongo

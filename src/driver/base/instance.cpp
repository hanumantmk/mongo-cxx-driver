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

#include "driver/base/instance.hpp"

#include "mongoc.h"

namespace mongo {
namespace driver {

static void log_handler(mongoc_log_level_t, const char *, const char *, void *) {}

class LIBMONGOCXX_EXPORT instance::impl {
   public:
    impl() {
        mongoc_init();

        mongoc_log_set_handler(log_handler, nullptr);
    }

    ~impl() { mongoc_cleanup(); }
};

instance::instance() : _impl(new impl{}) {}

instance::instance(instance &&) = default;
instance &instance::operator=(instance &&) = default;
instance::~instance() = default;

}  // namespace driver
}  // namespace mongo

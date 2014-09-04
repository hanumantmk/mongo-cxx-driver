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

#pragma once

#include "driver/config/prelude.hpp"

#include <vector>

#include "driver/model/write.hpp"
#include "driver/util/optional.hpp"
#include "driver/util/unique_ptr_void.hpp"

namespace mongo {
namespace driver {
namespace model {

class LIBMONGOCXX_EXPORT bulk_write {
    friend class collection;

public:
    bulk_write(bool ordered);

    template <typename T>
    bulk_write& append(const T& container) {
        for (auto&& x : container) {
            append(x);
        }
    }

    bulk_write& append(const write& operation);

    bool ordered() const;

private:
    util::unique_ptr_void _impl;
};

}  // namespace model
}  // namespace driver
}  // namespace mongo

#include "driver/config/postlude.hpp"

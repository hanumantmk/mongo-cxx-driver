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

namespace mongo {
namespace driver {
namespace model {

// TODO: make generic template class for iterable vs vector
class LIBMONGOCXX_EXPORT bulk_write : public write<bulk_write> {
public:
    bulk_write(std::vector<write> operations);

    bulk_write& ordered(bool ordered);

    std::vector<write> operations() const;
    optional<bool> ordered() const;

private:
    std::vector<write> _operations;
    optional<bool> _ordered;

};

}  // namespace model
}  // namespace driver
}  // namespace mongo

#include "driver/config/postlude.hpp"
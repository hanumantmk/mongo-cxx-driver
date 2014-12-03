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

#include "driver/base/write_concern.hpp"

#include <stdexcept>

namespace mongo {
namespace driver {

majority_t majority{};
write_concern::type::type() {}

write_concern::write_concern() : _fsync(false), _journal(false), _confirm_from(), _timeout(0) {}

void write_concern::fsync(bool fsync) { _fsync = fsync; }
void write_concern::journal(bool journal) { _journal = journal; }
void write_concern::confirm_from(std::int32_t confirm_from) {
    if (confirm_from < 0) {
        throw std::invalid_argument(
            "Must confirm against a positive"
            " number of replica set members");
    }
    _confirm_from._count = confirm_from;
    _confirm_from._majority = false;
    _confirm_from._tag = nullopt;
}
void write_concern::confirm_from(std::string confirm_from) {
    _confirm_from._count = nullopt;
    _confirm_from._majority = false;
    _confirm_from._tag = std::move(confirm_from);
}
void write_concern::confirm_from(class majority_t confirm_from) {
    _confirm_from._count = nullopt;
    _confirm_from._majority = true;
    _confirm_from._tag = nullopt;
}

void write_concern::timeout(std::chrono::milliseconds timeout) { _timeout = timeout; }
const bool& write_concern::fsync() const { return _fsync; }
const bool& write_concern::journal() const { return _journal; }
const write_concern::type& write_concern::confirm_from() const { return _confirm_from; }
const std::chrono::milliseconds& write_concern::timeout() const { return _timeout; }

}  // namespace driver
}  // namespace mongo

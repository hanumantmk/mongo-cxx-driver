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

const std::int32_t write_concern::MAJORITY = -1;
const std::int32_t write_concern::TAG = -3;

write_concern::write_concern() : _fsync(false), _journal(false), _confirm_from(1), _timeout(0) {}

void write_concern::fsync(bool fsync) {
    _fsync = fsync;
}
void write_concern::journal(bool journal) {
    _journal = journal;
}
void write_concern::confirm_from(std::int32_t confirm_from) {
    if (confirm_from == write_concern::TAG) {
        throw std::invalid_argument("Cannot pass write_concern::TAG to confirm_from."
                                    "Use the `tag` method.");
    } else if (confirm_from != write_concern::MAJORITY && confirm_from < 0) {
        throw std::invalid_argument("Cannot require confirmation from a "
                                    "negative number of replica set members");
    }
    _tag = std::string{};
    _confirm_from = confirm_from;
}
void write_concern::timeout(std::chrono::milliseconds timeout) {
    _timeout = timeout;
}
void write_concern::tag(std::string tag) {
    _confirm_from = write_concern::TAG;
    _tag = std::move(tag);
}

const bool& write_concern::fsync() const { return _fsync; }
const bool& write_concern::journal() const { return _journal; }
const std::int32_t& write_concern::confirm_from() const { return _confirm_from; }
const std::chrono::milliseconds& write_concern::timeout() const { return _timeout; }
const std::string& write_concern::tag() const { return _tag; }

}  // namespace driver
}  // namespace mongo

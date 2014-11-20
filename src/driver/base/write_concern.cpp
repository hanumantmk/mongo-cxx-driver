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

namespace mongo {
namespace driver {

write_concern::write_concern()
    : _fsync(false)
    , _journal(false)
    , _w(1)
    , _wtimeout(0)
{}

void write_concern::fsync(bool fsync) {
    _fsync = fsync;
}

void write_concern::journal(bool journal) {
    _journal = journal;
}

void write_concern::w(std::int32_t w) {
    _w = w;
}

void write_concern::wtimeout(std::int32_t wtimeout) {
    _wtimeout = wtimeout;
}

void write_concern::wtag(std::string wtag) {
    _wtag = std::move(wtag);
}

const optional<bool>& write_concern::fsync() const { return _fsync; }
const optional<bool>& write_concern::journal() const { return _journal; }
const optional<std::int32_t>& write_concern::w() const { return _w; }
const optional<std::int32_t>& write_concern::wtimeout() const { return _wtimeout; }
const optional<std::string>& write_concern::wtag() const { return _wtag; }

}  // namespace driver
}  // namespace mongo

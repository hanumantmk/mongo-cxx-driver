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

#include <string>
#include <cstdint>

#include "driver/util/optional.hpp"

namespace mongo {
namespace driver {

class LIBMONGOCXX_EXPORT write_concern {

   public:
    write_concern();

    void fsync(bool fsync);
    void journal(bool journal);
    void w(std::int32_t w);
    void wtimeout(std::int32_t wtimeout);
    void wtag(std::string wtag);

    const optional<bool>& fsync() const;
    const optional<bool>& journal() const;
    const optional<std::int32_t>& w() const;
    const optional<std::int32_t>& wtimeout() const;
    const optional<std::string>& wtag() const;

   private:
    optional<bool> _fsync;
    optional<bool> _journal;
    optional<std::int32_t> _w;
    optional<std::int32_t> _wtimeout;
    optional<std::string> _wtag;

}; // class write_concern

}  // namespace driver
}  // namespace mongo

#include "driver/config/postlude.hpp"

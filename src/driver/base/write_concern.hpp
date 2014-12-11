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

#include <chrono>
#include <cstdint>
#include <stdexcept>
#include <string>

#include "stdx/optional.hpp"

namespace mongo {
namespace driver {

class majority_t{};
extern majority_t majority;

class LIBMONGOCXX_EXPORT write_concern {

   public:
    class type {

       public:
        bool majority() const {
            return _majority;
        }
        const optional<std::string>& tag () const {
            return _tag;
        }
        const optional<std::int32_t> number() const {
            return _count;
        }

       private:
        friend class write_concern;

        type();

        optional<std::int32_t> _count = 1;
        optional<std::string> _tag;
        bool _majority = false;

    };

    write_concern();

    void fsync(bool fsync);
    void journal(bool journal);
    void confirm_from(std::int32_t confirm_from);
    void confirm_from(class majority_t majority);
    void confirm_from(std::string tag);
    void timeout(std::chrono::milliseconds timeout);

    const bool& fsync() const;
    const bool& journal() const;
    const type& confirm_from() const;
    const std::chrono::milliseconds& timeout() const;

   private:
    bool _fsync;
    bool _journal;
    type _confirm_from;
    std::chrono::milliseconds _timeout;

};

}  // namespace driver
}  // namespace mongo

#include "driver/config/postlude.hpp"

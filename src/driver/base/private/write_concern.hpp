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

#include <memory>

#include "driver/libmongoc.hpp"

#include "driver/base/write_concern.hpp"

namespace mongo {
namespace driver {
namespace priv {

class write_concern {
public:
    write_concern(const driver::write_concern& arg) : _write_concern(mongoc_write_concern_new()) {
        mongoc_write_concern_t* wc = _write_concern;
        libmongoc::write_concern_set_fsync(wc, arg.fsync());
        libmongoc::write_concern_set_journal(wc, arg.journal());
        libmongoc::write_concern_set_wtimeout(wc, arg.timeout());
        if (arg.confirm_from() == driver::write_concern::MAJORITY) {
            libmongoc::write_concern_set_wmajority(wc, arg.timeout());
        } else if (!arg.tag().empty()) {
            libmongoc::write_concern_set_wtag(wc, arg.tag().c_str());
        } else {
            libmongoc::write_concern_set_w(wc, arg.confirm_from());
        }
    }

    ~write_concern() {
        libmongoc::write_concern_destroy(_write_concern);
    }

    const mongoc_write_concern_t* get_write_concern() const {
        return _write_concern;
    }

private:
    mongoc_write_concern_t* _write_concern;
}; // class write_concern

}  // namespace priv
}  // namespace driver
}  // namespace mongo

#include "driver/config/postlude.hpp"

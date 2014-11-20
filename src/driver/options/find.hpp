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

#include <cstdint>

#include "bson/document.hpp"
#include "driver/base/read_preference.hpp"
#include "driver/util/optional.hpp"

namespace mongo {
namespace driver {
namespace options {

class LIBMONGOCXX_EXPORT find {

   public:
    void allow_partial_results(bool allow_partial);
    void await_data(bool await_data);
    void batch_size(std::int32_t batch_size);
    void comment(std::string comment);
    void limit(std::int32_t limit);
    void max_time_ms(std::int64_t max_time_ms);
    void modifiers(bson::document::view modifiers);
    void no_cursor_timeout(bool no_cursor_timeout);
    void oplog_replay(bool oplog_replay);
    void projection(bson::document::view projection);
    void read_preference(class read_preference rp);
    void skip(std::int32_t skip);
    void sort(bson::document::view ordering);
    void tailable(bool tailable);

    const optional<bool>& allow_partial_results() const;
    const optional<bool>& await_data() const;
    const optional<std::int32_t>& batch_size() const;
    const optional<std::string>& comment() const;
    const optional<std::int32_t>& limit() const;
    const optional<std::int64_t>& max_time_ms() const;
    const optional<bson::document::view>& modifiers() const;
    const optional<bool>& no_cursor_timeout() const;
    const optional<bool>& oplog_replay() const;
    const optional<bson::document::view>& projection() const;
    const optional<class read_preference>& read_preference() const;
    const optional<std::int32_t>& skip() const;
    const optional<bson::document::view>& sort() const;
    const optional<bool>& tailable() const;

   private:
    optional<bool> _allow_partial_results;
    optional<bool> _await_data;
    optional<std::int32_t> _batch_size;
    optional<std::string> _comment;
    optional<std::int32_t> _limit;
    optional<std::int64_t> _max_time_ms;
    optional<bson::document::view> _modifiers;
    optional<bool> _no_cursor_timeout;
    optional<bool> _oplog_replay;
    optional<bson::document::view> _projection;
    optional<class read_preference> _read_preference;
    optional<std::int32_t> _skip;
    optional<bson::document::view> _ordering;
    optional<bool> _tailable;

}; // class find

}  // namespace options
}  // namespace driver
}  // namespace mongo

#include "driver/config/postlude.hpp"

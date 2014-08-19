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

#include "driver/model/write.hpp"

namespace mongo {
namespace driver {

/*
 *    class WriteRequest;
 *
 *    template <class T>
 *    class BulkWriteModel : public write<BulkWriteModel<T>> {
 *    public:
 *        BulkWriteModel(const T& requests, bool ordered)
 *            : _requests(requests), _ordered(ordered)
 *        {
 *        }
 *
 *        const T& requests() const { return _requests; }
 *        bool ordered() const { return _ordered; }
 *
 *    private:
 *
 *        const T& _requests;
 *        bool _ordered;
 *    };
 *
 *    template <class T>
 *    inline BulkWriteModel<T> make_bulk_write_model(const T& requests, bool
 *ordered) {
 *        return BulkWriteModel<T>(requests, ordered);
 *    }
 */
}
}

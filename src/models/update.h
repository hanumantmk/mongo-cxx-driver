/**
 * Copyright 2014 MongoDB Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include "bson/document.h"
#include "models/write.h"
#include "util/optional.h"

namespace mongo {
namespace driver {

    class UpdateModel : public WriteModel<UpdateModel> {

    public:
        UpdateModel(
            const bson::Document& filter,
            const bson::Document& update
        ) : _filter(filter), _update(update) { }

        const bson::Document& filter() const { return _filter; }
        const bson::Document& update() const { return _update; }

        UpdateModel& multi(bool multi) { _multi = multi; return *this; }
        UpdateModel& upsert(bool upsert) { _upsert = upsert; return *this; }

        optional<bool> multi() const { return _multi; }
        optional<bool> upsert() const { return _upsert; }

    private:
        const bson::Document& _filter;
        const bson::Document& _update;

        optional<bool> _multi;
        optional<bool> _upsert;

    };

} // namespace driver
} // namespace mongo

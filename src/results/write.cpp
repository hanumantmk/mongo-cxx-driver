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

#include "results/write.h"

namespace mongo {
namespace driver {

WriteResult::WriteResult(const bson::Document::View& view) : _value(view) {
}

WriteResult::WriteResult(bson::Document::Value value) : _value(std::move(value)) {
}

WriteResult::WriteResult() : _value(bson::Document::View()) {
}

WriteResult::~WriteResult() {
}

WriteResult::WriteResult(WriteResult&& rhs) : _value(std::move(rhs._value)) {
}

WriteResult& WriteResult::operator=(WriteResult&& rhs) {
    _value = std::move(rhs._value);
    return *this;
}

} // namespace driver
} // namespace mongo

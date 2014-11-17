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

#include "driver/base/settings.hpp"
#include <utility>

namespace mongo {
namespace driver {

namespace {
const char kDefaultURI[] = "mongodb://localhost:27017";
}  // namespace

settings::settings() : _mongodb_uri(kDefaultURI) {}

settings::settings(std::string mongodb_uri) : _mongodb_uri(std::move(mongodb_uri)) {}

}  // namespace driver
}  // namespace mongo

#include "driver/config/postlude.hpp"

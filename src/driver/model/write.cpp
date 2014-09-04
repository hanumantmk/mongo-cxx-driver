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

#include "driver/model/write.hpp"

namespace mongo {
namespace driver {
namespace model {

write::write(insert_one value) : _type(write_type::kInsertOne), _insert_one(value) {}
write::write(insert_many value) : _type(write_type::kInsertMany), _insert_many(value) {}
write::write(remove_one value) : _type(write_type::kRemoveOne), _remove_one(value) {}
write::write(remove_many value) : _type(write_type::kRemoveMany), _remove_many(value) {}
write::write(update_one value) : _type(write_type::kUpdateOne), _update_one(value) {}
write::write(update_many value) : _type(write_type::kUpdateMany), _update_many(value) {}
write::write(replace_one value) : _type(write_type::kReplaceOne), _replace_one(value) {}

write::write(write&& rhs) : _type(write_type::kUninitialized) {
    *this = std::move(rhs);
}

void write::destroy_member() {
    switch (_type) {
        case write_type::kInsertOne: _insert_one.~insert_one(); break;
        case write_type::kInsertMany: _insert_many.~insert_many(); break;
        case write_type::kUpdateOne: _update_one.~update_one(); break;
        case write_type::kUpdateMany: _update_many.~update_many(); break;
        case write_type::kRemoveOne: _remove_one.~remove_one(); break;
        case write_type::kRemoveMany: _remove_many.~remove_many(); break;
        case write_type::kReplaceOne: _replace_one.~replace_one(); break;
        case write_type::kUninitialized: break;
    }

    _type = write_type::kUninitialized;
}

write& write::operator=(write&& rhs) {
    destroy_member();

    switch (rhs._type) {
        case write_type::kInsertOne: _insert_one = std::move(rhs._insert_one); break;
        case write_type::kInsertMany: _insert_many = std::move(rhs._insert_many); break;
        case write_type::kUpdateOne: _update_one = std::move(rhs._update_one); break;
        case write_type::kUpdateMany: _update_many = std::move(rhs._update_many); break;
        case write_type::kRemoveOne: _remove_one = std::move(rhs._remove_one); break;
        case write_type::kRemoveMany: _remove_many = std::move(rhs._remove_many); break;
        case write_type::kReplaceOne: _replace_one = std::move(rhs._replace_one); break;
        case write_type::kUninitialized: break;
    }

    _type = rhs._type;

    return *this;
}

write::~write() {
    destroy_member();
}

}  // namespace model
}  // namespace driver
}  // namespace mongo

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

#include <iterator>

namespace mongo {
namespace driver {

template <class In, typename Func>
class Adapter {
   public:
    typedef decltype(*(std::declval<In>().begin())) inner_iter;

    typedef typename std::result_of<Func(inner_iter)>::type Out;

    class iterator : public std::iterator<std::forward_iterator_tag, const Out&, std::ptrdiff_t,
                                          const Out*, const Out&> {
        friend class Adapter;

       public:
        Out operator*() const { return _adapter->_func(*_iterator); }

        iterator& operator++() {
            ++_iterator;
            return *this;
        }

        bool operator==(const iterator& rhs) const { return _iterator == rhs._iterator; }

        bool operator!=(const iterator& rhs) const { return !(*this == rhs); }

       private:
        iterator(const Adapter* adapter, typename In::iterator&& iterator)
            : _adapter(adapter), _iterator(std::move(iterator)) {}

        const Adapter* _adapter;

        typename In::iterator _iterator;
    };

    friend class iterator;

    Adapter(const In* in, Func func) : _in(in), _func(func) {}

    iterator begin() const { return iterator(this, std::move(_in->begin())); }

    iterator end() const { return iterator(this, std::move(_in->end())); }

   private:
    const In* _in;
    Func _func;
};

template <class In, typename Func>
inline Adapter<In, Func> make_adapter(const In* in, Func func) {
    return Adapter<In, Func>(in, func);
}

}  // namespace driver
}  // namespace mongo

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

#include <iostream>
#include <deque>
#include <vector>
#include <memory>
#include <functional>
#include <type_traits>

namespace mongo {
namespace util {

template <typename T>
class mock {};

template <typename R, typename... Args>
class mock<R (*)(Args...)> {
   public:
    using ptr = R (*)(Args...);
    using callback = std::function<R(ptr, Args...)>;
    using conditional = std::function<bool(Args...)>;

    class rule {
        friend class mock;

       public:
        rule(callback callback) : _callback(std::move(callback)) { times(1); }

        void times(int n) {
            drop_when([n](Args...) mutable->bool {
                if (n < 0) {
                    return true;
                } else if (n == 0) {
                    return false;
                } else {
                    return n--;
                }
            });
        }

        void forever() { return times(-1); }

        void drop_when(conditional conditional) { _conditional = std::move(conditional); }

       private:
        callback _callback;
        conditional _conditional;
    };

    class MockInstance {
    friend class mock;
    public:
     MockInstance(const MockInstance&) = delete;
     MockInstance* operator=(const MockInstance&) = delete;
     ~MockInstance() {
         _parent->_active = nullptr;
     }

     rule& interpose(std::function<R(ptr, Args...)> func) {
         _callbacks.emplace_back(func);

         return _callbacks.back();
     }

     rule& interpose(std::function<R(Args...)> func) {
         _callbacks.emplace_back([=](ptr, Args... args) { return func(args...); });

         return _callbacks.back();
     }

     template <typename T, typename... U>
     typename std::enable_if<std::is_same<T, R>::value, rule&>::type interpose(T r, U... rs) {
         std::vector<R> vec = {r, rs...};
         std::size_t i = 0;

         _callbacks.emplace_back([ vec, i ](ptr, Args... args) mutable->R {
             if (i == vec.size()) {
                 i = 0;
             }
             return vec[i++];
         });
         _callbacks.back().times(vec.size());

         return _callbacks.back();
     }

     rule& visit(std::function<void(Args...)> func) {
         _callbacks.emplace_back([=](ptr, Args... args) {
             func(args...);

             return _parent->_func(args...);
         });

         return _callbacks.back();
     }

     rule& interpose(std::function<R(void)> func) {
         _callbacks.emplace_back([=](ptr, Args... args) { return func(); });

         return _callbacks.back();
     }

     rule& visit(std::function<void(void)> func) {
         _callbacks.emplace_back([=](ptr, Args... args) {
             func();

             return _parent->_func(args...);
         });

         return _callbacks.back();
     }


     std::size_t depth() const { return _callbacks.size(); }

     bool empty() const { return _callbacks.empty(); }

    private:
     MockInstance(mock* parent) : _parent(parent) {}
     mock* _parent;
     std::deque<rule> _callbacks;
    };

    friend class MockInstance;

    mock(ptr func) :_active(nullptr), _func(func){}

    R operator()(Args... args) {
        if (_active != nullptr) {
            while (!_active->_callbacks.empty()) {
                if (_active->_callbacks.front()._conditional(args...)) {
                    return _active->_callbacks.front()._callback(_func, args...);
                } else {
                    _active->_callbacks.pop_front();
                }
            }
        }

        return _func(args...);
    }

    std::unique_ptr<MockInstance> create_instance() {
        if (_active != nullptr) {
            throw std::runtime_error("Cannot create second mock instance in thread");
        }
        std::unique_ptr<MockInstance> mock_instance(new MockInstance(this));
        _active = &*mock_instance;
        return mock_instance;
    }

   private:
    MockInstance* _active;
    ptr _func;
};

//template <typename R, typename... Args>
//thread_local typename mock<R (*)(Args...)>::MockInstance* mock<R (*)(Args...)>::_active = nullptr;

}  // namespace util
}  // namespace mongo

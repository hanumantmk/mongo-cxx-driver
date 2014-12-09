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

#include <array>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <stack>
#include <thread>
#include <type_traits>
#include <unordered_map>
#include <vector>

namespace mongo {
namespace util {

template <typename T>
class mock;

template <typename R, typename... Args>
class mock<R (*)(Args...)> {
   public:
    using underlying_ptr = R (*)(Args...);
    using callback = std::function<R(Args...)>;
    using conditional = std::function<bool(Args...)>;

    class rule {
        friend class mock;

       public:
        rule(callback callback) : _callback(std::move(callback)) { times(1); }

        void times(int n) {
            until([n](Args...) mutable->bool {
                if (n < 0) {
                    return true;
                } else if (n == 0) {
                    return false;
                } else {
                    n--;
                    return true;
                }
            });
        }

        void forever() { return times(-1); }

        void until(conditional conditional) { _conditional = std::move(conditional); }

       private:
        callback _callback;
        conditional _conditional;
    };

    class MockInstance {
    friend class mock;
    public:
     MockInstance(const MockInstance&) = delete;
     MockInstance& operator=(const MockInstance&) = delete;

     ~MockInstance() {
         _parent->destroy_active_instance();
     }

     rule& interpose(const std::function<R(Args...)>& func) {
         _callbacks.emplace([=](Args... args) { return func(args...); });

         return _callbacks.top();
     }

     template <typename T, typename... U>
     typename std::enable_if<std::is_same<T, R>::value, rule&>::type interpose(T r, U... rs) {
         std::array<R, sizeof...(rs) + 1> vec = {r, rs...};
         std::size_t i = 0;

         _callbacks.emplace([ vec, i ](Args... args) mutable->R {
             if (i == vec.size()) {
                 i = 0;
             }
             return vec[i++];
         });
         _callbacks.top().times(vec.size());

         return _callbacks.top();
     }

     rule& visit(std::function<void(Args...)> func) {
         _callbacks.emplace([=](Args... args) {
             func(args...);
             return _parent->_func(args...);
         });

         return _callbacks.top();
     }

     std::size_t depth() const { return _callbacks.size(); }

     bool empty() const { return _callbacks.empty(); }

    private:
     MockInstance(mock* parent) : _parent(parent) {}
     mock* _parent;
     std::stack<rule> _callbacks;
    };

    friend class MockInstance;

    mock(underlying_ptr func) : _func(std::move(func)) {}
    mock(mock&&) = delete;
    mock(const mock&) = delete;
    mock& operator=(const mock&) = delete;

    R operator()(Args... args) {
        auto instance = active_instance();
        if (instance) {
            while (!instance->_callbacks.empty()) {
                if (instance->_callbacks.top()._conditional(args...)) {
                    return instance->_callbacks.top()._callback(args...);
                }
                instance->_callbacks.pop();
            }
        }

        return _func(args...);
    }

    std::unique_ptr<MockInstance> create_instance() {
        std::unique_ptr<MockInstance> mock_instance(new MockInstance(this));
        active_instance(mock_instance.get());
        return mock_instance;
    }

   private:
    MockInstance* active_instance() {
        const auto id = std::this_thread::get_id();
        std::lock_guard<std::mutex> lock(_active_instances_lock);
        const auto iterator = _active_instances.find(id);
        if (iterator != _active_instances.end()) {
            return iterator->second;
        }
        return nullptr;
    }

    void active_instance(MockInstance* instance) {
        const auto id = std::this_thread::get_id();
        std::lock_guard<std::mutex> lock(_active_instances_lock);

        auto& current = _active_instances[id];
        assert(!current); // It is impossible to create two MockInstances in a single thread
        current = instance;
    }

    void destroy_active_instance() {
        const auto id = std::this_thread::get_id();
        std::lock_guard<std::mutex> lock(_active_instances_lock);
        _active_instances.erase(id);
    }

    std::mutex _active_instances_lock;
    std::unordered_map<std::thread::id, MockInstance*> _active_instances;
    const underlying_ptr _func;
};

}  // namespace util
}  // namespace mongo

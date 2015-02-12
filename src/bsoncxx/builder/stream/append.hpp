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

#include <bsoncxx/config/prelude.hpp>

#include <bsoncxx/builder/stream/single_context.hpp>

namespace bsoncxx {
BSONCXX_INLINE_NAMESPACE_BEGIN
namespace builder {
namespace stream {

namespace {
template<int ...>
struct seq { };

template<int N, int ...S>
struct gens : gens<N-1, N-1, S...> { };

template<int ...S>
struct gens<0, S...> {
      typedef seq<S...> type;
};
}

template <typename T, typename U, typename ...Args>
auto append_bson(T&& t, U&& u, Args&& ...args) -> decltype(append_bson((std::forward<T>(t) << std::forward<U>(u)), std::forward<Args>(args)...)) {
    return append_bson((std::forward<T>(t) << std::forward<U>(u)), std::forward<Args>(args)...);
}

template <typename T>
auto append_bson(T&& t) -> decltype(std::forward<T>(t)) {
    return std::forward<T>(t);
}

template <typename ...Args>
struct sub_document_type {
    std::tuple<Args&&...> tup;

    template <int ...S>
    void invoke(single_context sc, seq<S...>) const {
        append_bson(sc, open_document, std::get<S>(tup)..., close_document);
    }

    void operator()(single_context sc) const {
        invoke(sc, typename gens<sizeof...(Args)>::type());
    }
};

template <typename ...Args>
struct sub_array_type {
    std::tuple<Args&&...> tup;

    template <int ...S>
    void invoke(single_context sc, seq<S...>) const {
        append_bson(sc, open_array, std::get<S>(tup)..., close_array);
    }

    void operator()(single_context sc) const {
        invoke(sc, typename gens<sizeof...(Args)>::type());
    }
};

template <typename ...Args>
sub_document_type<Args...> sub_document(Args&& ...args) {
    return sub_document_type<Args...>{std::tuple<Args&&...>(std::forward<Args>(args)...)};
}

template <typename ...Args>
sub_array_type<Args...> sub_array(Args&& ...args) {
    return sub_array_type<Args...>{std::tuple<Args&&...>(std::forward<Args>(args)...)};
}

}  // namespace stream
}  // namespace builder
BSONCXX_INLINE_NAMESPACE_END
}  // namespace bsoncxx

#include <bsoncxx/config/postlude.hpp>

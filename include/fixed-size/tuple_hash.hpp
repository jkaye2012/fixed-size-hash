#pragma once

#include "fixed-size/hash.hpp"

template <typename... T>
struct std::hash<std::tuple<T...>> {
  using Tuple = std::tuple<T...>;

  std::size_t operator()(Tuple const& tup) const noexcept {
    return fixed_size::hash{}(tup);
  }
};
#pragma once

#include "fixed-size/hash.hpp"

template <typename T, typename U>
struct std::hash<std::pair<T, U>> {
  using Pair = std::pair<T, U>;

  std::size_t operator()(Pair const& pair) const noexcept {
    return fixed_size::hash{}(pair);
  }
};
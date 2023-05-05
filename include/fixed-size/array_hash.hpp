#pragma once

#include "fixed-size/hash.hpp"

template <typename T, std::size_t N>
struct std::hash<std::array<T, N>> {
  using Array = std::array<T, N>;
  std::size_t operator()(Array const& arr) const noexcept {
    return fixed_size::hash{}(arr);
  }
};
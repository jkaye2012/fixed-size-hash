#pragma once

#include <array>
#include <cstddef>
#include <functional>
#include <tuple>
#include <utility>

namespace fixed_size {

extern std::size_t hash_combine(std::size_t seed, std::size_t val);

template <std::size_t Index, typename C>
struct hash_impl {
  std::size_t operator()(C const& c) const noexcept {
    if constexpr (Index == 0) {
      return std::hash<std::tuple_element_t<Index, C>>{}(std::get<Index>(c));
    } else {
      return hash_combine(
          std::hash<std::tuple_element_t<Index, C>>{}(std::get<Index>(c)),
          hash_impl<Index - 1, C>{}(c));
    }
  }
};

struct hash {
  template <typename C>
  std::size_t operator()(C const& c) const noexcept {
    return hash_impl<std::tuple_size_v<C> - 1, C>{}(c);
  }
};
}  // namespace fixed_size

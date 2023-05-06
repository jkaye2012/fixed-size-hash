#pragma once

#include <array>
#include <concepts>
#include <cstddef>
#include <functional>
#include <tuple>
#include <type_traits>
#include <utility>

namespace fixed_size {

extern std::size_t hash_combine(std::size_t seed, std::size_t val);

// clang-format off
template<typename C>
concept FixedSize = std::tuple_size<C>::value > 0;
// clang-format on

template <std::size_t Index, typename C>
struct hash_impl {
  std::size_t operator()(C const& c) const noexcept {
    auto hash = std::hash<std::tuple_element_t<Index, C>>{}(std::get<Index>(c));
    if constexpr (Index == 0) {
      return hash;
    } else {
      return hash_combine(hash, hash_impl<Index - 1, C>{}(c));
    }
  }
};

template <typename Arr>
inline constexpr std::size_t array_hash_impl(Arr const& arr) noexcept {
  auto hash = std::hash<typename Arr::value_type>{}(std::get<0>(arr));
  for (std::size_t idx = 1; idx < std::tuple_size_v<Arr>; ++idx) {
    hash =
        hash_combine(hash, std::hash<typename Arr::value_type>{}(arr.at(idx)));
  }
  return hash;
}

struct hash {
  template <FixedSize C>
  std::size_t operator()(C const& c) const noexcept {
    return hash_impl<std::tuple_size_v<C> - 1, C>{}(c);
  }

  template <typename T, std::size_t N>
  std::size_t operator()(std::array<T, N> const& c) const noexcept {
    return array_hash_impl(c);
  }
};
}  // namespace fixed_size

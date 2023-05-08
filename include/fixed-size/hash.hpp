#pragma once

#include <array>
#include <concepts>
#include <cstddef>
#include <functional>
#include <tuple>
#include <type_traits>
#include <utility>

namespace fixed_size {

// clang-format off
template<typename C>
concept FixedSize = std::tuple_size<C>::value > 0;

template<typename C>
concept HashCombine = std::is_default_constructible_v<C> &&
requires(C c, std::size_t seed, std::size_t val)
{
  { c(seed, val) } -> std::convertible_to<std::size_t>;
};
// clang-format on

struct default_combine {
  std::size_t operator()(std::size_t seed, std::size_t val) const noexcept {
    return seed ^ (val + 0x9e3779b9 + (seed << 6) + (seed >> 2));
  }
};

template <HashCombine Combiner, std::size_t Index, typename C>
struct hash_impl {
  std::size_t operator()(C const& c) const noexcept {
    auto hash = std::hash<std::tuple_element_t<Index, C>>{}(std::get<Index>(c));
    if constexpr (Index == 0) {
      return hash;
    } else {
      return Combiner{}(hash, hash_impl<Combiner, Index - 1, C>{}(c));
    }
  }
};

template <HashCombine Combiner, typename Arr>
inline constexpr std::size_t array_hash_impl(Arr const& arr) noexcept {
  auto hash = std::hash<typename Arr::value_type>{}(std::get<0>(arr));
  for (std::size_t idx = 1; idx < std::tuple_size_v<Arr>; ++idx) {
    hash = Combiner{}(hash, std::hash<typename Arr::value_type>{}(arr.at(idx)));
  }
  return hash;
}

template <HashCombine Combiner = default_combine>
struct hash {
  template <FixedSize C>
  std::size_t operator()(C const& c) const noexcept {
    return hash_impl<Combiner, std::tuple_size_v<C> - 1, C>{}(c);
  }

  template <typename T, std::size_t N>
  std::size_t operator()(std::array<T, N> const& c) const noexcept {
    return array_hash_impl<Combiner, std::array<T, N>>(c);
  }
};
}  // namespace fixed_size

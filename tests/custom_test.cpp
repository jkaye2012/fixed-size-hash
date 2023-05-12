#include <catch2/catch_all.hpp>

#include <cstddef>
#include <cstdint>
#include <functional>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

#include "fixed-size/hash.hpp"

struct custom_combine {
  std::size_t operator()(std::size_t seed, std::size_t val) const noexcept {
    return seed ^ (val + 0xdeadbeef + (seed << 6) + (seed >> 2));
  }
};

template <typename T, std::size_t N>
struct std::hash<std::array<T, N>> {
  using Array = std::array<T, N>;

  std::size_t operator()(Array const& arr) const noexcept {
    return fixed_size::hash<custom_combine>{}(arr);
  }
};

TEST_CASE("Custom hash combination", "[hash][custom]") {
  using Array = std::array<std::string_view, 3>;
  Array arr{"matey", "welcome", "aboard"};
  REQUIRE(std::hash<Array>{}(arr) != fixed_size::hash{}(arr));
}
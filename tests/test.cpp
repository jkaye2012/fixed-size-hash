#include <array>

#include <catch2/catch_test_macros.hpp>

#include <cstddef>
#include <cstdint>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>

#include "fixed-size/prelude.hpp"

TEST_CASE("Pair hash should work", "[hash][pair]") {
  using Pair = std::pair<std::size_t, std::size_t>;
  using Map = std::unordered_map<Pair, std::string>;

  Map m{{{1, 2}, "buckle my shoe"},
        {{3, 4}, "knock at the door"},
        {{5, 6}, "pick up sticks"}};
  CHECK(m.at({1, 2}) == "buckle my shoe");
  CHECK(!m.contains({1, 1}));
}

TEST_CASE("Array hash should work", "[hash][array]") {
  using Array = std::array<std::string, 3>;
  using Map = std::unordered_map<Array, std::string>;

  Map m{{{"a", "b", "c"}, "d"}};
  CHECK(m.at({"a", "b", "c"}) == "d");
  CHECK(!m.contains({"x", "y", "z"}));
}

TEST_CASE("Tuple hash should work", "[hash][array]") {
  using Tuple = std::tuple<std::string, std::size_t, int>;
  using Map = std::unordered_map<Tuple, std::size_t>;

  Map m{{{"foobar", 1, 2}, 123}, {{"baz", 3, 4}, 234}};
  CHECK(m.at({"baz", 3, 4}) == 234);
  CHECK(!m.contains({"something", 121, 90}));
}
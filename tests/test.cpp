
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
//

TEST_CASE("Array hash should work", "[hash][array]") {
  using Array = std::array<std::string, 3>;
  using Map = std::unordered_map<Array, std::string>;

  Map m{{{"a", "b", "c"}, "d"}};
  CHECK(m.at({"a", "b", "c"}) == "d");
  CHECK(!m.contains({"x", "y", "z"}));
}

TEST_CASE("Tuple hash should work", "[hash][tuple]") {
  using Tuple = std::tuple<std::string, std::size_t, int>;
  using Map = std::unordered_map<Tuple, std::size_t>;

  Map m{{{"foobar", 1, 2}, 123}, {{"baz", 3, 4}, 234}};
  CHECK(m.at({"baz", 3, 4}) == 234);
  CHECK(!m.contains({"something", 121, 90}));
}

TEST_CASE("Benchmarks", "[benchmark]") {
  using Array = std::array<std::size_t, 100>;
  Array arr;
  for (auto i = 0; i < arr.size(); ++i) {
    arr[i] = std::rand() / ((RAND_MAX + 1u) / 6);
  }

  using Tuple = std::tuple<std::size_t, std::size_t, std::size_t>;
  Tuple tup{1, 2, 3};

  using Pair = std::pair<std::size_t, std::size_t>;
  Pair pair{4, 5};

  BENCHMARK("Pair performance") { return std::hash<Pair>{}(pair); };
  BENCHMARK("Tuple performance") { return std::hash<Tuple>{}(tup); };
  BENCHMARK("Array performance") { return std::hash<Array>{}(arr); };
}
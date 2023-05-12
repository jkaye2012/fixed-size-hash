#include <array>
#include <functional>
#include <iostream>
#include <sstream>
#include <string_view>

#include "fixed-size/prelude.hpp"

int main(int argc, char** argv) {
  using Array = std::array<std::string_view, 3>;
  Array arr{"matey", "welcome", "aboard"};
  std::cout << std::hash<Array>{}(arr) << std::endl;
  return 0;
}
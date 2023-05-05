#pragma once

#include <cstddef>

namespace fixed_size {
inline std::size_t hash_combine(std::size_t seed, std::size_t val) {
  return seed ^ (val + 0x9e3779b9 + (seed << 6) + (seed >> 2));
}
}  // namespace fixed_size
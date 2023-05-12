# Fixed-size container hashing

Example implementation of arbitrary fixed-size container hashing in C++20.

This repository was created primarily as a resource for [a blog post on template
metaprogramming](https://jordankaye.dev/posts/template-metaprogramming-primer/). While it's not intended for production
use, it should be stable and performant for most use cases.

Currently, implementations are provided for:

* [std::array](https://en.cppreference.com/w/cpp/container/array)
* [std::tuple](https://en.cppreference.com/w/cpp/utility/tuple)
* [std::pair](https://en.cppreference.com/w/cpp/utility/pair)

Tuple and pair hashing is provided generically for any tuple-like structure that supports all of:

* [std::tuple_size_v](https://en.cppreference.com/w/cpp/utility/tuple/tuple_size)
* [std::tuple_element_t](https://en.cppreference.com/w/cpp/utility/tuple_element)
* [std::get](https://en.cppreference.com/w/cpp/utility/tuple/get)

Array hashing is specialized separately for improved performance and to support arrays of size greater
than the 1024 template depth limit.

## Cmake integration

The library can be integated using CMake easily:

```cmake
include(FetchContent)
FetchContent_Declare(fixed-size-hash
    GIT_REPOSITORY https://github.com/jkaye2012/fixed-size-hash.git
    GIT_TAG v0.1.0
)
FetchContent_MakeAvailable(fixed-size-hash)

target_link_libraries(your-target-goes-here PRIVATE fixed-size-hash)
```

A complete example can be found in the `examples` directory.

## Opt-in default hashing

Default implementations for supported containers can be opted into by including the prelude:

```c++
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
```

---

It's also possible to opt in to implementations for individual containers:

```c++
#include "fixed-size/array_hash.hpp"
```

This will allow `std::array` to be hashed, but will not bring `std::pair` or `std::tuple` implementations into scope.

## Hashing with a custom hash combination

The default implementations use a general purpose hash combination function that may not be ideal for all situations.
Hash combination can be customized by providing a struct that satisfies the `HashCombine` concept:

```c++
template<typename C>
concept HashCombine = std::is_default_constructible_v<C> &&
requires(C c, std::size_t seed, std::size_t val)
{
  { c(seed, val) } -> std::convertible_to<std::size_t>;
};
```

This concept is provided by the `fixed-size/hash.hpp` header. A complete example:

```c++
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
```


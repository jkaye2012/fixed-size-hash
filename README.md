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

## Cmake integration

## Opt-in default hashing

## Hashing with a custom hash combination


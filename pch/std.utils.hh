// Precompiled header for utils in std.
#pragma once

#include <utility>
#include <type_traits>
#include <typeinfo>
#include <typeindex>
#include <bitset>
#include <functional>
#include <tuple>

#if __cplusplus >= 201703L
#include <any>
#include <optional>
#include <variant>
#endif // __cplusplus >= 201703L

#if __cplusplus >= 202002L
#include <version>
#include <compare>
#endif // __cplusplus >= 202002L

#if __cplusplus >= 202203L
#include <expected>
#endif // __cplusplus >= 202203L

#if __cplusplus >= 202600L
#include <debugging>
#endif // __cplusplus >= 202600L
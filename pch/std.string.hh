// Precompiled header for string in std.
#pragma once

#include <string>

#if __cplusplus >= 201703L
#include <string_view>
#include <charconv>
#endif // __cplusplus >= 201703L

#if __cplusplus >= 202002L
#include <format>
#endif // __cplusplus >= 202002L

// C string functions
#include <cctype>
#include <cstring>
#include <cwctype>
#include <cuchar>
#include <cwctype>

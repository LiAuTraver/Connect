// Precompiled header for input/output in std.
#pragma once

#include <ios>
#include <iosfwd>
#include <istream>
#include <ostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <streambuf>
#include <locale>
//#include <regex> // not gonna use regex

#if __cplusplus >= 201703L
#include <filesystem>
#endif // __cplusplus >= 201703L

#if __cplusplus >= 202002L
#include <syncstream>
#include <source_location>
#endif // __cplusplus >= 202002L

#if __cplusplus >= 202203L
#include <print>
#include <spanstream>
#endif // __cplusplus >= 202203L

#if __cplusplus >= 202600L
#include <text_encoding>
#else
#include <codecvt>
#endif // __cplusplus >= 202600L

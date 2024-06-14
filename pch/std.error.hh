// Precompiled header for error in std.
#pragma once

#include <exception>
#include <stdexcept>
#include <system_error>

#if __cplusplus >= 202203L
#include <stacktrace>
#endif // __cplusplus >= 202203L

// C error handling
#include <cerrno>
#include <cassert>

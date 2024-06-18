#pragma once

#include "include/config.hpp"
#include "pch/std.error.hh"

CONNECT_NAMESPACE_BEGIN
class NotImplementedException : public std::exception {
public:
	NotImplementedException() noexcept: std::exception("Code here has not been implemented yet.",1) {}
};
CONNECT_NAMESPACE_END
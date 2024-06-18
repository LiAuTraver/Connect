#pragma once

#include "include/config.hpp"
#include <pch/qt.core.hh>
CONNECT_NAMESPACE_BEGIN

struct Point {
	using size_type = qsizetype;
	size_type y;
	size_type x;

	Point(size_type y, size_type x) : y(y), x(x) {}

	_NODISCARD constexpr inline bool operator==(const Point &rhs) const noexcept {
		return this->y == rhs.y && this->x == rhs.x;
	}

	_NODISCARD constexpr inline bool operator!=(const Point &rhs) const noexcept {
		return !(this->y == rhs.y && this->x == rhs.x);
	}
};

CONNECT_NAMESPACE_END

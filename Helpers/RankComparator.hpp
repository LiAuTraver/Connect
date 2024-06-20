#pragma once

#include <include/config.hpp>
#include <pch/std.container.hh>
#include <pch/qt.core.hh>
#include "Models/Record.hpp"

CONNECT_NAMESPACE_BEGIN
struct RankComparator {
	RankComparator() = default;

	_NODISCARD CONNECT_INLINE bool operator()(const Record &lhs, const Record &rhs) const noexcept {
		if (lhs.score > rhs.score)
			return true;
		else if (lhs.score == rhs.score) {
			if (lhs.elapsedMilliseconds < rhs.elapsedMilliseconds)
				return true;
			else if (lhs.elapsedMilliseconds == rhs.elapsedMilliseconds) {
				if (lhs.name < rhs.name)
					return true;
			}
		}
		return false;
	}
};
CONNECT_NAMESPACE_END
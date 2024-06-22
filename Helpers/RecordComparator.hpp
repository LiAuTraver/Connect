#pragma once

#include <include/config.hpp>
#include <pch/std.utils.hh>
#include "Records.hpp"

CONNECT_NAMESPACE_BEGIN
#if 1
//! Record: a tuple of QString, qint64, qint64, each standing for name, score, time
//! According to this comparator logic, two records are considered `identical`
//! *if* and *only if* `lhs < rhs` and `rhs < lhs` both return `false`.
struct RecordComparator {
	_NODISCARD CONNECT_INLINE bool operator()(const Record &lhs, const Record &rhs)
	const noexcept(noexcept(std::get<0>(lhs) < std::get<0>(rhs))) {
		if (std::get<1>(lhs) != std::get<1>(rhs)) {
			return std::get<1>(lhs) > std::get<1>(rhs);
		}
		if (std::get<2>(lhs) != std::get<2>(rhs)) {
			return std::get<2>(lhs) < std::get<2>(rhs);
		}
		return std::get<0>(lhs) < std::get<0>(rhs);
	}
};

CONNECT_NAMESPACE_END
#else
struct RecordComparator {
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
#endif

#pragma once

#include <Models/Record.hpp>
#include <include/config.hpp>
#include <pch/std.utils.hh>

CONNECT_NAMESPACE_BEGIN
//! Record: a tuple of QString, qint64, qint64, each standing for name, score, time
//! According to this comparator logic, two records are considered `identical`
//! *if* and *only if* `lhs < rhs` and `rhs < lhs` both return `false`.
CONNECT_OPT_1_NAMESPACE_BEGIN
struct RecordComparator {
	_NODISCARD CONNECT_INLINE bool operator()(const Record &lhs, const Record &rhs) const
			noexcept(noexcept(std::get<0>(lhs) < std::get<0>(rhs))) {
		if (std::get<1>(lhs) != std::get<1>(rhs)) {
			return std::get<1>(lhs) > std::get<1>(rhs);
		}
		if (std::get<2>(lhs) != std::get<2>(rhs)) {
			return std::get<2>(lhs) < std::get<2>(rhs);
		}
		return std::get<0>(lhs) < std::get<0>(rhs);
	}
};
CONNECT_OPT_1_NAMESPACE_END

CONNECT_OPT_2_NAMESPACE_BEGIN
struct RecordComparator {
	_NODISCARD CONNECT_INLINE bool operator()(const Record &lhs, const Record &rhs) const
			noexcept(noexcept(std::get<0>(lhs) < std::get<0>(rhs))) {
		if (std::get<1>(lhs) != std::get<1>(rhs)) {
			return std::get<1>(lhs) > std::get<1>(rhs);
		}
		if (std::get<2>(lhs) != std::get<2>(rhs)) {
			return std::get<2>(lhs) < std::get<2>(rhs);
		}
		return std::get<0>(lhs) < std::get<0>(rhs);
	}
};
CONNECT_OPT_2_NAMESPACE_END

CONNECT_NAMESPACE_END

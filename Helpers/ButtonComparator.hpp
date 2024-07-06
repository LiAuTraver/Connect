#pragma once

#include <include/config.hpp>
#include <Models/BlockButton.hpp>
#include <Models/Point.hpp>


CONNECT_NAMESPACE_BEGIN
class ButtonComparator_fn {
public:
	_NODISCARD inline bool operator()(const BlockButton* lhs, const BlockButton* rhs)const {
		return true;
	}
};
inline constexpr ButtonComparator_fn ButtonComparator;
CONNECT_NAMESPACE_END

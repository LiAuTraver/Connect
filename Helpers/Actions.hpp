#pragma once

#include <include/config.hpp>

CONNECT_NAMESPACE_BEGIN
enum class TimeAction {
	Pause,
	Resume
};

enum class ButtonAction {
	Hide,
	Show
};

enum class ButtonStatus{
	Hidden,
	Showed
};
CONNECT_NAMESPACE_END

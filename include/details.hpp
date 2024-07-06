#pragma once

#include <include/config.hpp>

CONNECT_NAMESPACE_BEGIN

inline namespace details {
struct json {};

enum class TimeAction { Pause, Resume };

enum class ButtonAction { Hide, Show };

enum class ButtonStatus { Hidden, Showed };

/**
 * @brief Base class for IO devices.
 * @details This class is used to define the base class for IO devices.
 * @details It's similar to the `QIODevice` class in Qt but without Qt-specified macros.
 */
class IODeviceBase {
public:
	enum OpenModeFlag {
		NotOpen = 0x0000,
		ReadOnly = 0x0001,
		WriteOnly = 0x0002,
		ReadWrite = ReadOnly | WriteOnly,  // 0x0003, a.k.a. 3
		Append = 0x0004,
		Truncate = 0x0008,
		Text = 0x0010,
		Unbuffered = 0x0020,
		NewOnly = 0x0040,
		ExistingOnly = 0x0080,
		NewOrExisting = NewOnly | ExistingOnly	// 0x00C0, a.k.a. 192
	};
};
//! note: just for reading, actually a dummy interface
interface ISerializer extends public IODeviceBase {
public:
	ISerializer() = default;
	virtual ~ISerializer() noexcept = default;
};
_NODISCARD CONNECT_INLINE CONNECT_CONSTEXPR IODeviceBase::OpenModeFlag operator|(
	IODeviceBase::OpenModeFlag lhs, IODeviceBase::OpenModeFlag rhs) {
	return static_cast<IODeviceBase::OpenModeFlag>(static_cast<int>(lhs) | static_cast<int>(rhs));
}
_NODISCARD CONNECT_INLINE CONNECT_CONSTEXPR IODeviceBase::OpenModeFlag operator&(
	IODeviceBase::OpenModeFlag lhs, IODeviceBase::OpenModeFlag rhs) {
	return static_cast<IODeviceBase::OpenModeFlag>(static_cast<int>(lhs) & static_cast<int>(rhs));
}
_NODISCARD CONNECT_INLINE CONNECT_CONSTEXPR IODeviceBase::OpenModeFlag operator~(
	IODeviceBase::OpenModeFlag flag) {
	return static_cast<IODeviceBase::OpenModeFlag>(~static_cast<int>(flag));
}
_NODISCARD CONNECT_INLINE CONNECT_CONSTEXPR bool operator!(IODeviceBase::OpenModeFlag flag) {
	return static_cast<int>(flag) == 0;
}
_NODISCARD CONNECT_INLINE CONNECT_CONSTEXPR auto operator<=>(IODeviceBase::OpenModeFlag lhs,
															 IODeviceBase::OpenModeFlag rhs) {
	return static_cast<int>(lhs) <=> static_cast<int>(rhs);
}
_NODISCARD CONNECT_INLINE CONNECT_CONSTEXPR IODeviceBase::OpenModeFlag& operator|=(
	IODeviceBase::OpenModeFlag& lhs, IODeviceBase::OpenModeFlag rhs) {
	return lhs = lhs | rhs;
}
_NODISCARD CONNECT_INLINE CONNECT_CONSTEXPR IODeviceBase::OpenModeFlag& operator&=(
	IODeviceBase::OpenModeFlag& lhs, IODeviceBase::OpenModeFlag rhs) {
	return lhs = lhs & rhs;
}
_NODISCARD CONNECT_INLINE CONNECT_CONSTEXPR IODeviceBase::OpenModeFlag& operator^=(
	IODeviceBase::OpenModeFlag& lhs, IODeviceBase::OpenModeFlag rhs) {
	return lhs = static_cast<IODeviceBase::OpenModeFlag>(static_cast<int>(lhs) ^
														 static_cast<int>(rhs));
}
_NODISCARD CONNECT_INLINE CONNECT_CONSTEXPR IODeviceBase::OpenModeFlag operator^(
	IODeviceBase::OpenModeFlag lhs, IODeviceBase::OpenModeFlag rhs) {
	return static_cast<IODeviceBase::OpenModeFlag>(static_cast<int>(lhs) ^ static_cast<int>(rhs));
}
_NODISCARD CONNECT_INLINE CONNECT_CONSTEXPR IODeviceBase::OpenModeFlag operator<<(
	IODeviceBase::OpenModeFlag flag, int shift) {
	return static_cast<IODeviceBase::OpenModeFlag>(static_cast<int>(flag) << shift);
}
_NODISCARD CONNECT_INLINE CONNECT_CONSTEXPR IODeviceBase::OpenModeFlag operator>>(
	IODeviceBase::OpenModeFlag flag, int shift) {
	return static_cast<IODeviceBase::OpenModeFlag>(static_cast<int>(flag) >> shift);
}
_NODISCARD CONNECT_INLINE CONNECT_CONSTEXPR IODeviceBase::OpenModeFlag& operator<<=(
	IODeviceBase::OpenModeFlag& flag, int shift) {
	return flag = flag << shift;
}
_NODISCARD CONNECT_INLINE CONNECT_CONSTEXPR IODeviceBase::OpenModeFlag& operator>>=(
	IODeviceBase::OpenModeFlag& flag, int shift) {
	return flag = flag >> shift;
}

// delete + -
_NODISCARD CONNECT_INLINE CONNECT_CONSTEXPR IODeviceBase::OpenModeFlag operator+(
	IODeviceBase::OpenModeFlag lhs, IODeviceBase::OpenModeFlag rhs) = delete;
_NODISCARD CONNECT_INLINE CONNECT_CONSTEXPR IODeviceBase::OpenModeFlag operator-(
	IODeviceBase::OpenModeFlag lhs, IODeviceBase::OpenModeFlag rhs) = delete;
}
CONNECT_NAMESPACE_END

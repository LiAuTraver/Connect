#pragma once

#include <include/config.hpp>
#include <pch/qt.widgets.hh>

CONNECT_NAMESPACE_BEGIN
class Block {

public:
	using size_type = qsizetype;
	using button_pointer = QPushButton *;
public:
	explicit Block(QWidget *parent = nullptr);

	explicit Block(const size_type &y,
	               const size_type &x,
	               QWidget *parent = nullptr);

	explicit Block(const size_type &y, const size_type &x, const QString &text = "", QWidget *parent = nullptr);

	~Block() = default;

public:

	CONNECT_INLINE bool operator==(const Block &) const;

	CONNECT_INLINE bool operator!=(const Block &) const;

	CONNECT_INLINE bool operator==(const QVector2D &) const;

	CONNECT_INLINE bool operator!=(const QVector2D &) const;

	CONNECT_INLINE Block &operator=(const QVector2D &);

	_NODISCARD CONNECT_INLINE button_pointer operator->() const noexcept;

	CONNECT_INLINE bool operator<=>(const Block &) = delete;

	static CONNECT_INLINE Block empty() noexcept;

public:
	_NODISCARD CONNECT_INLINE QVector2D get_coor() const noexcept;

	template<typename T>
	requires std::convertible_to<T, size_type>
	CONNECT_CONSTEXPR CONNECT_INLINE void set_row(T &y) noexcept{
		row_coor = static_cast<size_type>(y);
	}

	template<typename T>
	requires std::convertible_to<T, size_type>
	CONNECT_CONSTEXPR CONNECT_INLINE void set_col(T &y) noexcept{
		col_coor = static_cast<size_type>(y);
	}

	template<typename T>
	requires std::convertible_to<T, size_type>
	_NODISCARD CONNECT_CONSTEXPR CONNECT_INLINE size_type get_row(T &y) const noexcept{
		return row_coor;
	}

	template<typename T>
	requires std::convertible_to<T, size_type>
	_NODISCARD CONNECT_CONSTEXPR CONNECT_INLINE size_type get_col(T &y) const noexcept{
		return col_coor;
	}

public:
	button_pointer button;
private:
	size_type row_coor;
	size_type col_coor;
};

CONNECT_NAMESPACE_END


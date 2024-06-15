#pragma once

#include <include/Block.hpp>
#include <include/config.hpp>
#include <include/Point.hpp>

CONNECT_NAMESPACE_BEGIN
#if 0
class Blocks {
public:
	using size_type = qsizetype;
public:
	explicit Blocks();

	explicit Blocks(size_type rows, size_type cols) : height(rows), width(cols) {
		gridBlocks.resize(height);
		for (auto &rowBlocks: gridBlocks) {
			rowBlocks.resize(width);
		}
	}

public:
	_NODISCARD CONNECT_CONSTEXPR CONNECT_INLINE
	Block &operator[](size_type row, size_type col) noexcept;

private:
	std::vector<std::vector<Block>> gridBlocks;
	size_type height;
	size_type width;
};
#else

class Blocks {
public:
	using size_type = qsizetype;
public:
	explicit Blocks();

	explicit Blocks(size_type h, size_type w);

public:
	void reset() noexcept;

	void reset(size_type h, size_type w) noexcept;

	size_type getTotal() noexcept;

	_NODISCARD const std::vector<std::string> &getImagePath() const noexcept;

	_NODISCARD size_type getRows() const noexcept;

	_NODISCARD size_type getCols() const noexcept;

public:
	template<typename... _IndexTypes> requires (std::is_convertible_v<_IndexTypes, size_type> && ...) &&
	(std::is_nothrow_constructible_v<size_type, _IndexTypes> && ...)
	&&(sizeof...(_IndexTypes) == 2)
	// COMPILER's FAULT. SHOULD BE operator[].
	_NODISCARD CONNECT_INLINE const char *operator()(_IndexTypes... indices) const noexcept {
		qDebug() << sizeof...(indices);
		return imagePath.at(_indices_to_index(indices...)).c_str();
	}

	_NODISCARD inline const char* operator()(const Point& point)const noexcept{
		return this->operator()(point.y,point.x);
	}

	void addImages();

private:
	template<typename... _Indices>
	size_type _indices_to_index(_Indices... indices) const {
		std::array<size_type, sizeof...(indices)> _idx{indices...};
		return _idx.at(0) * (width - 1) + _idx.at(1);
	}

private:
	std::vector<std::string> imagePath;
	size_type height;
	size_type width;
	size_type total;
public:
#ifdef __cpp_multidimensional_subscript
	template<typename... _IndexTypes>
	requires (std::is_convertible_v<_IndexTypes, size_type> && ...) &&
	(std::is_nothrow_constructible_v<size_type, _IndexTypes> && ...)
	&&(sizeof...(_IndexTypes) == 2)
	// COMPILER's FAULT. SHOULD BE operator[].
	_NODISCARD CONNECT_INLINE const char *operator[](_IndexTypes... indices) const noexcept {
		qDebug() << sizeof...(indices);
		return imagePath.at(_indices_to_index(indices...)).c_str();
	}
#else
#endif
};

#endif


CONNECT_NAMESPACE_END
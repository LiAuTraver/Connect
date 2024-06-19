#pragma once

#include "Models/Block.hpp"
#include "include/config.hpp"
#include "Models/Point.hpp"
#include "Contracts/IFileService.hpp"

CONNECT_NAMESPACE_BEGIN
class Blocks {
public:
	using size_type = qsizetype;

	static const std::string_view IMAGE_PATH;
public:
	explicit Blocks();

	explicit Blocks(std::string_view path);

	explicit Blocks(size_type h, size_type w);

	explicit Blocks(size_type h, size_type w, std::string_view path);

public:
	Blocks &reset(size_type h = 0, size_type w = 0, const std::string_view importPath = IMAGE_PATH);

	_NODISCARD size_type getTotal() noexcept;

	_NODISCARD const std::vector<std::string> &getImagePath() const noexcept;

	_NODISCARD size_type getRows() const noexcept;

	_NODISCARD size_type getCols() const noexcept;

public:
	Blocks &Oninitialize();

	Blocks &initializeImagePaths();

	Blocks &initializeImageGrid();

	_NODISCARD CONNECT_FORCE_INLINE const char *generateImagePath() const;

private:
	template<typename... _Indices>
	_NODISCARD CONNECT_INLINE constexpr size_type _indices_to_index(_Indices... indices) const {
		std::array<size_type, sizeof...(indices)> _idx{indices...};
		return _idx.at(0) * (width - 1) + _idx.at(1);
	}

public:
	template<typename... _IndexTypes> requires (std::is_convertible_v<_IndexTypes, size_type> && ...) &&
	(std::is_nothrow_constructible_v<size_type, _IndexTypes> && ...)
	&&(sizeof...(_IndexTypes) == 2)
	// COMPILER's FAULT. SHOULD BE operator[].
	_NODISCARD CONNECT_INLINE const char *
	operator()(_IndexTypes... indices) const noexcept(noexcept(_indices_to_index(indices...))) {
		qDebug() << sizeof...(indices);
		return imageGrid.at(_indices_to_index(indices...)).data();
	}

	_NODISCARD CONNECT_FORCE_INLINE const char *
	operator()(const Point &point) const noexcept(noexcept(this->operator()(point.y, point.x))) {
		return this->operator()(point.y, point.x);
	}

	/**
	 * @brief string_view's version
	 */
	template<typename... _IndexTypes> requires (std::is_convertible_v<_IndexTypes, size_type> && ...) &&
	(std::is_nothrow_constructible_v<size_type, _IndexTypes> && ...)
	&&(sizeof...(_IndexTypes) == 2)
	_NODISCARD CONNECT_INLINE std::string_view &
	operator()(_IndexTypes... indices) noexcept(noexcept(_indices_to_index(indices...))) {
		return imageGrid.at(_indices_to_index(indices...));
	}

	_NODISCARD CONNECT_FORCE_INLINE std::string_view &
	operator()(const Point &point) noexcept(noexcept(this->operator()(point.y, point.x))) {
		return this->operator()(point.y, point.x);
	}

private:
	/**
	 * @brief imageSource: a two*two grid <br>
	 * @brief imageGrid: non-repetition paths of images
	 */
	std::vector<std::string> imageSource;
	std::vector<std::string_view> imageGrid;
	size_type height;
	size_type width;
	size_type total;
	std::filesystem::path path;
};
CONNECT_NAMESPACE_END
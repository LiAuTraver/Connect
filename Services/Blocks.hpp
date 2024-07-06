#pragma once

#include <Models/Point.hpp>
#include <include/config.hpp>

CONNECT_NAMESPACE_BEGIN
CONNECT_OPT_1_NAMESPACE_BEGIN
class Blocks {
public:
	using size_type = qsizetype;
public:
	explicit Blocks() = default;

	explicit Blocks(size_type h, size_type w);

public:
	Blocks &reset(size_type h = 0, size_type w = 0);

	_NODISCARD size_type getTotal() noexcept;

	_NODISCARD const std::vector<QString> &getImagePath() const noexcept;

	_NODISCARD size_type getRows() const noexcept;

	_NODISCARD size_type getCols() const noexcept;


public:
	Blocks &Oninitialize();

	std::optional<std::string_view> initializeImagePaths();

	Blocks &initializeImageGrid();

	_NODISCARD CONNECT_FORCE_INLINE QString generateImagePath() const;

private:
	template<typename... Indices>
	_NODISCARD CONNECT_INLINE constexpr size_type _indices_to_index(Indices... indices) const {
		std::array<size_type, sizeof...(indices)> _idx{indices...};
		return _idx.at(0) * (width - 1) + _idx.at(1);
	}

public:
	template<typename... IndexTypes> requires (std::is_convertible_v<IndexTypes, size_type> && ...) &&
	(std::is_nothrow_constructible_v<size_type, IndexTypes> && ...)
	&&(sizeof...(IndexTypes) == 2)
	// COMPILER's FAULT. SHOULD BE operator[].
	_NODISCARD CONNECT_INLINE QString
	operator()(IndexTypes... indices) const noexcept(noexcept(_indices_to_index(indices...))) {
		qDebug() << sizeof...(indices);
		return imageGrid.at(_indices_to_index(indices...));
	}

	_NODISCARD QString
	operator()(const Point &point) const noexcept(noexcept(this->operator()(point.y, point.x))) {
		return this->operator()(point.y, point.x);
	}

	/**
	 * @brief string_view's version
	 */
	template<typename... IndexTypes> requires (std::is_convertible_v<IndexTypes, size_type> && ...) &&
	(std::is_nothrow_constructible_v<size_type, IndexTypes> && ...)
	&&(sizeof...(IndexTypes) == 2)
	_NODISCARD CONNECT_INLINE QString &
	operator()(IndexTypes... indices) noexcept(noexcept(_indices_to_index(indices...))) {
		return imageGrid.at(_indices_to_index(indices...));
	}

	_NODISCARD CONNECT_FORCE_INLINE QString &
	operator()(const Point &point) noexcept(noexcept(this->operator()(point.y, point.x))) {
		return this->operator()(point.y, point.x);
	}

private:
	/**
	 * @brief imageSource: a two*two grid <br>
	 * @brief imageGrid: non-repetition paths of images
	 */
	std::vector<QString> imageSource;
	std::vector<QString> imageGrid;
	size_type height{};
	size_type width{};
	size_type total{};
};
CONNECT_OPT_1_NAMESPACE_END
CONNECT_OPT_2_NAMESPACE_BEGIN
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
	Blocks &reset(size_type h = 0, size_type w = 0, std::string_view importPath = IMAGE_PATH);

	_NODISCARD size_type getTotal() noexcept;

	_NODISCARD const std::vector<std::string> &getImagePath() const noexcept;

	_NODISCARD size_type getRows() const noexcept;

	_NODISCARD size_type getCols() const noexcept;

public:
	Blocks &Oninitialize();

	std::optional<std::string_view> initializeImagePaths(std::string_view filePath);

	Blocks &initializeImageGrid();

	_NODISCARD CONNECT_FORCE_INLINE const char *generateImagePath() const;

private:
	template<typename... Indices>
	_NODISCARD CONNECT_INLINE constexpr size_type _indices_to_index(Indices... indices) const {
		std::array<size_type, sizeof...(indices)> _idx{indices...};
		return _idx.at(0) * (width - 1) + _idx.at(1);
	}

public:
	template<typename... IndexTypes> requires (std::is_convertible_v<IndexTypes, size_type> && ...) &&
	(std::is_nothrow_constructible_v<size_type, IndexTypes> && ...)
	&&(sizeof...(IndexTypes) == 2)
	// COMPILER's FAULT. SHOULD BE operator[].
	_NODISCARD CONNECT_INLINE const char *
	operator()(IndexTypes... indices) const noexcept(noexcept(_indices_to_index(indices...))) {
		qDebug() << sizeof...(indices);
		return imageGrid.at(_indices_to_index(indices...)).data();
	}

	_NODISCARD const char *
	operator()(const Point &point) const noexcept(noexcept(this->operator()(point.y, point.x))) {
		return this->operator()(point.y, point.x);
	}

	/**
	 * @brief string_view's version
	 */
	template<typename... IndexTypes> requires (std::is_convertible_v<IndexTypes, size_type> && ...) &&
	(std::is_nothrow_constructible_v<size_type, IndexTypes> && ...)
	&&(sizeof...(IndexTypes) == 2)
	_NODISCARD CONNECT_INLINE std::string_view &
	operator()(IndexTypes... indices) noexcept(noexcept(_indices_to_index(indices...))) {
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
	size_type height{};
	size_type width{};
	size_type total{};
	std::filesystem::path imageSourcePath;
};
CONNECT_OPT_2_NAMESPACE_END
CONNECT_NAMESPACE_END
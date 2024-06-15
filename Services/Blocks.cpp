#include <include/Blocks.hpp>
#include <include/config.hpp>

#if 0
_NODISCARD CONNECT_CONSTEXPR CONNECT_INLINE Connect::Block &
Connect::Blocks::operator[](size_type row, size_type col) noexcept {
	return gridBlocks[row][col];
}

Connect::Blocks::Blocks() : height(0), width(0), gridBlocks() {}
#else

Connect::Blocks::Blocks() : height(0), width(0), total(0) {}

Connect::Blocks::Blocks(Connect::Blocks::size_type h, Connect::Blocks::size_type w)
		: height(h), width(w), total(height * width) {
	imagePath.resize(total);
}

void Connect::Blocks::reset() noexcept {
	height = 0;
	width = 0;
	total = 0;
	imagePath.clear();
}

void Connect::Blocks::reset(Connect::Blocks::size_type h, Connect::Blocks::size_type w) noexcept {
	height = h;
	width = w;
	total = height * width;
	imagePath.clear();
	imagePath.resize(total);
}


Connect::Blocks::size_type Connect::Blocks::getTotal() noexcept {
	total = height * width;
	return total;
}


const std::vector<std::string> &Connect::Blocks::getImagePath() const noexcept {
	return imagePath;
}


Connect::Blocks::size_type Connect::Blocks::getRows() const noexcept {
	return height;
}


Connect::Blocks::size_type Connect::Blocks::getCols() const noexcept {
	return width;
}

void Connect::Blocks::addImages() {
	imagePath.clear();
	this->imagePath.emplace_back(CONNECT_IMAGE_PATH("bread.png"));
	this->imagePath.emplace_back(CONNECT_IMAGE_PATH("brick.png"));
}



#endif


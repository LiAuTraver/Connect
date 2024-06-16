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
	imageGrid.resize(total);
}

void Connect::Blocks::reset() noexcept {
	height = 0;
	width = 0;
	total = 0;
	imageGrid.clear();
	imageSource.clear();
}

void Connect::Blocks::reset(Connect::Blocks::size_type h, Connect::Blocks::size_type w) noexcept {
	height = h;
	width = w;
	total = height * width;
	imageSource.clear();
	imageSource.resize(total);
}


Connect::Blocks::size_type Connect::Blocks::getTotal() noexcept {
	total = height * width;
	return total;
}


const std::vector<std::string> &Connect::Blocks::getImagePath() const noexcept {
	return imageSource;
}


Connect::Blocks::size_type Connect::Blocks::getRows() const noexcept {
	return height;
}


Connect::Blocks::size_type Connect::Blocks::getCols() const noexcept {
	return width;
}

void Connect::Blocks::initializeImagePaths() {
	imageSource.clear();
	this->imageSource.emplace_back(CONNECT_IMAGE_PATH("bread.png"));
	this->imageSource.emplace_back(CONNECT_IMAGE_PATH("brick.png"));
}

_NODISCARD const char *Connect::Blocks::generateImagePath() const {

	std::random_device rd;
	std::mt19937_64 gen(rd());
	std::uniform_int_distribution<size_type> dis(0, static_cast<size_type>((imageSource.size() - 1 > 0 ?
	                                                                        imageSource.size() - 1 : 0)));
	auto num = dis(gen);
	qDebug() << "num: " << num;
	return imageSource.at(num).c_str();
}

void Connect::Blocks::initializeImageGrid(size_type row, size_type col) {
	imageGrid.resize(row * col);
	for (auto y = 0LL; y < row; y++)
		for (auto x = 0LL; x < col; x++) {
			this->operator()(y, x) = generateImagePath();
		}
}


#endif


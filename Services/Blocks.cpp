#include <Services/Blocks.hpp>
#include <include/config.hpp>


const std::string_view Connect::Blocks::IMAGE_PATH = {std::filesystem::current_path().string() + "Resources/images"};

Connect::Blocks::Blocks() : height(0), width(0), total(0), path("") {}

Connect::Blocks::Blocks(std::nullptr_t) : Blocks() {}

Connect::Blocks::Blocks(Connect::Blocks::size_type h, Connect::Blocks::size_type w) {
	reset(h, w);
}

Connect::Blocks::Blocks(Connect::Blocks::size_type h, Connect::Blocks::size_type w, const std::string_view path) {
	reset(h, w, path);
}

void Connect::Blocks::reset() noexcept {
	height = 0;
	width = 0;
	total = 0;
	imageGrid.clear();
	imageSource.clear();
	path = "";
}

void Connect::Blocks::reset(Connect::Blocks::size_type h, Connect::Blocks::size_type w) noexcept {
	height = h;
	width = w;
	total = height * width;
	imageSource.clear();
	imageSource.resize(total);
	path = "";
}


void Connect::Blocks::reset(Connect::Blocks::size_type h, Connect::Blocks::size_type w,
                            const std::string_view importPath = Connect::Blocks::IMAGE_PATH) {
	height = h;
	width = w;
	total = height * width;
	imageSource.clear();
	imageSource.resize(total);
	this->path = importPath;
	if (importPath.empty() or importPath == "") {
		qDebug() << "Path is empty";
		return;
	}
	this->initializeImagePaths();
}

_NODISCARD Connect::Blocks::size_type Connect::Blocks::getTotal() noexcept {
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
	if (this->path.empty() || not std::filesystem::exists(this->path)) {
		qDebug() << "invalid path: " << path.string();
//		exit(1);
	}
	// recursively search for all files in the directory using std::filesystem
	for (const auto &entry: std::filesystem::recursive_directory_iterator(path)) {
		if (entry.is_regular_file()) {
			imageSource.push_back(entry.path().string());
		}
	}
	qDebug() << "imageSource.size(): " << imageSource.size();
	qDebug() << "imageSource.at(0): " << imageSource.at(0).c_str();
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



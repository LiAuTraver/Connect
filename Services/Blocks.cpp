#include <Services/Blocks.hpp>
#include <include/config.hpp>


//const std::string_view Connect::Blocks::IMAGE_PATH = {std::filesystem::current_path().string() + "Resources/images"};
const std::string_view Connect::Blocks::IMAGE_PATH = {R"(M:/Projects/Connect/Resources/images)"};

Connect::Blocks::Blocks() : height(0), width(0), total(0), path("") {}

Connect::Blocks::Blocks(std::string_view path) : path(path) {}

Connect::Blocks::Blocks(Connect::Blocks::size_type h, Connect::Blocks::size_type w) {
	reset(h, w);
}

Connect::Blocks::Blocks(Connect::Blocks::size_type h, Connect::Blocks::size_type w, const std::string_view path) {
	reset(h, w, path);
}

Connect::Blocks &Connect::Blocks::reset(Connect::Blocks::size_type h, Connect::Blocks::size_type w,
                                        const std::string_view importPath) {
	height = h;
	width = w;
	total = height * width;
	imageSource.clear();
	imageSource.resize(total);
	this->path = importPath;
	if (importPath.empty()) {
		qDebug() << "Path is empty";
		return *this;
	}
	return this->Oninitialize();
}

_NODISCARD Connect::Blocks::size_type Connect::Blocks::getTotal() noexcept {
	return total = height * width, total;
}


_NODISCARD const std::vector<std::string> &Connect::Blocks::getImagePath() const noexcept {
	return imageSource;
}


_NODISCARD Connect::Blocks::size_type Connect::Blocks::getRows() const noexcept {
	return height;
}


_NODISCARD Connect::Blocks::size_type Connect::Blocks::getCols() const noexcept {
	return width;
}

Connect::Blocks &Connect::Blocks::initializeImagePaths() {
	imageSource.clear();
	if (this->path.empty() or not std::filesystem::exists(this->path)) {
		qDebug() << "invalid path: " << path.string();
		throw std::invalid_argument("Path not exists");
	}
	// recursively search for all files in the directory using std::filesystem
	for (const auto &entry: std::filesystem::recursive_directory_iterator(path))
		if (entry.is_regular_file())
			imageSource.push_back(entry.path().string());
	qDebug() << "imageSource.size(): " << imageSource.size();
	qDebug() << "imageSource.at(0): " << imageSource.at(0).c_str();
	return *this;
}

_NODISCARD CONNECT_FORCE_INLINE const char *Connect::Blocks::generateImagePath() const {

	static std::random_device rd;
	static std::mt19937_64 gen(rd());
	std::uniform_int_distribution<size_type> dis(0, static_cast<size_type>((imageSource.size() - 1 > 0 ?
	                                                                        imageSource.size() - 1 : 0)));
	return imageSource.at(dis(gen)).c_str();
}

Connect::Blocks &Connect::Blocks::initializeImageGrid() {
	imageGrid.resize(height * width);
	for (auto y = 0LL; y < height; y++)
		for (auto x = 0LL; x < width; x++)
			this->operator()(y, x) = this->generateImagePath();
	return *this;
}

Connect::Blocks &Connect::Blocks::Oninitialize() {

	return (*this)
			.initializeImagePaths()
			.initializeImageGrid();
}

#include <Services/Blocks.hpp>
#include <include/config.hpp>

#include "Helpers/ResourcesSerializer.hpp"

CONNECT_NAMESPACE_BEGIN
CONNECT_OPT_1_NAMESPACE_BEGIN

Blocks::Blocks(const size_type h, const size_type w) { reset(h, w); }

Blocks &Blocks::reset(const size_type h, const size_type w) {
	height = h;
	width = w;
	total = height * width;
	imageSource.clear();
	imageSource.resize(total);
	return this->Oninitialize();
}

_NODISCARD Blocks::size_type Blocks::getTotal() noexcept { return total = height * width, total; }

_NODISCARD const std::vector<QString> &Blocks::getImagePath() const noexcept { return imageSource; }

_NODISCARD Blocks::size_type Blocks::getRows() const noexcept { return height; }

_NODISCARD Blocks::size_type Blocks::getCols() const noexcept { return width; }

_NODISCARD CONNECT_FORCE_INLINE QString Blocks::generateImagePath() const {
	static std::random_device rd;
	static std::mt19937_64 gen(rd());
	const auto imageCount = imageSource.size();
	// @note: cannot write
	//		@code const auto imageCount = imageSource.size() - 1;
	//			  if(imageCount < 0)return{};
	//		@endcode
	// because imageCount is a size_t which will never less than 0.
	if (imageCount - 1 < 0)
		return {};
	std::uniform_int_distribution<size_type> dis(0, static_cast<long long>(imageCount) - 1);
	return imageSource.at(dis(gen));
}

Blocks &Blocks::initializeImageGrid() {
	imageGrid.resize(height * width);
	for (auto y = 0LL; y < height; y++)
		for (auto x = 0LL; x < width; x++)
			if (const auto soloPath = this->generateImagePath(); not soloPath.isEmpty())
				this->operator()(y, x) = soloPath;
	return *this;
}

Blocks &Blocks::Oninitialize() {
	if (auto status = this->initializeImagePaths())
		qWarning() << status.value();
	return this->initializeImageGrid();
}
std::optional<std::string_view> Blocks::initializeImagePaths() {
	try {
		auto imageSourceOpt =
			ResourcesSerializer.deserialise(std::filesystem::current_path() / "resources.json");
		if (not imageSourceOpt)
			return std::nullopt;
		auto it = imageSourceOpt.value().find("images");
		if (it == imageSourceOpt.value().cend())
			return std::nullopt;
		imageSource = std::move(  // can't be `qrc:/images/`. dunno why.
			it->second | std::views::transform([&](auto &&str) { return ":/images/" + str; }) |
			std::ranges::to<decltype(imageSource)>());
		return std::nullopt;
	} catch (std::exception &e) {
		return e.what();
	} catch (std::error_code &e) {
		return e.message();
	} catch (...) {
		return "Unknown exception occurred.";
	}
}
CONNECT_OPT_1_NAMESPACE_END
CONNECT_OPT_2_NAMESPACE_BEGIN
#pragma region folded
// const std::string_view Blocks::IMAGE_PATH = {std::filesystem::current_path().string() +
// "Resources/images"};
const std::string_view Blocks::IMAGE_PATH = {R"(M:/Projects/Connect/Resources/images)"};

Blocks::Blocks() : imageSourcePath("") {}

Blocks::Blocks(const std::string_view path) : imageSourcePath(path) {}

Blocks::Blocks(const size_type h, const size_type w) { reset(h, w); }

Blocks::Blocks(const size_type h, const size_type w, const std::string_view path) {
	reset(h, w, path);
}

Blocks &Blocks::reset(const size_type h, const size_type w, const std::string_view importPath) {
	height = h;
	width = w;
	total = height * width;
	imageSource.clear();
	imageSource.resize(total);
	this->imageSourcePath = importPath;
	if (importPath.empty()) {
		qDebug() << "Path is empty";
		return *this;
	}
	return this->Oninitialize();
}

_NODISCARD Blocks::size_type Blocks::getTotal() noexcept { return total = height * width, total; }

_NODISCARD const std::vector<std::string> &Blocks::getImagePath() const noexcept {
	return imageSource;
}

_NODISCARD Blocks::size_type Blocks::getRows() const noexcept { return height; }

_NODISCARD Blocks::size_type Blocks::getCols() const noexcept { return width; }

std::optional<std::string_view> Blocks::initializeImagePaths(
	const std::string_view filePath = IMAGE_PATH) {
	imageSourcePath = filePath;
	imageSource.clear();
	try {
		if (this->imageSourcePath.empty() or not exists(this->imageSourcePath))
			return fmt::format("Invalid Path: {}", imageSourcePath.string());

		// recursively search for all files in the directory using std::filesystem
		for (const auto &entry : std::filesystem::recursive_directory_iterator(imageSourcePath))
			if (entry.is_regular_file())
				imageSource.push_back(entry.path().string());
		qDebug() << "imageSource.size(): " << imageSource.size();
		qDebug() << "imageSource.at(0): " << imageSource.at(0).c_str();
		return std::nullopt;
	} catch (std::exception &e) {
		return e.what();
	} catch (std::error_code &e) {
		return e.message();
	} catch (...) {
		return "Unknown exception occurred.";
	}
}

_NODISCARD CONNECT_FORCE_INLINE const char *Blocks::generateImagePath() const {
	static std::random_device rd;
	static std::mt19937_64 gen(rd());
	const auto imageCount = imageSource.size();
	// @note: cannot write
	//		@code const auto imageCount = imageSource.size() - 1;
	//			  if(imageCount < 0)return{};
	//		@endcode
	// because imageCount is a size_t which will never less than 0.
	if (imageCount - 1 < 0)
		return {};
	std::uniform_int_distribution<size_type> dis(0, static_cast<long long>(imageCount) - 1);
	return imageSource.at(dis(gen)).c_str();
}

Blocks &Blocks::initializeImageGrid() {
	imageGrid.resize(height * width);
	for (auto y = 0LL; y < height; y++)
		for (auto x = 0LL; x < width; x++)
			if (const auto soloPath = this->generateImagePath())
				this->operator()(y, x) = soloPath;
	return *this;
}

Blocks &Blocks::Oninitialize() {
	if (auto status = this->initializeImagePaths())
		qWarning() << status.value();
	return this->initializeImageGrid();
}
#pragma endregion
CONNECT_OPT_2_NAMESPACE_END
CONNECT_NAMESPACE_END
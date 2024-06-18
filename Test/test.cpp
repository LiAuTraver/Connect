#include <pch/qt.core.hh>
#include <pch/qt.xml.hh>
#include <pch/std.container.hh>
#include <pch/fmt.hh>

int main(int argc, char *argv[]) {
	QDir dir(R"(M:/Projects/Connect)");
	// print current directory
	fmt::print("Current directory: {}\n", dir.currentPath().toStdString()); // C:/Qt/6.6.3/msvc2019_64/bin
	fmt::print("Current directory: {}\n", dir.absolutePath().toStdString()); // project root
	fmt::print("Current directory: {}\n", dir.canonicalPath().toStdString()); // project root

	QCoreApplication app(argc, argv);

	std::vector<std::string> imageSource;

	// Load the XML file
//	QFile file(R"(M:/Projects/Connect/resources.qrc)");
	QFile file(dir.absolutePath() + "/resources.qrc");
	if (!file.open(QIODevice::ReadOnly)) {
		std::cerr << "Failed to open file\n";
		return -1;
	}

	QDomDocument doc;
	if (!doc.setContent(&file)) {
		std::cerr << "Failed to parse XML content\n";
		file.close();
		return -1;
	}
	// print the whole file for debugging
//	fmt::print("{}\n", doc.toString().toStdString());
	file.close();

	// Get the root element
	QDomElement root = doc.documentElement();

	// Iterate over all <file> elements
	QDomNodeList fileList = root.elementsByTagName("file");
	for (int i = 0; i < fileList.count(); ++i)
		if (auto alias = fileList.at(i).toElement().attribute("alias"); not alias.isEmpty())
			imageSource.push_back(alias.toStdString());
	int i = 0;
	// Print the contents of imageSource
	for (const auto &src: imageSource) {
		std::cout << src << std::endl;
		i++;
		if (i == 10) {
			break;
		}
	}
}
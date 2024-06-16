#include <pch/qt.core.hh>
#include <pch/qt.gui.hh>
#include <pch/qt.widgets.hh>
#include <nlohmann/json.hpp>
#include <include/menu.hpp>
#include <pch/absl.log.hh>
#include <include/mainwindow.hpp>
#include <include/config.hpp>
int main(int argc, char *argv[]) {
	absl::InitializeLog();
	LOG(INFO) << "App Started.";
	qDebug () << "App started.";
	QApplication connectApp(argc,argv);
	Connect::MainWindow mainWindow(nullptr);
	mainWindow.show();
	LOG(INFO) << "Main window showed.";
	qDebug() << "Main window showed.";
	return QApplication::exec();
}

//#include <QCoreApplication>
//#include <QDomDocument>
//#include <QFile>
//#include <QString>
//#include <QTextStream>
//#include <vector>
//#include <string>
//#include <iostream>
//
//int main(int argc, char *argv[]) {
//	QCoreApplication app(argc, argv);
//
//	std::vector<std::string> imageSource;
//
//	// Load the XML file
//	QFile file(R"(M:/Projects/Connect/resources.qrc)");
//	if (!file.open(QIODevice::ReadOnly)) {
//		std::cerr << "Failed to open file\n";
//		return -1;
//	}
//
//	QDomDocument doc;
//	if (!doc.setContent(&file)) {
//		std::cerr << "Failed to parse XML content\n";
//		file.close();
//		return -1;
//	}
//	file.close();
//
//	// Get the root element
//	QDomElement root = doc.documentElement();
//
//	// Iterate over all <file> elements
//	QDomNodeList fileList = root.elementsByTagName("file");
//	for (int i = 0; i < fileList.count(); ++i) {
//		QDomElement element = fileList.at(i).toElement();
//		QString alias = element.attribute("alias");
//		if (!alias.isEmpty()) {
//			imageSource.push_back(alias.toStdString());
//		}
//	}
//
//	// Print the contents of imageSource
//	for (const std::string& src : imageSource) {
//		std::cout << src << std::endl;
//	}
//
//	return 0;
//}
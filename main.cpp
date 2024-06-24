#include <Views/mainwindow.hpp>
#include <nlohmann/json.hpp>
#include <pch/absl.log.hh>
#include <pch/qt.core.hh>
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

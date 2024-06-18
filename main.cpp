#include <pch/qt.core.hh>
#include <pch/qt.gui.hh>
#include <pch/qt.widgets.hh>
#include <nlohmann/json.hpp>
#include <ViewModels/menu.hpp>
#include <pch/absl.log.hh>
#include <Views/mainwindow.hpp>
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

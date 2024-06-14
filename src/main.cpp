#include <pch/qCore.hh>
#include <pch/qGui.hh>
#include <pch/qWidgets.hh>
#include <src/menu.hpp>
#include <pch/absl.log.hh>
#include <src/mainwindow.hpp>
#include <include/config.hpp>
#include <nlohmann/json.hpp>
int main(int argc, char *argv[]) {
	absl::InitializeLog();
	LOG(INFO) << "App Started.";
	QApplication connectApp(argc,argv);
	Connect::MainWindow mainWindow(nullptr);
	mainWindow.show();
	LOG(INFO) << "Main window showed.";
	return QApplication::exec();
}

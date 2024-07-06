/**
 * @author lyc.
 * @copyright lyc.
 * @details 2024 CS project at HDU.
 */

#include <Views/mainwindow.hpp>
#include <pch/absl.log.hh>
#include <pch/qt.core.hh>

/**
 * @brief Initialize the logging system: for the `LOG()` macro to work properly,
 * @brief and call `Q_INIT_RESOURCE` before loaded audios and images; otherwise `qrc` file would not
 * be loaded correctly.
 * @return The static lambda function cannot return a void, so I made it return an `absl::Status`.
 * @note `static` and `()` at the end are used to initialize the logging system before the `main`
 * function is called.
 */
[[maybe_unused]] static const auto initialization = []() -> absl::Status {
	Q_INIT_RESOURCE(resources);
	qDebug("resources initialized successfully.");
	absl::InitializeLog();
	LOG(INFO) << "abseil log initialized successfully.";
	return absl::OkStatus();
}();

/**
 * @brief Main entry point of the application.
 * @note The `main` isn't actually the `main` function: the `main` function is used by Qt; Qt Moc
 * will define this `main` as something else and call it in the background.
 * @note QObject without parent, like QGuiApplication/QApplication, QMainWindow here, should be
 * allocated on stack, not heap.
 */
int main(int argc, char *argv[]) {
	LOG(INFO) << "App Started.";
	qDebug() << "App started.";
	// the main class of the Qt Widgets module: Qt-built-in class.
	QApplication connectApp(argc, argv);
	/**
	 * @brief The main window of the application: user-implemented class.
	 *			nullptr as parent: Qt will manage the memory;
	 *			QWidget with no parent will be showed as a separate window;
	 *			who cares an object went out of scope in function `main`?
	 */
	Connect::MainWindow mainWindow(nullptr);
	// show the main window.
	mainWindow.show();
	LOG(INFO) << "Main window showed.";
	qDebug() << "Main window showed.";
	/**
	 * @brief the main loop of the application: wait for user interaction:
	 *			if the user closes the window,the app will exit.
	 * @note: the actual loop was implemented in Qt's source code, not here.
	 */
	return connectApp.exec();  // NOLINT(*-static-accessed-through-instance)
}

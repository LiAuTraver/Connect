// #include <QApplication>
// #include <QTableView>
// #include <QStandardItemModel>
// #include <QVBoxLayout>
// #include <QWidget>
//
// int main(int argc, char *argv[]) {
// 	QApplication app(argc, argv);
//
// 	QWidget window;
// 	window.setWindowTitle("QTableView Example");
//
// 	QTableView *tableView = new QTableView(&window);
//
// 	// Create a model with 5 rows and 3 columns
// 	QStandardItemModel *model = new QStandardItemModel(5, 3, &window);
// 	model->setHorizontalHeaderLabels({"Column 1", "Column 2", "Column 3"});
//
// 	// Fill the model with some data
// 	for (int row = 0; row < 5; ++row) {
// 		for (int column = 0; column < 3; ++column) {
// 			QStandardItem *item = new QStandardItem(QString("Item %1-%2").arg(row + 1).arg(column + 1));
// 			model->setItem(row, column, item);
// 		}
// 	}
//
// 	tableView->setModel(model);
//
// 	QVBoxLayout *layout = new QVBoxLayout(&window);
// 	layout->addWidget(tableView);
//
// 	window.setLayout(layout);
// 	window.resize(400, 300);
// 	window.show();
//
// 	return app.exec();
// }



// #include <QApplication>
// #include <QTableWidget>
// #include <QVBoxLayout>
// #include <QWidget>
//
// int main(int argc, char *argv[]) {
// 	QApplication app(argc, argv);
//
// 	QWidget window;
// 	window.setWindowTitle("QTableWidget Example");
//
// 	QTableWidget *tableWidget = new QTableWidget(5, 3, &window); // 5 rows, 3 columns
// 	tableWidget->setHorizontalHeaderLabels({"Column 1", "Column 2", "Column 3"});
//
// 	// Fill the table with some data
// 	for (int row = 0; row < 5; ++row) {
// 		for (int column = 0; column < 3; ++column) {
// 			QTableWidgetItem *item = new QTableWidgetItem(QString("Item %1-%2").arg(row + 1).arg(column + 1));
// 			tableWidget->setItem(row, column, item);
// 		}
// 	}
//
// 	QVBoxLayout *layout = new QVBoxLayout(&window);
// 	layout->addWidget(tableWidget);
//
// 	window.setLayout(layout);
// 	window.resize(400, 300);
// 	window.show();
//
// 	return app.exec();
// }
//


#include <QApplication>
#include <QMainWindow>
#include <QFileDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <Services/Records.hpp>
#include <Models/Record.hpp>

class MainWindow : public QMainWindow {
Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
		auto *button = new QPushButton("Open File", this);
		auto *label = new QLabel("No file selected", this);

		connect(button, &QPushButton::clicked, this, [this, label]() {
			QString fileName = QFileDialog::getOpenFileName(this, "Open File", "",
			                                                "All Files (*.*);;Text Files (*.txt);;Images (*.png *.jpg)");

			if (!fileName.isEmpty()) {
				label->setText("Selected file: " + fileName);
			}
		});

		auto *layout = new QVBoxLayout;
		layout->addWidget(button);
		layout->addWidget(label);

		auto *widget = new QWidget(this);
		widget->setLayout(layout);
		setCentralWidget(widget);
	}
};

int main(int argc, char *argv[]) {
	// absl::InitializeLog();
//	QApplication app(argc, argv);
//
//	MainWindow mainWindow;
//	mainWindow.resize(400, 300);
//	mainWindow.show();
//	return QApplication::exec();
	Connect::Records records;
	records.OnInitialize();
	records.printRecords();// success!
	auto opt = std::optional{3};
	try {
		opt = std::nullopt;
		auto _ = opt.value();
	}catch (std::exception& e) {
		fmt::println("{}",e.what());
	}
}

#include "test.moc"

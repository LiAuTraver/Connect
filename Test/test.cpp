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
//	QApplication app(argc, argv);
//
//	MainWindow mainWindow;
//	mainWindow.resize(400, 300);
//	mainWindow.show();
//	return QApplication::exec();
	Connect::Records records;
	records.OnInitialize();
	records.printRecords();// success!
}

#include "test.moc"

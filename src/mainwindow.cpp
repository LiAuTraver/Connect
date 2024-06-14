#include "mainwindow.hpp"
#include "ui_MainWindow.h"

CONNECT_NAMESPACE_BEGIN
MainWindow::MainWindow(QWidget *parent) :
		QMainWindow(parent),
		ui(new Connect::Ui::MainWindow),
		menu(new Connect::Menu(this)),
		game(new Connect::Game(this)) {
	this->ui->setupUi(this);
	this->setCentralWidget(menu);
}

MainWindow::~MainWindow() {
	delete ui; // (?)
	// no need to delete custom widgets: they are deleted by their parent(parent-child relationship)
}
CONNECT_NAMESPACE_END

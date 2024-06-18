#include "mainwindow.hpp"
#include "ui_MainWindow.h"

CONNECT_NAMESPACE_BEGIN
MainWindow::MainWindow(QWidget *parent) :
		QMainWindow(parent), ui(new Connect::Ui::MainWindow), menu(new Connect::Menu(this)),
		game(nullptr) // Initialize game to nullptr, create it only when needed
{
	this->ui->setupUi(this);
	this->setCentralWidget(menu);
	QWidget::connect(menu, &Connect::Menu::OnStartButtonClicked, this, &Connect::MainWindow::onGameStart);
	QWidget::connect(this->ui->action_Quit, &QAction::triggered, qApp, &QApplication::quit);
}

MainWindow::~MainWindow() {
	delete ui; // (?)
	// no need to delete custom widgets: they are deleted by their parent(parent-child relationship)
}

void MainWindow::onGameStart() {
	if (not game) {
		this->game = new Connect::Game(this);
	}
	this->setCentralWidget(game);
	Connect::MainWindow::destroyChildWidget(menu); // destroy for now
}

void MainWindow::onGameExit() {
	if (not menu) {
		this->menu = new Connect::Menu(this);
	}
	this->setCentralWidget(menu);
	Connect::MainWindow::destroyChildWidget(game); // destroy for now
}

void MainWindow::destroyChildWidget(QWidget *childWidget) {
	delete childWidget;
	childWidget = nullptr;
}


CONNECT_NAMESPACE_END

#include "mainwindow.hpp"

//! if use Qt ui file (in Qt Designer) then we shall include this `ui_{class name}.h`
#include "ui_MainWindow.h"

CONNECT_NAMESPACE_BEGIN
MainWindow::MainWindow(QWidget *parent) :
		QMainWindow(parent), ui(new Connect::Ui::MainWindow), menu(new Connect::Menu(this)),
		game(nullptr) //! Initialize game to nullptr, create it only when needed
{
	this->ui->setupUi(this);
	this->setCentralWidget(menu);
	QWidget::connect(menu, &Connect::Menu::onStartButtonClicked, this, &Connect::MainWindow::handleGameStart);
	QWidget::connect(this->ui->action_Quit, &QAction::triggered, qApp, &QApplication::quit);
}

MainWindow::~MainWindow() {
	//! no need to delete custom widgets: they are deleted by their parent (parent-child relationship)
	delete ui; //! needed, see note in `game.cpp`
}

void MainWindow::handleGameStart() {
	if (not game) {
		this->game = new Connect::Game(this);
	}
	this->setCentralWidget(game);
	Connect::MainWindow::destroyChildWidget(menu); // destroy for now
}

void MainWindow::handleGameExit() {
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

Connect::StatusWidget& Connect::StatusWidget::onButtonEliminate(QPushButton *button) {
	auto buttonOpacityEffect = new QGraphicsOpacityEffect(button);
	button->setGraphicsEffect(buttonOpacityEffect);
	auto animation = new QPropertyAnimation(buttonOpacityEffect, "opacity");
	animation->setDuration(1000);
	animation->setStartValue(1);
	animation->setEndValue(0);
	QWidget::connect(animation, &QPropertyAnimation::finished, button, &QPushButton::hide);
	animation->start(QAbstractAnimation::DeleteWhenStopped);
	return *this;
}

CONNECT_NAMESPACE_END

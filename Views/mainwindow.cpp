#include "mainwindow.hpp"

//! note: if use Qt ui file (in Qt Designer) then we shall include this `ui_{class name}.h`
#include "Helpers/Animation.hpp"
#include "ui_MainWindow.h"

Connect::MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent), ui(new Connect::Ui::MainWindow), menu(new Connect::Menu(this)), game(nullptr),
	leaderboard(nullptr), about(nullptr) //! note: Initialize to nullptr, create it only when needed
{
	this->ui->setupUi(this);
	this->setCentralWidget(menu);
	this->initializeConnections();
}
Connect::MainWindow::~MainWindow() {
	//! note: no need to delete custom widgets: they are deleted by their parent (parent-child relationship)
	delete ui; //! note: needed, see note in `game.cpp`
}
void Connect::MainWindow::handleGameStart() {
	if (not game)
		this->game = new Connect::Game(this);
	menu = dynamic_cast<Menu *>(this->takeCentralWidget());
	this->setCentralWidget(game);
	// this->destroyChildWidget(menu); // destroy for now
}
void Connect::MainWindow::handleLeaderboardStart() {
	if (not leaderboard)
		this->leaderboard = new Connect::Leaderboard(this);
	menu = dynamic_cast<Menu *>(this->takeCentralWidget());
	this->setCentralWidget(leaderboard);
	// this->destroyChildWidget(menu);
}
void Connect::MainWindow::handleAboutPageStart() {
	if (not about)
		this->about = new Connect::About(this);
	menu = dynamic_cast<Menu *>(this->takeCentralWidget());
	this->setCentralWidget(about);
	QWidget::connect(about, &Connect::About::onCloseButtonCicked, this, &Connect::MainWindow::handleAboutExit);
	// this->destroyChildWidget(menu);
}
void Connect::MainWindow::handleGameExit() {
	if (not menu)
		this->menu = new Connect::Menu(this);
	game = dynamic_cast<Game *>(this->takeCentralWidget());
	this->setCentralWidget(menu);
	// this->destroyChildWidget(game); // fixme: destroy for now
}
void Connect::MainWindow::handleAboutExit() {
	if (not menu)
		this->menu = new Connect::Menu(this);
	about = dynamic_cast<About *>(this->takeCentralWidget());
	this->setCentralWidget(menu);
	// this->destroyChildWidget(about);
}
//! note: delete a pointer MUST USE REFERENCE!!!
void Connect::MainWindow::destroyChildWidget(auto *&childWidget) {
	delete childWidget;
	childWidget = nullptr;
}
void Connect::MainWindow::initializeConnections() {
	this->initializeMenuConnections();
	QWidget::connect(this->ui->action_Quit, &QAction::triggered, qApp, &QApplication::quit);
}
void Connect::MainWindow::initializeMenuConnections() {
	QWidget::connect(menu, &Connect::Menu::onStartButtonClicked, this, &Connect::MainWindow::handleGameStart);
	QWidget::connect(menu, &Connect::Menu::onRecordButtonClicked, this, &Connect::MainWindow::handleLeaderboardStart);
	QWidget::connect(menu, &Connect::Menu::onAboutButtonClicked, this, &Connect::MainWindow::handleAboutPageStart);
}
Connect::StatusWidget &Connect::StatusWidget::onButtonEliminate(QPushButton *button) {
	Animation(button);
	return *this;
}

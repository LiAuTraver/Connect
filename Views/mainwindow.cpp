#include <Helpers/Animation.hpp>
#include <Views/mainwindow.hpp>
//! note: if use Qt ui file (in Qt Designer) then we shall include this `ui_{class name}.h`
#include "ui_MainWindow.h"

Connect::MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent), ui(new Ui::MainWindow), menu(new Menu(this)), game(nullptr), leaderboard(nullptr),
	about(nullptr) //! note: Initialize to nullptr, create it only when needed
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
		this->game = new Game(this);
	menu = dynamic_cast<Menu *>(this->takeCentralWidget()); //! Qt Gui take the widget away I must take back
	this->setCentralWidget(game);
	// this->destroyChildWidget(menu);
}
void Connect::MainWindow::handleLeaderboardStart() {
	if (not leaderboard)
		this->leaderboard = new Leaderboard(this);
	menu = dynamic_cast<Menu *>(this->takeCentralWidget());
	connect(leaderboard, &Leaderboard::onCloseButtonClicked, this, &MainWindow::handleLeaderboardExit);
	this->setCentralWidget(leaderboard);
	// this->destroyChildWidget(menu);
}
void Connect::MainWindow::handleAboutPageStart() {
	if (not about)
		this->about = new About(this);
	menu = dynamic_cast<Menu *>(this->takeCentralWidget());
	connect(about, &About::onCloseButtonCicked, this, &MainWindow::handleAboutExit);
	this->setCentralWidget(about);
	// this->destroyChildWidget(menu);
}
void Connect::MainWindow::handleGameExit() {
	if (not menu)
		this->menu = new Menu(this);
	game = dynamic_cast<Game *>(this->takeCentralWidget());
	this->setCentralWidget(menu);
	// this->destroyChildWidget(game); // fixme: destroy for now
}
void Connect::MainWindow::handleAboutExit() {
	if (not menu)
		this->menu = new Menu(this);
	about = dynamic_cast<About *>(this->takeCentralWidget());
	this->setCentralWidget(menu);
	// this->destroyChildWidget(about);
}
void Connect::MainWindow::handleLeaderboardExit() {
	if (not menu)
		this->menu = new Menu(this);
	leaderboard = dynamic_cast<Leaderboard *>(this->takeCentralWidget());
	this->setCentralWidget(menu);
}
//! note: delete a pointer MUST USE REFERENCE!!!
void Connect::MainWindow::destroyChildWidget(auto *&childWidget) {
	delete childWidget;
	childWidget = nullptr;
}
void Connect::MainWindow::initializeConnections() {
	this->initializeMenuConnections();
	connect(this->ui->action_Quit, &QAction::triggered, qApp, &QApplication::quit);
}
void Connect::MainWindow::initializeMenuConnections() {
	connect(menu, &Menu::onStartButtonClicked, this, &MainWindow::handleGameStart);
	connect(menu, &Menu::onRecordButtonClicked, this, &MainWindow::handleLeaderboardStart);
	connect(menu, &Menu::onAboutButtonClicked, this, &MainWindow::handleAboutPageStart);
}
Connect::StatusWidget &Connect::StatusWidget::onButtonEliminate(QPushButton *button) {
	Animation(button);
	return *this;
}

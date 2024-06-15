#include "include/mainwindow.hpp"
#include "ui_MainWindow.h"

CONNECT_NAMESPACE_BEGIN
MainWindow::MainWindow(QWidget *parent) :
		QMainWindow(parent)
		,ui(new Connect::Ui::MainWindow)
		,menu(new Connect::Menu(this))
		,game(nullptr) // Initialize game to nullptr, create it only when needed
		{
	this->ui->setupUi(this);
	this->setCentralWidget(menu);
	connect(menu,&Connect::Menu::OnStartButtonClicked, this, &Connect::MainWindow::startGame);
}

MainWindow::~MainWindow() {
	delete ui; // (?)
	// no need to delete custom widgets: they are deleted by their parent(parent-child relationship)
}

void MainWindow::startGame() {
	if(not game){
		this->game = new Connect::Game(this);
	}
	this->setCentralWidget(game);
	Connect::MainWindow::destroyChildWidget(menu); // destroy for now
}

void MainWindow::destroyChildWidget(QWidget *childWidget) {
	delete childWidget;
	childWidget = nullptr;
}
CONNECT_NAMESPACE_END

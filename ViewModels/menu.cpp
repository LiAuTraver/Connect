#include "menu.hpp"
#include "ui_Menu.h"

CONNECT_NAMESPACE_BEGIN
Menu::Menu(QWidget *parent) :
		QWidget(parent), ui(new Ui::Menu) {
	ui->setupUi(this);
	connect(ui->pushButtonExit,&QPushButton::clicked ,qApp,&QApplication::quit);
	connect(ui->pushButtonAbout,&QPushButton::clicked,this,&Menu::debug);
	connect(ui->pushButtonStart,&QPushButton::clicked,this,&Menu::OnStartButtonClicked);
}

Menu::~Menu() {
	delete ui;
}

void Menu::debug() {
	qDebug()<< " about button clicked.";
}
CONNECT_NAMESPACE_END

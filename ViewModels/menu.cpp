#include "menu.hpp"
#include "ui_Menu.h"

CONNECT_NAMESPACE_BEGIN
Menu::Menu(QWidget *parent) :
		QWidget(parent), ui(new Ui::Menu) {
	ui->setupUi(this);
	QWidget::connect(ui->pushButtonExit,&QPushButton::clicked ,qApp,&QApplication::quit);
	QWidget::connect(ui->pushButtonAbout,&QPushButton::clicked,this,&Menu::onAboutButtonClicked);
	QWidget::connect(ui->pushButtonStart,&QPushButton::clicked,this, &Menu::onStartButtonClicked);
	QWidget::connect(ui->pushButtonRecord,&QPushButton::clicked,this,&Menu::onRecordButtonClicked);
}

Menu::~Menu() {
	delete ui;
}

void Menu::debug() {
	qDebug()<< " about button clicked.";
}
CONNECT_NAMESPACE_END

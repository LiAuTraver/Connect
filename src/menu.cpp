#include "menu.hpp"
#include "ui_Menu.h"

CONNECT_NAMESPACE_BEGIN
Menu::Menu(QWidget *parent) :
		QWidget(parent), ui(new Ui::Menu) {
	ui->setupUi(this);
}

Menu::~Menu() {
	delete ui;
}
CONNECT_NAMESPACE_END

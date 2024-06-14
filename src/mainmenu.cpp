// You may need to build the project (run Qt uic code generator) to get "ui_MainMenu.h" resolved

#include "mainmenu.hpp"
#include "ui_MainMenu.h"

namespace Connect {
MainMenu::MainMenu(QWidget *parent) :
		QWidget(parent), ui(new Ui::MainMenu) {
	ui->setupUi(this);
}

MainMenu::~MainMenu() {
	delete ui;
}
} // Connect

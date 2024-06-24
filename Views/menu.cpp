#include <Views/menu.hpp>
#include "ui_Menu.h"

Connect::Menu::Menu(QWidget *parent) : QWidget(parent), ui(new Ui::Menu) {
	ui->setupUi(this);
	this->OnInitialize();
}

Connect::Menu::~Menu() { delete ui; }
void Connect::Menu::OnInitialize() {
	QWidget::connect(ui->pushButtonExit, &QPushButton::clicked, qApp, &QApplication::quit);
	QWidget::connect(ui->pushButtonAbout, &QPushButton::clicked, this, &Menu::onAboutButtonClicked);
	QWidget::connect(ui->pushButtonStart, &QPushButton::clicked, this, &Menu::onStartButtonClicked);
	QWidget::connect(ui->pushButtonRecord, &QPushButton::clicked, this, &Menu::onRecordButtonClicked);
}

void Connect::Menu::debug() { qDebug() << " about button clicked."; }


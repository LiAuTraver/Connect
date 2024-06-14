#include "game.hpp"
#include "ui_Game.h"

CONNECT_NAMESPACE_BEGIN
Game::Game(QWidget *parent) :
		QWidget(parent), ui(new Ui::Game) {
	ui->setupUi(this);
}

Game::~Game() {
	delete ui;
}
CONNECT_NAMESPACE_END

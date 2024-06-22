#include "leaderboard.hpp"
#include "ui_Leaderboard.h"
#include <include/config.hpp>

Connect::Leaderboard::Leaderboard(QWidget *parent) :
		QWidget(parent),
		leaderboardLayout(new QHBoxLayout(this)),
		ui(new Ui::Leaderboard) {
	ui->setupUi(this);
}

Connect::Leaderboard::~Leaderboard() {
	delete ui;
}


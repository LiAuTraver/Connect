#include "leaderboardwidget.hpp"
#include "ui_LeaderBoardWidget.h"
#include <include/config.hpp>

Connect::LeaderboardWidget::LeaderboardWidget(QWidget *parent) :
		QWidget(parent),
		leaderboardLayout(new QHBoxLayout(this)),
		ui(new Ui::LeaderboardWidget) {
	ui->setupUi(this);
}

Connect::LeaderboardWidget::~LeaderboardWidget() {
	delete ui;
}


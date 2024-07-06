#include <ViewModels/pastgamewidget.hpp>

#include "ui_PastGameWidget.h"

constinit const char* Connect::PastGameWidget::GAME_OVER = "Game Over!";

constinit const char* Connect::PastGameWidget::YOU_WIN = "You Win!";

Connect::PastGameWidget::PastGameWidget(QWidget* parent)
	: QWidget(parent), ui(new Ui::PastGameWidget) {
	ui->setupUi(this);

	connect(this->ui->toMenuButton, &QPushButton::clicked, this,
			[this]() { emit this->NavigateToSuper(BackToMenu); });
	connect(this->ui->replayButton, &QPushButton::clicked, this,
			[this]() { emit this->NavigateToSuper(ReplayGame); });
	connect(this->ui->toLeaderboardButton, &QPushButton::clicked, this,
			[this]() { emit this->NavigateToSuper(ToLeaderboard); });
}

Connect::PastGameWidget::~PastGameWidget() { delete ui; }

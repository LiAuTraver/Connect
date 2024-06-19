#include <ViewModels/game.hpp>
#include <Services/Blocks.hpp>
#include <Helpers/NotImplementedException.hpp>
#include "ui_Game.h"

Connect::Game::Game(QWidget *parent) :
		QWidget(parent),
		ui(new Ui::Game),
		mainLayout(new QVBoxLayout(this)),
		gameWidget(new GameWidget(this)),
		statusWidget(new StatusWidget(this)),
		isPaused(false) {
	this->OnInitialize();
	this->statusWidget->Oninitialize();
	this->gameWidget->Oninitialize();
	this->ui->setupUi(this);
}

Connect::Game::~Game() {
	delete ui;
}

Connect::Game &Connect::Game::initializeLayout() {
	this->gameWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	this->mainLayout->addWidget(this->statusWidget);
	this->mainLayout->addWidget(this->gameWidget);
	this->setLayout(mainLayout);
	return *this;
}

CONNECT_FORCE_INLINE Connect::Game &Connect::Game::OnInitialize() {

	this->isPaused = false;
	this->initializeLayout()
			.initializeConnections();
	return *this;
}

Connect::Game &Connect::Game::win() {
	QWidget::disconnect(this->statusWidget->pauseButton, &QPushButton::toggled, this,
	                    &::Connect::Game::togglePauseResume);
	this->statusWidget->win();
	return *this;
}

_NODISCARD bool Connect::Game::checkGameCondition() {

	if (not gameWidget->isAllButtonEliminated())
		return false;
	return true;
}

void Connect::Game::togglePauseResume() {
	if (isPaused) {
		statusWidget->onPauseButtonToggled("Resume");
		gameWidget->onPauseButtonToggled("Show");
	} else {
		statusWidget->onPauseButtonToggled("Pause");
		gameWidget->onPauseButtonToggled("Hide");
	}
	isPaused = !isPaused;
}

void Connect::Game::onNavigatedFrom() {
	if (this->checkGameCondition())
		this->win();
}

Connect::Game &Connect::Game::initializeConnections() {
	// must be clicked not toggled???
	// what's even confusing is that previously `this->pauseButton` I shall use `QPushButton::toggled`
	QWidget::connect(this->statusWidget->pauseButton, &QPushButton::clicked, this, &Connect::Game::togglePauseResume);
	QWidget::connect(this->gameWidget, &Connect::GameWidget::forward, this, &Connect::Game::checkGameCondition);
	return *this;
}




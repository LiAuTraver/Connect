#include <Views/game.hpp>
#include "ui_Game.h"

Connect::Game::Game(QWidget *parent) :
	QWidget(parent), ui(new Ui::Game), mainLayout(new QVBoxLayout(this)), blocksWidget(new BlocksWidget(this)),
	statusWidget(new StatusWidget(this)), isPaused(false) {
	this->OnInitialize().ui->setupUi(this);
}

Connect::Game::~Game() {
	// note: ui (a.k.a class Connect::Game::Ui) is not a QObject and needs to be manually deleted.
	delete ui;
	// note: other members, e.g., QPushButton, do not need to be manually deleted since they are QObject and the parent
	// is the current class.
}

Connect::Game &Connect::Game::initializeLayout() {
	this->blocksWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	this->mainLayout->addWidget(this->statusWidget);
	this->mainLayout->addWidget(this->blocksWidget);
	this->setLayout(mainLayout);
	return *this;
}

CONNECT_FORCE_INLINE Connect::Game &Connect::Game::OnInitialize() {

	this->isPaused = false;
	this->initializeLayout().initializeConnections();
	return *this;
}

Connect::Game &Connect::Game::win() {
	QWidget::disconnect(this->statusWidget->pauseButton, &QPushButton::toggled, this,
						&::Connect::Game::togglePauseResume);
	this->statusWidget->win();
	return *this;
}

void Connect::Game::togglePauseResume() {
	if (isPaused) {
		statusWidget->onPauseButtonToggled("Resume");
		blocksWidget->onPauseButtonToggled("Show");
	} else {
		statusWidget->onPauseButtonToggled("Pause");
		blocksWidget->onPauseButtonToggled("Hide");
	}
	isPaused = !isPaused;
}

void Connect::Game::onNavigatedFrom() {
	if (blocksWidget->isAllButtonEliminated())
		this->win();
}

Connect::Game &Connect::Game::initializeConnections() {
	// must be clicked not toggled???
	// what's even confusing is that previously `this->pauseButton` I shall use `QPushButton::toggled`
	QWidget::connect(this->statusWidget->pauseButton, &QPushButton::clicked, this, &Connect::Game::togglePauseResume);
	QWidget::connect(this->blocksWidget, &Connect::BlocksWidget::navigateToSuper, this,
					 &Connect::Game::onNavigatedFrom);
	return *this;
}

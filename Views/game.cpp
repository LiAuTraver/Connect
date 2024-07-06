#include <ViewModels/pastgamewidget.hpp>
#include <Views/game.hpp>

#include "ui_Game.h"

Connect::Game::Game(QWidget *parent)
	: QWidget(parent),
	  ui(new Ui::Game),
	  // note: QLayout isn't a QWidget; no need to assign `this`.  vvvvvv
	  // if assigned `this`, just omit `this->setLayout(..)`.
	  mainLayout(new QVBoxLayout(this)),
	  // note: block widget was about to add into `QLayout` which is already has `this` parent; no
	  // need to assign `this` again actually. vvvvvvv
	  blocksWidget(new BlocksWidget(this)),
	  statusWidget(new StatusWidget),
	  pastGameWidget(nullptr){
	this->OnInitialize().ui->setupUi(this);
}

Connect::Game::~Game() {
	// note: ui (a.k.a class Connect::Game::Ui) is not a QObject and needs to be manually
	// deleted.
	delete ui;
	// note: other members, e.g., QPushButton, do not need to be manually deleted since
	// they are QObject and the parent is the current class.
}

Connect::Game &Connect::Game::initializeLayout() {
	this->blocksWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	// vvvvvv note: automatically set parent of `statusWidget` as `mainLayout`.
	this->mainLayout->addWidget(this->statusWidget);
	// ^^^^^^ note: even if `statusWidget` does not have a parent, as soon as it was added into
	// `mainLayout` which has a parent `this`: its safe.
	this->mainLayout->addWidget(this->blocksWidget);
	this->setLayout(mainLayout);
	return *this;
}

Connect::Game &Connect::Game::OnInitialize() {
	this->isPaused = false;
	return this->initializeLayout().initializeConnections();
}

void Connect::Game::onGameOver() {
	auto res = this->blocksWidget->isAllButtonEliminated();
	if (not res)
		return;
	auto winScore = res.value();
	auto elapsedTime = this->statusWidget->win().elapsed();

	this->mainLayout->removeWidget(statusWidget);
	this->mainLayout->removeWidget(blocksWidget);
	// FIXME: Optionally of not, shall I delete ^^^^^ those widgets explicitly or not?
	// See: https://doc.qt.io/qt-6/qlayout.html#removeWidget
	// and https://doc.qt.io/qt-6/qlayout.html#addWidget
	// but if I do not delete, the UI would mess up.
	delete statusWidget;
	delete blocksWidget;
	pastGameWidget = new PastGameWidget(this);
	connect(this->pastGameWidget, &PastGameWidget::NavigateToSuper, this, &Game::RelayFrom);
	this->mainLayout->addWidget(pastGameWidget);

	emit this->onGameWinCheckRecord(winScore, elapsedTime);
}
void Connect::Game::RelayFrom(const PastGameWidget::Option option) { emit this->RelayTo(option); }


void Connect::Game::togglePauseResume() {
	if (isPaused) {
		statusWidget->onPauseButtonToggled("Resume");
		blocksWidget->onPauseButtonToggled("Show");
	} else {
		statusWidget->onPauseButtonToggled("Pause");
		blocksWidget->onPauseButtonToggled("Hide");
	}
	isPaused = not isPaused;
}

Connect::Game &Connect::Game::initializeConnections() {
	// must be clicked not toggled???
	// what's even confusing is that previously `this->pauseButton` I shall use
	// `QPushButton::toggled`
	connect(this->statusWidget->pauseButton, &QPushButton::clicked, this, &Game::togglePauseResume);
	connect(this->blocksWidget, &BlocksWidget::navigateToSuper, this, &Game::onGameOver);
	connect(this->blocksWidget, &BlocksWidget::updateScoreLabel,this->statusWidget,&StatusWidget::updateScore);
	return *this;
}

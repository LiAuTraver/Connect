#include "include/game.hpp"
#include "ui_Game.h"
#include <include/Blocks.hpp>
#include <include/Point.hpp>
#include <include/NotImplementedException.hpp>

// dunno why but must put it here otherwise linking error
qint64 Connect::Game::pausedTime = 0;

Connect::Game::Game(QWidget *parent) :
		QWidget(parent),
		ui(new Ui::Game),
		buttons(QVector<QVector<QPushButton *>>{}),
		gridLayout(new QGridLayout(this)),
		blocks(),
		previousButton(-1, -1),
//		soundEffect(new QSoundEffect(this)),
		isPaused(false),
		elapsedTimer(),
		mediaPlayer(new QMediaPlayer(this)),
		timer(new QTimer(this)),
		timeLabel(new QLabel(this)),
		pauseButton(new QPushButton(this)),
		startTime() {
	this->OnInitialize();
	this->setLayout(this->gridLayout);
	ui->setupUi(this);
}

Connect::Game::~Game() {
	delete ui;
//	delete textEditBlock; // needed or not(?)
}

void Connect::Game::initializeGrid() {
	blocks.reset(2, 2);
	buttons.resize(blocks.getRows());
	for (auto &rowButtons: buttons)
		rowButtons.resize(blocks.getCols());
	isButtonEliminated.resize(blocks.getRows());
	for (auto &rowButtonsClicked: isButtonEliminated)
		rowButtonsClicked.resize(blocks.getCols(), false);

}

void Connect::Game::onButtonPressed(Point point) {
	qDebug() << "pressed button:" << point.y << " " << point.x;
	qDebug() << "previous:" << previousButton.y << " " << previousButton.x;
	if (previousButton == Point(-1, -1)) {
		qDebug() << "Block Pressed.";
		previousButton = point;
		// todo:change texture
		return;
	} else if (previousButton == point) {
		qDebug() << "same button pressed. ignore.";
	} else if (isSame(point)) {
		qDebug() << "ok!";
		// animation of elimination
		this->getEliminatedButtonAt(point) = true;
		this->getEliminatedButtonAt(previousButton) = true;
		onButtonEliminate(getButtonAt(point));
		onButtonEliminate(getButtonAt(previousButton));
	} else {
		qDebug() << "not the same type.";
		// todo:change back texture
	}
	previousButton = Point(-1, -1);
}

_NODISCARD bool Connect::Game::isSame(Point &point) noexcept {
	return this->blocks(point) == this->blocks(previousButton);
}

void Connect::Game::onButtonEliminate(QPushButton *button) {
	auto effect = new QGraphicsOpacityEffect(button);
	button->setGraphicsEffect(effect);
	auto animation = new QPropertyAnimation(effect, "opacity");
	animation->setDuration(1000);
	animation->setStartValue(1);
	animation->setEndValue(0);
	QWidget::connect(animation, &QPropertyAnimation::finished, button, &QPushButton::hide);
//	soundEffect->play();
	animation->start(QAbstractAnimation::DeleteWhenStopped);
}

QPushButton *&Connect::Game::getButtonAt(
		const Connect::Point &point) noexcept(noexcept(buttons[point.y][point.x])) {
	return buttons[point.y][point.x];
}

bool &Connect::Game::getEliminatedButtonAt(
		const Connect::Point &point) noexcept(noexcept(isButtonEliminated[point.y][point.x])) {
	return isButtonEliminated[point.y][point.x];
}

bool Connect::Game::getEliminatedButtonAt(const Connect::Point &point) const noexcept {
	return isButtonEliminated.at(point.y).at(point.x);
}

void Connect::Game::initializeSoundEffect() {
//	if (not soundEffect) {
//		soundEffect = new QSoundEffect(this);
//	}
//	qDebug() << "playing sound...";
//	soundEffect->setSource(QUrl("qrc:/Resources/audios/winmusic.mp3"));
//	qDebug() << "Play sound finished.";
//	soundEffect->setVolume(0.5);
	if (not mediaPlayer)
		mediaPlayer = new QMediaPlayer(this);

}

void Connect::Game::initializeLayout() {
	this->gridLayout->addWidget(timeLabel, 0, 1);
	this->gridLayout->addWidget(pauseButton, 0, 2);
	QWidget::connect(pauseButton, &QPushButton::clicked, this, &Connect::Game::togglePauseResume);
	for (auto row = 0LL; row < blocks.getRows(); row++) {
		for (auto col = 0LL; col < blocks.getCols(); col++) {
			auto point = Point(row, col);
			getButtonAt(point) = new QPushButton(QIcon(QString{blocks(point).data()}), "", this);
			gridLayout->addWidget(getButtonAt(point), row + 1, col);
			// CANNOT capture `row` and `col` by reference; the lambda expression might be executed AFTER the loop because it's a connection
			// Asynchronous signal-slot mechanism problem, also `onButtonPressed` cannot ref row and col.
			// or it'll be garbage value. vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			connect(getButtonAt(point), &QPushButton::pressed, [point, this]() -> void {
				this->onButtonPressed(point);
			});
		}
	}
}

CONNECT_FORCE_INLINE void Connect::Game::OnInitialize() {
	this->initializeGrid();
	this->initializeImages();
	this->initializeSoundEffect();
	this->initializeTime();
	this->initializeLayout();
}

void Connect::Game::initializeImages() {
	this->blocks.initializeImagePaths();
	this->blocks.initializeImageGrid(10, 10);
}

void Connect::Game::updateElapsedTime() {
	qint64 elapsedMilliseconds = elapsedTimer.elapsed() + pausedTime;
	timeLabel->setText(QString("Elapsed time: %1:%2.%3")
			                   .arg(elapsedMilliseconds / 60000, 2, 10, QChar('0'))
			                   .arg((elapsedMilliseconds % 60000) / 1000, 2, 10, QChar('0'))
			                   .arg((elapsedMilliseconds % 1000) / 100)
	);
	this->checkGameCondition();
}

void Connect::Game::initializeTime() {
	this->isPaused = false;
	this->startTime = QTime::currentTime();
	this->timer->setInterval(100);
	this->pauseButton->setText("Pause");
	this->elapsedTimer.start();
	this->timer->start();
	Connect::Game::pausedTime = 0;
	QWidget::connect(this->timer, &QTimer::timeout, this, &Connect::Game::updateElapsedTime);
	// must be toggled not clicked.
	QWidget::connect(this->pauseButton, &QPushButton::toggled, this, &Connect::Game::togglePauseResume);
}

void Connect::Game::checkGameCondition() {
	if (not isAllButtonEliminated())return;
	// win condition met.
	timer->stop();
	QWidget::disconnect(this->timer, &QTimer::timeout, this, &Connect::Game::updateElapsedTime);
	timeLabel->setText(timeLabel->text() + " - You Win!");
}

CONNECT_INLINE bool Connect::Game::isAllButtonEliminated() const {
	for (auto y = 0LL; y < blocks.getRows(); y++)
		for (auto x = 0LL; x < blocks.getCols(); x++)
			if (not isButtonEliminated[y][x])
				// has button not eliminated yet
				return false;
	return true;
}

void Connect::Game::togglePauseResume() {

	if (isPaused) {
//		elapsedTimer += pausedTime; // can't do that. :(
		elapsedTimer.restart();
		timer->start();
		pauseButton->setText("Pause");
		for (auto &rowButtons: buttons)
			for (auto &button: rowButtons)
				button->setEnabled(true);
	} else {
		Connect::Game::pausedTime += elapsedTimer.elapsed();
		timer->stop();
		pauseButton->setText("Resume");
		for (auto &rowButtons: buttons)
			for (auto &button: rowButtons)
				button->setEnabled(false);
	}
	isPaused = !isPaused;
}


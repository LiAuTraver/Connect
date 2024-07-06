#include <ViewModels/statuswidget.hpp>
#include <include/details.hpp>
#include <pch/qt.widgets.hh>

#include "ui_StatusWidget.h"

qint64 Connect::StatusWidget::pausedTime = 0;

Connect::StatusWidget::StatusWidget(QWidget *parent)
	: QWidget(parent),
	  pauseButton(new QPushButton(this)),
	  timer(new QTimer(this)),
	  ui(new Ui::StatusWidget),
	  statusLayout(new QHBoxLayout(this)),
	  timeLabel(new QLabel(this)),
	  scoreLabel(new QLabel(this)) {
	this->Oninitialize();
	this->ui->setupUi(this);
}

Connect::StatusWidget::~StatusWidget() { delete ui; }

Connect::StatusWidget &Connect::StatusWidget::initializeLayout() {
	this->statusLayout->addWidget(this->timeLabel);
	this->statusLayout->addWidget(this->pauseButton);
	this->statusLayout->addWidget(this->scoreLabel);
	return *this;
}

Connect::StatusWidget &Connect::StatusWidget::initializeTime() {
	this->timer->setInterval(100);
	this->pauseButton->setText("Pause");
	this->startTime = QTime::currentTime();
	this->elapsedTimer.start();
	this->timer->start();
	pausedTime = 0;
	connect(this->timer, &QTimer::timeout, this, &StatusWidget::updateElapsedTime);
	return *this;
}

QElapsedTimer Connect::StatusWidget::win() {
	timer->stop();
	disconnect(this->timer, &QTimer::timeout, this, &StatusWidget::updateElapsedTime);
	onButtonEliminate(pauseButton);
	timeLabel->setText(timeLabel->text() + " - You Win!");
	scoreLabel->setText(scoreLabel->text() + " final");
	return elapsedTimer;
}

void Connect::StatusWidget::updateElapsedTime() const {
	qint64 elapsedMilliseconds = elapsedTimer.elapsed() + pausedTime;
	timeLabel->setText(QString("Elapsed time: %1:%2.%3")
						   .arg(elapsedMilliseconds / 60000, 2, 10, QChar('0'))
						   .arg((elapsedMilliseconds % 60000) / 1000, 2, 10, QChar('0'))
						   .arg((elapsedMilliseconds % 1000) / 100));
}
void Connect::StatusWidget::updateScore(const int score) const {
	scoreLabel->setText(QString("Score: %1").arg(score));
}

Connect::StatusWidget &Connect::StatusWidget::onPauseButtonToggled(
	const std::string_view enumName) {
	auto option = magic_enum::enum_cast<TimeAction>(enumName, magic_enum::case_insensitive);
	if (not option) {
		throw std::invalid_argument(
			fmt::format(R"(enum "{}" in class "{}" not found.)", enumName.data(), "TimeAction"));
	}
	if (option == TimeAction::Pause) {
		// elapsedTimer += pausedTime; // can't do that. :(
		pausedTime += elapsedTimer.elapsed();
		timer->stop();
		pauseButton->setText("Resume");
	} else {
		// Resume
		elapsedTimer.restart();
		timer->start();
		pauseButton->setText("Pause");
	}
	return *this;
}

Connect::StatusWidget &Connect::StatusWidget::Oninitialize() {
	return this->initializeTime().initializeLayout();
}

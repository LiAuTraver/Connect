#pragma once

#include <include/config.hpp>
#include <magic_enum.hpp>
#include <pch/qt.core.hh>
#include <pch/qt.widgets.hh>

#include "ui_StatusWidget.h"

CONNECT_NAMESPACE_BEGIN
QT_BEGIN_NAMESPACE
namespace Ui {
class StatusWidget;
}
QT_END_NAMESPACE
CONNECT_NAMESPACE_END

CONNECT_NAMESPACE_BEGIN
class StatusWidget extends public QWidget {
	Q_OBJECT

public:
	using size_type = qsizetype;

public:
	explicit StatusWidget(QWidget *parent = nullptr);

	~StatusWidget() override;

public:
	StatusWidget &Oninitialize();

	StatusWidget &initializeLayout();

	QElapsedTimer win();

	StatusWidget &onPauseButtonToggled(std::string_view enumName);

public:
	// note: Qt connect-related function must return nothing(void) or return a static type or
	// something(todo).
	void updateElapsedTime() const;

	void updateScore(int) const;

public:
	QPushButton *pauseButton;
	QTimer *timer;

private:
	Ui::StatusWidget *ui;
	QHBoxLayout *statusLayout;
	QElapsedTimer elapsedTimer;
	QLabel *timeLabel;
	QLabel *scoreLabel;
	QTime startTime;
	static qint64 pausedTime;

private:
	StatusWidget &initializeTime();

	void onButtonEliminate(QPushButton * button) const;
};
CONNECT_NAMESPACE_END

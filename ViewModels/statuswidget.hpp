#pragma once

#include <include/config.hpp>
#include <pch/qt.core.hh>
#include <pch/qt.widgets.hh>
#include "ui_StatusWidget.h"
#include <magic_enum.hpp>


CONNECT_NAMESPACE_BEGIN
QT_BEGIN_NAMESPACE
namespace Ui { class StatusWidget; }
QT_END_NAMESPACE
CONNECT_NAMESPACE_END

CONNECT_NAMESPACE_BEGIN
class StatusWidget : public QWidget {
Q_OBJECT

public:
	explicit StatusWidget(QWidget *parent = nullptr);

	~StatusWidget() override;

public:
	StatusWidget &Oninitialize();

	StatusWidget &initializeLayout();

	StatusWidget &win();

	StatusWidget &onPauseButtonToggled(std::string_view enumName);

public receivers:

// note: Qt connect-related function must return nothing(void) or return a static type or something(todo).
	void updateElapsedTime() const;

public senders:
	QPushButton *pauseButton;
	QTimer *timer;
private:
	Ui::StatusWidget *ui;
	QHBoxLayout *statusLayout;
	QElapsedTimer elapsedTimer;
	QLabel *timeLabel;
	QTime startTime;
	static qint64 pausedTime;
private:
	StatusWidget &initializeTime();

	StatusWidget &onButtonEliminate(QPushButton *button);
};
CONNECT_NAMESPACE_END

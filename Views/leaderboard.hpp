#pragma once

#include <Services/Records.hpp>
#include <include/config.hpp>
#include <pch/qt.widgets.hh>

CONNECT_NAMESPACE_BEGIN
QT_BEGIN_NAMESPACE

namespace Ui {
class Leaderboard;
}

QT_END_NAMESPACE
CONNECT_NAMESPACE_END

CONNECT_NAMESPACE_BEGIN
class Leaderboard extends public QWidget {
	Q_OBJECT

public:
	explicit Leaderboard(QWidget *parent = nullptr);

	~Leaderboard() override;

public
receivers:
	void onImportRecordButtonClicked();

private:
	Ui::Leaderboard *ui;
	QHBoxLayout *leaderboardLayout;
	Records records;
	QPushButton *importRecordButton;
	QPushButton *closeButton;
signals:
	void onCloseButtonClicked();
};

CONNECT_NAMESPACE_END

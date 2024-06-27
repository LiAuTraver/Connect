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

public:
	Leaderboard &setupTable();

private:
	Ui::Leaderboard *ui;
	QVBoxLayout *leaderboardLayout;
	QHBoxLayout *buttonLayout;
	QTableView *tableView;
	Records records;
	QPushButton *importRecordButton;
	QPushButton *closeButton;
	static constinit const char *WARNING_MESSAGE;
signals:
	void onCloseButtonClicked();
private slots:
	void onImportRecordButtonClicked();
	void onMessageBoxButtonClicked();
};
CONNECT_NAMESPACE_END

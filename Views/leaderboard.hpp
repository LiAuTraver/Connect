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
	void saveData() const;
	Leaderboard &setupTable();

private:
	Ui::Leaderboard *ui;
	QVBoxLayout *leaderboardLayout;
	QHBoxLayout *buttonLayout;
	QTableView *tableView;
	QPushButton *importRecordButton;
	QPushButton *closeButton;
	Records records;
public:
	//! no ref
	//! do not pass reference in slots, they're multi-threaded
	void onGameWinChangeRecord(qint64, qint64);

private:
	absl::StatusOr<QString> onAddingRecord();
	void acquireName(Record & pendingRecord);
	static constinit const char *WARNING_MESSAGE;
	static const QRegularExpression invalidPattern;
signals:
	void onLeaderboradCloseButtonClicked();
private slots:
	void handleImportRecordButtonClicked();
	void handleMessageBoxButtonClicked();
};
CONNECT_NAMESPACE_END

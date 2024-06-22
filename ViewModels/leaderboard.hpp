#pragma once

#include <pch/qt.widgets.hh>
#include <include/config.hpp>

CONNECT_NAMESPACE_BEGIN
QT_BEGIN_NAMESPACE
namespace Ui { class Leaderboard; }
QT_END_NAMESPACE
CONNECT_NAMESPACE_END

CONNECT_NAMESPACE_BEGIN
class Leaderboard : public QWidget {
Q_OBJECT

public:
	explicit Leaderboard(QWidget *parent = nullptr);

	~Leaderboard() override;

private:
	Ui::Leaderboard *ui;
	QHBoxLayout* leaderboardLayout;
};
CONNECT_NAMESPACE_END

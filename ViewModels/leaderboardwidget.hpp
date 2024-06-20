#pragma once

#include <pch/qt.widgets.hh>
#include <include/config.hpp>

CONNECT_NAMESPACE_BEGIN
QT_BEGIN_NAMESPACE
namespace Ui { class LeaderboardWidget; }
QT_END_NAMESPACE
CONNECT_NAMESPACE_END

CONNECT_NAMESPACE_BEGIN
class LeaderboardWidget : public QWidget {
Q_OBJECT

public:
	explicit LeaderboardWidget(QWidget *parent = nullptr);

	~LeaderboardWidget() override;

private:
	Ui::LeaderboardWidget *ui;
	QHBoxLayout* leaderboardLayout;
};
CONNECT_NAMESPACE_END

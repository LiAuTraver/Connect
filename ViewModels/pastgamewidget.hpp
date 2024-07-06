#pragma once

#include <include/config.hpp>
#include <pch/qt.widgets.hh>

CONNECT_NAMESPACE_BEGIN
QT_BEGIN_NAMESPACE
namespace Ui {
class PastGameWidget;
}
QT_END_NAMESPACE
CONNECT_NAMESPACE_END

CONNECT_NAMESPACE_BEGIN
class PastGameWidget : public QWidget {
	Q_OBJECT

public:
	explicit PastGameWidget(QWidget* parent = nullptr);
	~PastGameWidget() override;
public:
	enum Option {
		ReplayGame,
		ToLeaderboard,
		BackToMenu
	};
signals:
	void NavigateToSuper(Option);

private:
	Ui::PastGameWidget* ui;
	static constinit const char* GAME_OVER;
	static constinit const char* YOU_WIN;
};
CONNECT_NAMESPACE_END

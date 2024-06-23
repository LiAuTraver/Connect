#pragma once

#include "pch/qt.widgets.hh"
#include "include/config.hpp"
#include "pch/std.container.hh"
#include "pch/qt.multimedia.hh"
#include "Services/Blocks.hpp"
#include "Models/Point.hpp"
#include "statuswidget.hpp"
#include "blockswidget.hpp"

CONNECT_NAMESPACE_BEGIN
QT_BEGIN_NAMESPACE
namespace Ui { class Game; }
QT_END_NAMESPACE
CONNECT_NAMESPACE_END

CONNECT_NAMESPACE_BEGIN
class Game extends public QWidget {
Q_OBJECT

public:
	explicit Game(QWidget *parent = nullptr);

	~Game() override;

public:
	using size_type = qsizetype;
private:
	Ui::Game *ui;
	QVBoxLayout *mainLayout;
	Connect::BlocksWidget *blocksWidget;
	Connect::StatusWidget *statusWidget;
	bool isPaused;

private:

	CONNECT_FORCE_INLINE Game &OnInitialize();

	Game &win();

	Game &initializeLayout();

	Game &initializeConnections();

private receivers:

	void togglePauseResume();

private slots:

	void onNavigatedFrom();

};
CONNECT_NAMESPACE_END

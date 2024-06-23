#pragma once

#include "ViewModels/about.hpp"
#include "ViewModels/game.hpp"
#include "ViewModels/leaderboard.hpp"
#include "ViewModels/menu.hpp"
#include "include/config.hpp"
#include "pch/qt.widgets.hh"

QT_BEGIN_NAMESPACE
CONNECT_NAMESPACE_BEGIN
namespace Ui {
class MainWindow;
}

CONNECT_NAMESPACE_END

QT_END_NAMESPACE

CONNECT_NAMESPACE_BEGIN
class MainWindow : public QMainWindow {
	Q_OBJECT
	// if we define the class at a .cpp file, that is,
	//! the macro `Q_OBJECT`appears at a cpp source file,
	//! then we shall include "{cpp name}.moc" meta file.

public:
	explicit MainWindow(QWidget *parent = nullptr);

	~MainWindow() override;

private:
	CONNECT_FORCE_INLINE void destroyChildWidget(auto *&childWidget);

	CONNECT_FORCE_INLINE void initializeConnections();

	CONNECT_FORCE_INLINE void initializeMenuConnections();

private senders:
	Ui::MainWindow *ui;
	Menu *menu;
	Game *game;
	Leaderboard *leaderboard;
	About *about;

private slots:
	void handleGameStart();

	void handleLeaderboardStart();

	void handleAboutPageStart();

	void handleGameExit();

	void handleAboutExit();

};

CONNECT_NAMESPACE_END

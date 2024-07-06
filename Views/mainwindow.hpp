#pragma once

#include <Services/Sound.hpp>
#include <ViewModels/pastgamewidget.hpp>
#include <Views/about.hpp>
#include <Views/game.hpp>
#include <Views/leaderboard.hpp>
#include <Views/menu.hpp>
#include <include/config.hpp>
#include <pch/qt.widgets.hh>

QT_BEGIN_NAMESPACE
CONNECT_NAMESPACE_BEGIN
namespace Ui {
class MainWindow;
}
CONNECT_NAMESPACE_END
QT_END_NAMESPACE

CONNECT_NAMESPACE_BEGIN
class MainWindow extends public QMainWindow {
	Q_OBJECT
	//! if we define the class at a .cpp file, that is,
	//! the macro `Q_OBJECT`appears at a cpp source file,
	//! then we shall include "{cpp name}.moc" meta file.

public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow() override;

public:
	using enum PastGameWidget::Option;
	enum Page { kMenu, kGame, kLeaderboard, kAbout, kThis };

public:
	void initializeConnections(Page);

private:
	Ui::MainWindow *ui;
	Menu *menu;
	Game *game;
	Leaderboard *leaderboard;
	About *about;
	SoundEvent soundEvent{};
	QString gameBGM{};

private slots:
	// ^^^^ note: the `slots` keyword ais optional for Qt 5 & 6, but necessary for Qt 4 or so.
	// I just keep it for clarity and maintainity;
	// But if the `connect` func was used as Qt 4's way: connect(...,SIGNAL(...),...,SLOT(...)),
	// the `slot` keyword cannot be omitted.
	void handleAddNewRecord(qint64, qint64);

	// ReSharper disable CppRedundantQualifier
	void handleExitFromGame(Connect::PastGameWidget::Option);

	void handleStartFromMenu(Connect::MainWindow::Page);

	void handlePageExitToMenu(Connect::MainWindow::Page);
	// ReSharper enable CppRedundantQualifier

	void handleVolumeChanged(int);
};

CONNECT_NAMESPACE_END

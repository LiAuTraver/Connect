#pragma once

#include "pch/qt.widgets.hh"
#include "include/config.hpp"
#include "ViewModels/menu.hpp"
#include "ViewModels/game.hpp"

QT_BEGIN_NAMESPACE
CONNECT_NAMESPACE_BEGIN
namespace Ui { class MainWindow; }
CONNECT_NAMESPACE_END
QT_END_NAMESPACE

CONNECT_NAMESPACE_BEGIN
class MainWindow : public QMainWindow {
Q_OBJECT 	//! if we define the class at a .cpp file, that is,
			//! the macro `Q_OBJECT`appears at a cpp source file,
			//! then we shall include "{cpp name}.moc" meta file.

public:
	explicit MainWindow(QWidget *parent = nullptr);

	~MainWindow() override;

private:
	static CONNECT_FORCE_INLINE void destroyChildWidget(QWidget *childWidget);

private:
	Connect::Ui::MainWindow *ui;
	Connect::Menu *menu;
	Connect::Game *game;
private slots:

	void handleGameStart();

	void handleGameExit();
};
CONNECT_NAMESPACE_END
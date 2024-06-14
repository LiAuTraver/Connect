#pragma once

#include <pch/qWidgets.hh>
#include "include/config.hpp"
#include "menu.hpp"
#include "game.hpp"

QT_BEGIN_NAMESPACE
CONNECT_NAMESPACE_BEGIN
namespace Ui { class MainWindow; }
CONNECT_NAMESPACE_END
QT_END_NAMESPACE

CONNECT_NAMESPACE_BEGIN
class MainWindow : public QMainWindow {
Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow() override;

private:
	Connect::Ui::MainWindow *ui;
	Connect::Menu* menu;
	Connect::Game* game;
};
CONNECT_NAMESPACE_END
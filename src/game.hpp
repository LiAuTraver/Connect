#pragma once

#include <pch/qWidgets.hh>
#include "include/config.hpp"
CONNECT_NAMESPACE_BEGIN
QT_BEGIN_NAMESPACE
namespace Ui { class Game; }
QT_END_NAMESPACE
CONNECT_NAMESPACE_END

CONNECT_NAMESPACE_BEGIN
class Game : public QWidget {
Q_OBJECT

public:
	explicit Game(QWidget *parent = nullptr);

	~Game() override;

private:
	Ui::Game *ui;
};
CONNECT_NAMESPACE_END

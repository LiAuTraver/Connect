#pragma once

#include <pch/qWidgets.hh>
#include <pch/absl.log.hh>
#include "include/config.hpp"

QT_BEGIN_NAMESPACE
CONNECT_NAMESPACE_BEGIN
namespace Ui { class Menu; }
CONNECT_NAMESPACE_END
QT_END_NAMESPACE

CONNECT_NAMESPACE_BEGIN
class Menu : public QWidget {
Q_OBJECT

public:
	explicit Menu(QWidget *parent = nullptr);

	~Menu() override;

private:
	Ui::Menu *ui;
};
CONNECT_NAMESPACE_END
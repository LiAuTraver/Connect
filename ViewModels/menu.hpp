#pragma once

#include "pch/qt.widgets.hh"
#include "pch/absl.log.hh"
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
signals:
	void onStartButtonClicked();
private:
	Ui::Menu *ui;
	static void debug();
};
CONNECT_NAMESPACE_END
#pragma once

#include <include/config.hpp>
#include <pch/qt.widgets.hh>

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
public:
	void OnInitialize();
signals:
	void onStartButtonClicked();
	void onRecordButtonClicked();
	void onAboutButtonClicked();
private:
	Ui::Menu *ui;
	static void debug();
};
CONNECT_NAMESPACE_END
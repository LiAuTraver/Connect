#pragma once
#include <include/config.hpp>
#include <pch/qt.core.hh>
#include <pch/qt.widgets.hh>

CONNECT_NAMESPACE_BEGIN
QT_BEGIN_NAMESPACE
namespace Ui {
class About;
}
QT_END_NAMESPACE
CONNECT_NAMESPACE_END

CONNECT_NAMESPACE_BEGIN
class About : public QWidget {
	Q_OBJECT

public:
	explicit About(QWidget *parent = nullptr);
	~About() override;

private:
	Ui::About *ui;
signals:
	void onCloseButtonCicked();
};
CONNECT_NAMESPACE_END

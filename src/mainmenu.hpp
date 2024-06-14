#pragma once

#include <QWidget>

namespace Connect {
QT_BEGIN_NAMESPACE
namespace Ui { class MainMenu; }
QT_END_NAMESPACE

class MainMenu : public QWidget {
Q_OBJECT

public:
	explicit MainMenu(QWidget *parent = nullptr);

	~MainMenu() override;

private:
	Ui::MainMenu *ui;
};
} // Connect

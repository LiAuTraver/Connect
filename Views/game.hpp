#pragma once

#include <ViewModels/blockswidget.hpp>
#include <ViewModels/pastgamewidget.hpp>
#include <ViewModels/statuswidget.hpp>
#include <include/config.hpp>
#include <pch/qt.widgets.hh>

CONNECT_NAMESPACE_BEGIN
QT_BEGIN_NAMESPACE
namespace Ui {
class Game;
}
QT_END_NAMESPACE
CONNECT_NAMESPACE_END

CONNECT_NAMESPACE_BEGIN
class Game extends public QWidget {
	Q_OBJECT

public:
	explicit Game(QWidget *parent = nullptr);

	~Game() override;

public:
	using size_type = qsizetype;
	using enum PastGameWidget::Option;

private:
	Ui::Game *ui;
	QVBoxLayout *mainLayout;
	BlocksWidget *blocksWidget;
	StatusWidget *statusWidget;
	PastGameWidget *pastGameWidget;
	bool isPaused{false};

private:
	Game &OnInitialize();

	Game &initializeLayout();

	Game &initializeConnections();
signals:
	void onGameWinCheckRecord(qint64 score, qint64 elapsedTime);
	void RelayTo(PastGameWidget::Option);
private slots:
	void togglePauseResume();

	void onGameOver();

	void RelayFrom(PastGameWidget::Option);
};
CONNECT_NAMESPACE_END

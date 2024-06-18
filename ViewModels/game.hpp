#pragma once

#include "pch/qt.widgets.hh"
#include "include/config.hpp"
#include "pch/std.container.hh"
#include "pch/qt.multimedia.hh"
#include "Services/Blocks.hpp"
#include "Models/Point.hpp"

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

public:
	using size_type = qsizetype;
private:
	Ui::Game *ui;
	QVBoxLayout *mainLayout;
	QWidget* gameWidget;
	QWidget* statusWidget;
	QGridLayout *gameLayout;
	QHBoxLayout *statusLayout;
	QMediaPlayer *mediaPlayer;
	QTimer *timer;
	QElapsedTimer elapsedTimer;
	QLabel *timeLabel;
	QPushButton *pauseButton;
	QTime startTime;
	QVector<QVector<QPushButton *>> buttons;
	QVector<QVector<bool>> isButtonEliminated;
//	QSoundEffect *soundEffect;
	Point previousButton{-1, -1};
	Blocks blocks;
	bool isPaused;
	static qint64 pausedTime;
private:
	_NODISCARD CONNECT_INLINE QPushButton *&
	getButtonAt(const Point &point) noexcept(noexcept(buttons[point.y][point.x]));

	_NODISCARD CONNECT_INLINE bool &
	getEliminatedButtonAt(const Point &point) noexcept(noexcept(isButtonEliminated[point.y][point.x]));

	_NODISCARD CONNECT_MAYBE_UNUSED CONNECT_INLINE bool getEliminatedButtonAt(const Point &) const noexcept;

	void onButtonPressed(Point);

	void initializeImageGrid();

	_NODISCARD bool isSame(Point &) noexcept;

	static void onButtonEliminate(QPushButton *button);

	void initializeSoundEffect();

	void initializeImages();

	void initializeTime();

	CONNECT_FORCE_INLINE void OnInitialize();

	void updateElapsedTime();

	void checkGameCondition();

	void win();

	void initializeLayout();

	_NODISCARD bool isAllButtonEliminated() const;

	void togglePauseResume();
};
CONNECT_NAMESPACE_END

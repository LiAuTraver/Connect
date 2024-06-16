#pragma once

#include "pch/qt.widgets.hh"
#include "include/config.hpp"
#include "pch/std.container.hh"
#include "Blocks.hpp"
#include "Point.hpp"
#include <pch/qt.multimedia.hh>

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
	QGridLayout *gridLayout;
	QMediaPlayer *mediaPlayer;
	QTimer *timer;
	QElapsedTimer elapsedTimer;
	QLabel *timeLabel;
	QTime startTime;
	QVector<QVector<QPushButton *>> buttons;
	QVector<QVector<bool>> isButtonEliminated;
//	QSoundEffect *soundEffect;
	Point previousButton{-1, -1};
	Blocks blocks;


private:
	_NODISCARD inline QPushButton *&getButtonAt(const Point & point) noexcept(noexcept(buttons[point.y][point.x]));

	_NODISCARD inline bool &getEliminatedButtonAt(const Point & point) noexcept(noexcept(isButtonEliminated[point.y][point.x]));

	_NODISCARD inline bool getEliminatedButtonAt(const Point &) const noexcept;

	void onButtonPressed(Point);

	void initializeGrid();

	_NODISCARD bool isSame(Point &) noexcept;

	void onButtonEliminate(QPushButton *button);

	void initializeSoundEffect();

	void initializeConnections();

	void initializeImages();

	void initializeTime();

	CONNECT_FORCE_INLINE void OnInitialize();

	void updateElapsedTime();

	void checkGameCondition();

	_NODISCARD bool isAllButtonEliminated() const;
};
CONNECT_NAMESPACE_END

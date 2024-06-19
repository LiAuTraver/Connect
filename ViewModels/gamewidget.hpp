#pragma once

#include <pch/qt.core.hh>
#include <include/config.hpp>
#include <pch/qt.widgets.hh>
#include <Services/Blocks.hpp>
#include <magic_enum.hpp>
#include <Helpers/Actions.hpp>

CONNECT_NAMESPACE_BEGIN
QT_BEGIN_NAMESPACE
namespace Ui { class GameWidget; }
QT_END_NAMESPACE
CONNECT_NAMESPACE_END

CONNECT_NAMESPACE_BEGIN
class GameWidget : public QWidget {
Q_OBJECT

public:
	explicit GameWidget(QWidget *parent = nullptr);

	~GameWidget() override;
	using size_type = qsizetype;

public:
	GameWidget &Oninitialize();

	GameWidget &onPauseButtonToggled(std::string_view enumName);

	_NODISCARD bool isAllButtonEliminated() const;

private:
	Ui::GameWidget *ui;
	QGridLayout *gameLayout;
	QVector<QVector<QPushButton *>> buttons;
	QVector<QVector<bool>> isButtonEliminated;
	Point previousButton{-1, -1};
	Blocks blocks;
	size_type ROWS = 10;
	size_type COLS = 10;

private:
	GameWidget &initializeImageGrid();

	_NODISCARD bool isSame(Point &point) noexcept;

	_NODISCARD bool onButtonPressed(Point point);

	GameWidget &initializeLayout();

	_NODISCARD CONNECT_INLINE QPushButton *&
	getButtonAt(const Point &point) noexcept(noexcept(buttons[point.y][point.x]));

	_NODISCARD CONNECT_INLINE bool &
	getEliminatedButtonAt(const Point &point) noexcept(noexcept(isButtonEliminated[point.y][point.x]));

	_NODISCARD CONNECT_MAYBE_UNUSED CONNECT_INLINE bool
	getEliminatedButtonAt(const Point &) const noexcept;

signals:

	void forward();
};
CONNECT_NAMESPACE_END

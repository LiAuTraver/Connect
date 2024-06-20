#pragma once

#include <pch/qt.core.hh>
#include <include/config.hpp>
#include <pch/qt.widgets.hh>
#include <Services/Blocks.hpp>
#include <magic_enum.hpp>
#include <Helpers/Actions.hpp>
#include <Models/BlockButton.hpp>

CONNECT_NAMESPACE_BEGIN
QT_BEGIN_NAMESPACE
namespace Ui { class BlocksWidget; }
QT_END_NAMESPACE
CONNECT_NAMESPACE_END

CONNECT_NAMESPACE_BEGIN
class BlocksWidget extends public QWidget {
Q_OBJECT

public:
	explicit BlocksWidget(QWidget *parent = nullptr);

	~BlocksWidget() override;

	using size_type = qsizetype;

public:
	BlocksWidget &Oninitialize();

	BlocksWidget &onPauseButtonToggled(std::string_view enumName);

	_NODISCARD bool isAllButtonEliminated() const;

private:
	Ui::BlocksWidget *ui;
	QGridLayout *blockLayout;
	QVector<QVector<BlockButton *>> buttons;
//	QVector<QVector<bool>> isButtonEliminated;
	Point previousButton{-1, -1};
	Blocks blocks;
	size_type ROWS = 4;
	size_type COLS = 4;

private:
	BlocksWidget &initializeImageGrid();

	_NODISCARD bool isSame(Point &point) noexcept;

	_NODISCARD bool onButtonPressed(Point point);

	BlocksWidget &initializeLayout();

	_NODISCARD CONNECT_INLINE BlockButton *&
	getButtonAt(const Point &point) noexcept(noexcept(buttons[point.y][point.x]));


	_NODISCARD CONNECT_INLINE bool getEliminatedButtonAt(const Point &point);

signals:
	void navigateToSuper();
};
CONNECT_NAMESPACE_END

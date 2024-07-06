#pragma once

#include <include/details.hpp>
#include <Models/BlockButton.hpp>
#include <Services/Blocks.hpp>
#include <include/config.hpp>
#include <magic_enum.hpp>
#include <pch/qt.core.hh>
#include <pch/qt.widgets.hh>

CONNECT_NAMESPACE_BEGIN
QT_BEGIN_NAMESPACE
namespace Ui {
class BlocksWidget;
}
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

	_NODISCARD std::optional<size_type> isAllButtonEliminated() const;

private:
	Ui::BlocksWidget *ui;
	QGridLayout *blockLayout;
	QVector<QVector<BlockButton *>> buttons;
	Blocks blocks;
	Point previousButton{-1, -1};
	size_type score = 0;
	size_type ROWS = 8;
	size_type COLS = 8;

private:
	BlocksWidget &initializeImageGrid();

	_NODISCARD bool onButtonPressed(Point point);

	BlocksWidget &initializeLayout();

	_NODISCARD CONNECT_INLINE BlockButton *&getButtonAt(const Point &point) noexcept(
		noexcept(buttons[point.y][point.x]));

	_NODISCARD CONNECT_INLINE bool getEliminatedButtonAt(const Point &point);

signals:
	void navigateToSuper();

	void updateScoreLabel(int);
};
CONNECT_NAMESPACE_END

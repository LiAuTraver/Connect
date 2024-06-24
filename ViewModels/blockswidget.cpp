#include <Helpers/Animation.hpp>
#include <ViewModels/blockswidget.hpp>
#include <include/config.hpp>
#include <pch/qt.widgets.hh>

#include "ui_BlocksWidget.h"

Connect::BlocksWidget::BlocksWidget(QWidget *parent) :
	QWidget(parent), ui(new Ui::BlocksWidget), buttons(QVector<QVector<BlockButton *>>{}),
	blockLayout(new QGridLayout(nullptr)), previousButton(-1, -1) {
	this->Oninitialize().ui->setupUi(this);
}

Connect::BlocksWidget::~BlocksWidget() { delete ui; }

Connect::BlocksWidget &Connect::BlocksWidget::initializeImageGrid() {
	buttons.resize(blocks.getRows());
	for (auto &rowButtons: buttons) rowButtons.resize(blocks.getCols());
	return *this;
}

_NODISCARD bool Connect::BlocksWidget::onButtonPressed(Point point) {
	qDebug() << "pressed button:" << point.y << " " << point.x;
	qDebug() << "previous:" << previousButton.y << " " << previousButton.x;
	if (previousButton == Point(-1, -1)) {
		qDebug() << "Block Pressed.";
		previousButton = point;
		// todo:change texture
		return false;
	} else if (previousButton == point) {
		qDebug() << "same button pressed. ignore.";
		return false;
	} else if (isSame(point)) {
		qDebug() << "ok!";
		// animation of elimination
		this->getButtonAt(point)->eliminate();
		this->getButtonAt(previousButton)->eliminate();
		Connect::Animation(getButtonAt(point))(getButtonAt(previousButton));
		previousButton = Point(-1, -1);
		return true;  // should check win condition
	} else {
		qDebug() << "not the same type.";
		// todo:change back texture
		previousButton = Point(-1, -1);
		return false;
	}
}


_NODISCARD bool Connect::BlocksWidget::isSame(Point &point) noexcept {
	return true;
	//	return this->blocks(point) == this->blocks(previousButton);
}


_NODISCARD CONNECT_INLINE Connect::BlockButton *&Connect::BlocksWidget::getButtonAt(
		const Connect::Point &point) noexcept(noexcept(buttons[point.y][point.x])) {
	return buttons[point.y][point.x];
}

_NODISCARD CONNECT_INLINE bool Connect::BlocksWidget::getEliminatedButtonAt(const Connect::Point &point) noexcept(
		noexcept(buttons[point.y][point.x])) {
	return buttons[point.y][point.x]->isEliminated();
}

Connect::BlocksWidget &Connect::BlocksWidget::initializeLayout() {
	for (auto row = 0LL; row < blocks.getRows(); row++) {
		for (auto col = 0LL; col < blocks.getCols(); col++) {
			auto point = Point(row, col);
			getButtonAt(point) =
					new BlockButton(QIcon(QPixmap(QString{blocks(point).data()})
												  .scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation)),
									"", this, false);
			blockLayout->addWidget(getButtonAt(point), static_cast<int>(row), static_cast<int>(col));
			// CANNOT capture `row` and `col` by reference; the lambda expression might be executed AFTER the loop
			// because it's a connection Asynchronous signal-slot mechanism problem, also `onButtonPressed` cannot ref
			// row and col. or it'll be garbage value. vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			QWidget::connect(getButtonAt(point), &QPushButton::pressed, [point, this]() -> void {
				if (this->onButtonPressed(point)) {
					emit this->navigateToSuper();
				}
			});
		}
	}
	this->blockLayout->setVerticalSpacing(0);
	this->blockLayout->setHorizontalSpacing(0);
	this->setLayout(blockLayout);
	return *this;
}

_NODISCARD bool Connect::BlocksWidget::isAllButtonEliminated() const {
	for (auto y = 0LL; y < blocks.getRows(); y++)
		for (auto x = 0LL; x < blocks.getCols(); x++)
			if (buttons.at(y).at(x)->isEliminated() == false)
				// has button not eliminated yet
				return false;
	return true;
}

Connect::BlocksWidget &Connect::BlocksWidget::onPauseButtonToggled(std::string_view enumName) {
	auto option = magic_enum::enum_cast<ButtonAction>(enumName, magic_enum::case_insensitive);
	if (not option.has_value()) {
		throw std::invalid_argument(
				fmt::format(R"(enum "{}" in class "{}" not found.)", enumName.data(), "ButtonAction"));
	}
	if (option == ButtonAction::Hide) {
		for (auto &rowButtons: buttons)
			for (auto &button: rowButtons) button->setEnabled(false);
	} else {
		// Show
		for (auto &rowButtons: buttons)
			for (auto &button: rowButtons) button->setEnabled(true);
	}
	return *this;
}

Connect::BlocksWidget &Connect::BlocksWidget::Oninitialize() {
	this->blocks.reset(ROWS, COLS, Blocks::IMAGE_PATH);
	return (*this).initializeImageGrid().initializeLayout();
}

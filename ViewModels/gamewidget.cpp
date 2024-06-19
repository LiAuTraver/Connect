#include <include/config.hpp>
#include <pch/qt.widgets.hh>
#include <Helpers/Animation.hpp>
#include "gamewidget.hpp"
#include "ui_GameWidget.h"

Connect::GameWidget::GameWidget(QWidget *parent) :
		QWidget(parent), ui(new Ui::GameWidget),
		buttons(QVector<QVector<QPushButton *>>{}),
		gameLayout(new QGridLayout(nullptr)),
		previousButton(-1, -1) {
	this->
					Oninitialize()
			.ui->
					setupUi(this);
	this->blocks.reset(ROWS,COLS);
}

Connect::GameWidget::~GameWidget() {
	delete ui;
}

Connect::GameWidget &Connect::GameWidget::initializeImageGrid() {
	buttons.resize(blocks.getRows());
	for (auto &rowButtons: buttons)
		rowButtons.resize(blocks.getCols());
	isButtonEliminated.resize(blocks.getRows());
	for (auto &rowButtonsClicked: isButtonEliminated)
		rowButtonsClicked.resize(blocks.getCols(), false);
	return *this;
}

_NODISCARD bool Connect::GameWidget::onButtonPressed(Point point) {
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
		this->getEliminatedButtonAt(point) = true;
		this->getEliminatedButtonAt(previousButton) = true;
		Connect::Animation(getButtonAt(point))(getButtonAt(previousButton));
		return true; // should check win condition
	} else {
		qDebug() << "not the same type.";
		// todo:change back texture
	}
	previousButton = Point(-1, -1);
	return false;
}


_NODISCARD bool Connect::GameWidget::isSame(Point &point) noexcept {
	return this->blocks(point) == this->blocks(previousButton);
}


QPushButton *&Connect::GameWidget::getButtonAt(
		const Connect::Point &point) noexcept(noexcept(buttons[point.y][point.x])) {
	return buttons[point.y][point.x];
}

bool &Connect::GameWidget::getEliminatedButtonAt(
		const Connect::Point &point) noexcept(noexcept(isButtonEliminated[point.y][point.x])) {
	return isButtonEliminated[point.y][point.x];
}

_NODISCARD CONNECT_MAYBE_UNUSED CONNECT_INLINE bool
Connect::GameWidget::getEliminatedButtonAt(const Connect::Point &point) const noexcept {
	return isButtonEliminated.at(point.y).at(point.x);
}

Connect::GameWidget &Connect::GameWidget::initializeLayout() {
	for (auto row = 0LL; row < blocks.getRows(); row++) {
		for (auto col = 0LL; col < blocks.getCols(); col++) {
			auto point = Point(row, col);
			getButtonAt(point) = new QPushButton(QIcon(QString{blocks(point).data()}), "", this);
			gameLayout->addWidget(getButtonAt(point), static_cast<int>(row), static_cast<int>(col));
			// CANNOT capture `row` and `col` by reference; the lambda expression might be executed AFTER the loop because it's a connection
			// Asynchronous signal-slot mechanism problem, also `onButtonPressed` cannot ref row and col.
			// or it'll be garbage value. vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
			connect(getButtonAt(point), &QPushButton::pressed, [point, this]() -> void {
				if (this->onButtonPressed(point)) {
					emit
					this->forward();
				}
			});
		}
	}
	this->setLayout(gameLayout);
	return *this;
}

_NODISCARD bool Connect::GameWidget::isAllButtonEliminated() const {
	for (auto y = 0LL; y < blocks.getRows(); y++)
		for (auto x = 0LL; x < blocks.getCols(); x++)
			if (not isButtonEliminated[y][x])
				// has button not eliminated yet
				return false;
	return true;
}

Connect::GameWidget & Connect::GameWidget::onPauseButtonToggled(std::string_view enumName) {
	auto option = magic_enum::enum_cast<ButtonAction>(enumName);
	if (not option.has_value()) {
		throw std::invalid_argument(
				fmt::format(
						R"(enum "{}" in class "{}" not found.)", enumName, "ButtonAction"));
	}
	if (option == ButtonAction::Hide) {
		for (auto &rowButtons: buttons)
			for (auto &button: rowButtons)
				button->setEnabled(false);
	} else {
		// Show
		for (auto &rowButtons: buttons)
			for (auto &button: rowButtons)
				button->setEnabled(true);
	}
	return *this;
}

Connect::GameWidget &Connect::GameWidget::Oninitialize() {
	this->blocks.Oninitialize();
	return (*this)
			.initializeImageGrid()
			.initializeLayout();
}



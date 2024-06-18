
#include <Models/Block.hpp>
#include <include/config.hpp>

bool Connect::Block::operator==(const Connect::Block &rhs) const {
	return row_coor == rhs.row_coor &&
	       col_coor == rhs.col_coor;
}

bool Connect::Block::operator!=(const Connect::Block &rhs) const {
	return !(rhs == *this);
}

bool Connect::Block::operator==(const QVector2D &rhs) const {
	return static_cast<size_type>(rhs.x()) == this->row_coor &&
	       static_cast<size_type>(rhs.y()) == this->col_coor;
}

bool Connect::Block::operator!=(const QVector2D &rhs) const {
	return !(*this == rhs);
}

Connect::Block::Block(QWidget *parent) :
		row_coor(std::numeric_limits<size_type>::quiet_NaN()),
		col_coor(std::numeric_limits<size_type>::quiet_NaN()) {
	button = new QPushButton(parent);

}

Connect::Block::Block(const size_type &y, const size_type &x, QWidget *parent) :
		row_coor(y),
		col_coor(x) {
	button = new QPushButton(parent);
}

Connect::Block::Block(const size_type &y, const size_type &x, const QString &text, QWidget *parent) :
		row_coor(y),
		col_coor(x) {
	button = new QPushButton(text, parent);
}

Connect::Block &Connect::Block::operator=(const QVector2D &rhs) {
	row_coor = static_cast<size_type>(rhs.y());
	col_coor = static_cast<size_type>(rhs.x());
	return *this;
}

QVector2D Connect::Block::get_coor() const noexcept {
	return QVector2D(row_coor, col_coor);
}

Connect::Block Connect::Block::empty() noexcept {
	return Connect::Block();
}

Connect::Block::button_pointer Connect::Block::operator->() const noexcept {
	return button;
}


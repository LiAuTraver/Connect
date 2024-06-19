#pragma once

#include <include/config.hpp>
#include <pch/qt.core.hh>
#include <pch/qt.gui.hh>

CONNECT_NAMESPACE_BEGIN
class BlockButton extends public QPushButton {
Q_OBJECT

public:
	explicit BlockButton(QWidget *parent = nullptr, bool isEliminated = false)
			: QPushButton(parent), isEliminated(isEliminated) {}

	explicit BlockButton(const QString &text, QWidget *parent = nullptr,
	                     bool isEliminated = false) : QPushButton(text, parent), isEliminated(isEliminated) {}

	explicit BlockButton(const QIcon &icon, const QString &text,
	                     QWidget *parent = nullptr, bool isEliminated = false)
			: QPushButton(icon, text, parent), isEliminated(isEliminated) {}

protected:
	void resizeEvent(QResizeEvent *event) override {
		auto side = qMin(event->size().width(), event->size().height());
		setFixedSize(side, side);
		QPushButton::resizeEvent(event);
	}

private:
	bool isEliminated;
};
CONNECT_NAMESPACE_END
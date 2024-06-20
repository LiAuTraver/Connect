#pragma once

#include <include/config.hpp>
#include <pch/qt.core.hh>
#include <pch/qt.gui.hh>
#include <Helpers/Actions.hpp>

CONNECT_NAMESPACE_BEGIN
class BlockButton extends public QPushButton {
Q_OBJECT

public:
	explicit BlockButton(QWidget *parent = nullptr, bool isEliminated = false)
			: QPushButton(parent), status(isEliminated ? ButtonStatus::Hidden : ButtonStatus::Showed) {}

	explicit BlockButton(const QString &text, QWidget *parent = nullptr,
	                     bool isEliminated = false) : QPushButton(text, parent),
	                                                  status(isEliminated ? ButtonStatus::Hidden
	                                                                      : ButtonStatus::Showed) {}

	explicit BlockButton(const QIcon &icon, const QString &text,
	                     QWidget *parent = nullptr, bool isEliminated = false)
			: QPushButton(icon, text, parent), status(isEliminated ? ButtonStatus::Hidden : ButtonStatus::Showed) {}

public:
	_NODISCARD CONNECT_FORCE_INLINE bool operator!() { return status == ButtonStatus::Showed ? false : true; }

protected:
	void resizeEvent(QResizeEvent *event) override {
//		auto side = qMin(event->size().width(), event->size().height());
		setFixedSize(50, 50);
		QPushButton::resizeEvent(event);
	}

private:
	ButtonStatus status = ButtonStatus::Showed;
public:
	_NODISCARD CONNECT_FORCE_INLINE CONNECT_CONSTEXPR
	const bool isEliminated() const noexcept { return status == ButtonStatus::Showed ? false : true; }

	CONNECT_FORCE_INLINE void eliminate() noexcept { this->status = ButtonStatus::Hidden; }
};
CONNECT_NAMESPACE_END
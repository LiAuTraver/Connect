#pragma once

#include <include/config.hpp>
#include <pch/qt.core.hh>

CONNECT_NAMESPACE_BEGIN
CONNECT_NAMESPACE_DETAILS_BEGIN
class Animation_fn {
public:
	Animation_fn& operator()(QPushButton* /* & (?) */ button) {
		auto buttonOpacityEffect = new QGraphicsOpacityEffect(button);
		button->setGraphicsEffect(buttonOpacityEffect);
		auto animation = new QPropertyAnimation(buttonOpacityEffect, "opacity");
		animation->setDuration(1000);
		animation->setStartValue(1);
		animation->setEndValue(0);
		QWidget::connect(animation, &QPropertyAnimation::finished, button, &QPushButton::hide);
		animation->start(QAbstractAnimation::DeleteWhenStopped);
		return *this;
	}
};

inline Animation_fn Animation;
CONNECT_NAMESPACE_DETAILS_END
CONNECT_NAMESPACE_END

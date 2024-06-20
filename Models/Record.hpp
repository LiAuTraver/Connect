#pragma once

#include "include/config.hpp"
#include "pch/std.time.hh"
#include "pch/qt.core.hh"

CONNECT_NAMESPACE_BEGIN
struct Record {
	explicit Record() : name(""), score(0), elapsedMilliseconds(0) {}

	explicit Record(const QString &name, qint64 score, qint64 elapsedMilliseconds)
			: name(name), score(score), elapsedMilliseconds(elapsedMilliseconds) {}

	virtual ~Record() = default;

	QString name;
	qint64 score;
	qint64 elapsedMilliseconds; /// time
};
CONNECT_NAMESPACE_END

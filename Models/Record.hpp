#pragma once

#include <include/config.hpp>
#include <pch/qt.core.hh>
#include <pch/std.time.hh>

CONNECT_NAMESPACE_BEGIN
#if 1
using Record = std::tuple<QString, qint64, qint64>;
CONNECT_NAMESPACE_END
#else
struct Record {
	explicit Record() : name(""), score(0), elapsedMilliseconds(0) {}

	explicit Record(const QString &name, const qint64 score, const qint64 elapsedMilliseconds) :
		name(name), score(score), elapsedMilliseconds(elapsedMilliseconds) {}

	//! copy ctor shouldn't be declared as `explicit`
	Record(const Record &rhs) = default;

	Record(Record &&rhs) noexcept = default;

	virtual ~Record() = default;


	QString name;
	qint64 score;
	qint64 elapsedMilliseconds; /// time

	_NODISCARD CONNECT_INLINE bool operator<=>(const Record &rhs) const noexcept {
		if (this->score > rhs.score)
			return true;
		else if (this->score == rhs.score) {
			if (this->elapsedMilliseconds < rhs.elapsedMilliseconds)
				return true;
			else if (this->elapsedMilliseconds == rhs.elapsedMilliseconds) {
				if (this->name < rhs.name)
					return true;
			}
		}
		return false;
	}

	_NODISCARD CONNECT_INLINE bool operator==(const Record &rhs) const noexcept(noexcept(this->name == rhs.name)) {
		return name == rhs.name && score == rhs.score && elapsedMilliseconds == rhs.elapsedMilliseconds;
	}

	_NODISCARD CONNECT_INLINE bool operator!=(const Record &rhs) const noexcept(noexcept(!this->operator==(rhs))) {
		return !this->operator==(rhs);
	}

	template<class H>
		requires(H::combine(std::move(H{}), Connect::Record::name, Connect::Record::score,
							Connect::Record::elapsedMilliseconds))
	friend H AbslHashValue(H, const Record &);
};

CONNECT_NAMESPACE_END

template<class H>
	requires(H::combine(std::move(H{}), Connect::Record::name, Connect::Record::score,
						Connect::Record::elapsedMilliseconds))
H AbslHashValue(H h, const Connect::Record &m) {
	return H::combine(std::move(h), m.name, m.score, m.elapsedMilliseconds);
}
#endif

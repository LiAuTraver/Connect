#pragma once

#include <include/config.hpp>
#include <absl/hash/hash.h>
#include "Models/Record.hpp"

#if 1
#else
CONNECT_NAMESPACE_BEGIN
struct RecordHash {
	_NODISCARD CONNECT_FORCE_INLINE size_t operator()(const Record &record) const {
		return
				absl::Hash<QString>()(record.name)
				^ (absl::Hash<qint64>()(record.score) << 1)
				^ (absl::Hash<qint64>()(record.elapsedMilliseconds) << 2);
	}
};
CONNECT_NAMESPACE_END
#endif

#pragma once

#include <include/config.hpp>
#include <pch/qt.core.hh>
#include <pch/std.container.hh>
#include "Models/Record.hpp"
#include "Helpers/RankComparator.hpp"
#include <absl/container/flat_hash_set.h>
#include <absl/container/node_hash_set.h>

CONNECT_NAMESPACE_BEGIN
class Records {
private:
	// fixme: needs has, not predicate
//	absl::flat_hash_set<Record,RankComparator> records;
//	std::set<Record,RankComparator> records2;
//	absl::node_hash_set<Record,RankComparator> records3;
};
CONNECT_NAMESPACE_END
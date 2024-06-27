#pragma once

#include <include/config.hpp>
#include <pch/qt.core.hh>

CONNECT_NAMESPACE_BEGIN
CONNECT_OPT_1_NAMESPACE_BEGIN
using Record = std::tuple<QString, qint64, qint64>;
CONNECT_OPT_1_NAMESPACE_END
CONNECT_OPT_2_NAMESPACE_BEGIN
using Record = std::tuple<std::string, qint64, qint64>;
CONNECT_OPT_2_NAMESPACE_END
CONNECT_NAMESPACE_END

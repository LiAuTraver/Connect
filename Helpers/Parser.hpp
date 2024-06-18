#pragma once
#include "include/config.hpp"
#include "pch/qt.xml.hh"

CONNECT_NAMESPACE_BEGIN
class Parser {
public:
	Parser(const std::string_view stringView): file(stringView.data()){}

	~Parser() = default;

private:
	QFile file;
	QDomDocument document;
	QDomElement element;
	QDomNodeList nodeList;
};
CONNECT_NAMESPACE_END

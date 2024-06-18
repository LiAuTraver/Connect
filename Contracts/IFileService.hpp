#include "include/config.hpp"
#include "pch/qt.core.hh"
#include "pch/std.io.hh"
#include "pch/qt.xml.hh"
class IFileService {
public:
	IFileService() = default;
	virtual ~IFileService() = default;
//	// for ref-types
//	virtual void loadFile(const QString &path)& = 0;
//	virtual void saveFile(const QString &path)& = 0;
//	virtual void loadDirectory(const QString &path)& = 0;
//	virtual void saveDirectory(const QString &path)& = 0;
//	// for ordinary types
//	virtual void loadFile(const QString &path)&& = 0;
//	virtual void saveFile(const QString &path)&& = 0;
//	virtual void loadDirectory(const QString &path)&& = 0;
//	virtual void saveDirectory(const QString &path)&& = 0;
protected:
    QDir dir;
};
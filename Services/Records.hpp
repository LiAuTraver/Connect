#pragma once

#include <include/config.hpp>
#include <pch/qt.core.hh>
#include <pch/std.container.hh>
#include "Helpers/RecordComparator.hpp"
#include "Models/Record.hpp"

CONNECT_NAMESPACE_BEGIN
class Records {
public:
	using size_type = qsizetype;

	CONNECT_FORCE_INLINE bool OnInitialize(const char *filePath = RECORD_FILE_PATH) { return loadData(filePath); }

	void printRecords() const {
		for (const auto &record: records) {
			qDebug() << "Name: " << std::get<0>(record) << " Score: " << std::get<1>(record)
					 << " Time: " << std::get<2>(record);
			// LOG(INFO) << "Name: " << std::get<0>(record).toStdString() << " Score: " << std::get<1>(record)
			// 		  << " Time: " << std::get<2>(record);
		}
	}

	bool saveData(const char *filePath = RECORD_FILE_PATH) const {
		QJsonArray recordsJsonArray;
		for (const auto &record: records)
			recordsJsonArray.append(QJsonObject{
					{"name", std::get<0>(record)}, {"score", std::get<1>(record)}, {"time", std::get<2>(record)}});
		QJsonObject json{{"records", recordsJsonArray}};
		QFile file(filePath);
		if (not file.open(QIODevice::WriteOnly | QIODevice::Text)) {
			return qWarning() << "Failed to open file for writing:" << file.errorString(), false;
		}
		QJsonDocument jsonDocument(json);
		file.write(jsonDocument.toJson(QJsonDocument::Indented));
		return file.close(), true;
	}

	void jsonToRecords(const QJsonObject &object) noexcept
	/* note: except for memory allocation failure etc. I do not consider it. */ {
		records.clear();
		//! note: no need to use `try-catch` to wrap: Qt's `toXxx` functions are all exception-free
		//! fixme: not sure if i can replace this recordArray vvvv using above ^^^^: Might be UB.
		std::ranges::for_each(object["records"].toArray(), [&](const auto &array) mutable -> void {
			QJsonObject recordObject = array.toObject();
			this->records.emplace(Record{recordObject["name"].toString({}),
										 recordObject["score"].toInt(std::numeric_limits<size_type>::quiet_NaN()),
										 recordObject["time"].toInt(std::numeric_limits<size_type>::quiet_NaN())});
		});
	}

	bool loadData(const char *filePath = RECORD_FILE_PATH) {
		QFile file(filePath);
		if (not file.open(QIODevice::ReadOnly | QIODevice::Text))
			return qWarning() << "Could not open file.", false;

		QByteArray loadData = file.readAll();
		file.close();
		QJsonParseError parseError;
		QJsonDocument loadDocument(QJsonDocument::fromJson(std::move(loadData), &parseError));

		if (parseError.error) /* error is an enum and QJsonParseError::NoError is `0` */
			return qWarning() << "Failed to parse json: " << parseError.errorString(), false;

		if (not loadDocument.isObject())
			return qWarning() << "JSON is not an object; load data failed.", false;

		return jsonToRecords(loadDocument.object()), true;
	}

	_NODISCARD CONNECT_FORCE_INLINE
			//! fixme: ref or not? (multi-thread)
			bool
			addRecord(const Record &record) {
		//! note: emplace returns a pair: first is iterator, second indicates whether the emplacement success(returns
		//! true);
		return records.emplace(record).second;
	}

	_NODISCARD CONNECT_FORCE_INLINE auto getRecords() const noexcept { return records; }

	_NODISCARD CONNECT_FORCE_INLINE Records &setRecords(const std::set<Record, RecordComparator> &records) noexcept {
		return this->records = records, *this;
	}

	_NODISCARD CONNECT_FORCE_INLINE
			//! fixme: seems not correct when multithreading.
			bool
			deleteRecord(const Record &record) noexcept(noexcept(records.erase(record))) {
		return static_cast<bool>(records.erase(record));
	}

public:
	static constinit const char *RECORD_FILE_PATH;

private:
	std::set<Record, RecordComparator> records;
};

constinit const char *Records::RECORD_FILE_PATH = R"(M:/Projects/Connect/Resources/records/records.json)";

CONNECT_NAMESPACE_END

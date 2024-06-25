#pragma once
#include <Contracts/ISerializer.hpp>
#include <Helpers/Actions.hpp>
#include <Helpers/RecordComparator.hpp>
#include <Models/Record.hpp>
#include <include/config.hpp>
#include <magic_enum.hpp>
#include <pch/absl.status.hh>
#include <pch/nlohmann.json.hh>
#include <pch/std.container.hh>
#include <pch/std.io.hh>
CONNECT_NAMESPACE_BEGIN
inline namespace opt1 {
class RecordSerializer extends ISerializer {
public:
	RecordSerializer() = default;
	using size_type = qsizetype;
	using recordsCollection = std::set<Record, RecordComparator>;
	using recordsCollectionOpt = std::optional<recordsCollection>;

public:
	_NODISCARD static recordsCollectionOpt deserialize(const char*,
													   OpenModeFlag flag = OpenModeFlag::ReadOnly | OpenModeFlag::Text);
	static absl::Status serialize(const recordsCollection& records, const char*,
								  OpenModeFlag flag = OpenModeFlag::WriteOnly);

private:
	static recordsCollectionOpt process(const QByteArray&);

	/* note: Qt itself is almost exception-safe, except for memory allocation failure etc. I do not consider it. */
	static recordsCollectionOpt toRecords(const QJsonArray&) noexcept;
};

inline RecordSerializer::recordsCollectionOpt RecordSerializer::deserialize(const char* filePath, OpenModeFlag flag) {
	// QFile file(filePath);
	// if (not file.open(static_cast<QIODeviceBase::OpenModeFlag>(flag)))
	// 	return qWarning() << "Could not open file.", std::nullopt;
	// return process(file.readAll());
	std::fstream file(filePath);
	if (not file.is_open()) return qWarning() << "Could not open file.", std::nullopt;
	std::stringstream ss;
	ss << file.rdbuf();	 // Read the file content into stringstream
	file.close();

	std::string str = ss.str();	 // Convert stringstream to std::string
	// LOG(INFO) << str;
	QByteArray byteArray(str.c_str(), str.size());	// Create QByteArray from std::string
	return process(byteArray);
}

//! note: code here are highly nested
inline absl::Status RecordSerializer::serialize(const recordsCollection& records, const char* filePath,
												OpenModeFlag flag) {
	QJsonArray recordsJsonArray;
	std::ranges::for_each(records, [&](const auto& record) mutable -> void {
		recordsJsonArray.append(QJsonObject{
				{"name", std::get<0>(record)}, {"score", std::get<1>(record)}, {"time", std::get<2>(record)}});
	});
	if (QFile file(filePath); not file.open(static_cast<QIODeviceBase::OpenModeFlag>(flag))) {
		return qWarning() << "Failed to open file for writing:" << file.errorString(),
			   absl::PermissionDeniedError("Failed to open file for writing.");
	} else {
		file.write(QJsonDocument({"records", recordsJsonArray}).toJson(QJsonDocument::Indented));
		return file.close(), absl::OkStatus();
	}
}

inline RecordSerializer::recordsCollectionOpt RecordSerializer::process(const QByteArray& data)  {
    QJsonParseError parseError;
    QJsonDocument document(QJsonDocument::fromJson(data, &parseError));

    if (parseError.error != QJsonParseError::NoError) {
        qWarning() << "Failed to parse JSON: " << parseError.errorString();
        return std::nullopt;
    }

    if (!document.isArray()) {
        qWarning() << "JSON is not an array; load data failed.";
        return std::nullopt;
    }

    QJsonArray jsonArray = document.array();
    if (jsonArray.isEmpty()) {
        qWarning() << "JSON array is empty.";
        return std::nullopt;
    }

    if (!jsonArray[0].isString() || jsonArray[0].toString() != "records") {
        qWarning() << "First element is not 'records' key.";
        return std::nullopt;
    }

    if (!jsonArray[1].isArray()) {
        qWarning() << "Second element is not an array.";
        return std::nullopt;
    }

    QJsonArray recordsArray = jsonArray[1].toArray();
    return toRecords(recordsArray);
}

inline RecordSerializer::recordsCollectionOpt RecordSerializer::toRecords(const QJsonArray& jsonArray)noexcept {
    recordsCollection records;
    std::ranges::for_each(jsonArray, [&](const auto& array) mutable -> void {
        QJsonObject recordObject = array.toObject();
        records.emplace(Record{
            recordObject["name"].toString({}),
            recordObject["score"].toInt(std::numeric_limits<size_type>::quiet_NaN()),
            recordObject["time"].toInt(std::numeric_limits<size_type>::quiet_NaN())
        });
    });
    return std::make_optional(records);
}

//! fixme: WHY PASSING OBJECT ALWAYS BEEN NULL AND SPENT ME TWO AFTERNOON TO FIX AND FINALLY CONVERT TO PASSING THE ARRAY AND CONVERT TO OBJECT AGAIN
//
// inline RecordSerializer::recordsCollectionOpt RecordSerializer::process(const QByteArray& data) {
// 	QJsonParseError parseError;
// 	QJsonDocument document(QJsonDocument::fromJson(data, &parseError));
// 	// Check for JSON parsing errors
// 	if (parseError.error != QJsonParseError::NoError) {
// 		qWarning() << "Failed to parse JSON: " << parseError.errorString();
// 		return std::nullopt;
// 	}
// 	auto d = document.array();
// 	// Check if the document is an object
// 	// if (!document.isObject()) {
// 	// 	qWarning() << "JSON is not an object; load data failed.";
// 	// 	return std::nullopt;
// 	// }
// 	// // Extract the JSON object
// 	// QJsonObject obj = document.object();
// 	// // Check if the object is empty or has expected structure
// 	// if (obj.isEmpty()) {
// 	// 	qWarning() << "JSON object is empty.";
// 	// 	return std::nullopt;
// 	// }
// 	// // Debugging statement to print the object
// 	qDebug() << "Parsed JSON object: " << d;
// 	return toRecords(d);
// }
//
// inline RecordSerializer::recordsCollectionOpt RecordSerializer::toRecords(const QJsonArray& jsonArray) noexcept {
// 	recordsCollection records;
// 	//! note: no need to use `try-catch` to wrap: Qt's `toXxx` functions are all exception-free
// 	std::ranges::for_each(jsonArray, [&](const auto& array) mutable -> void {
// 		QJsonObject recordObject = array.toObject();
// 		records.emplace(Record{recordObject["name"].toString({}),
// 							   recordObject["score"].toInt(std::numeric_limits<size_type>::quiet_NaN()),
// 							   recordObject["time"].toInt(std::numeric_limits<size_type>::quiet_NaN())});
// 	});
// 	return std::make_optional(records);
// }

inline constexpr RecordSerializer RecordSerializer;
}  // namespace opt1

namespace opt2 {
class RecordSerializer extends ISerializer {
public:
	RecordSerializer() = default;
	using size_type = qsizetype;
	using recordsCollection = std::set<Record, RecordComparator>;
	using recordsCollectionOpt = std::optional<recordsCollection>;

public:
	_NODISCARD static recordsCollectionOpt deserialize(const char*);
	static absl::Status serialize(const recordsCollection&, const char*);
};
inline RecordSerializer::recordsCollectionOpt RecordSerializer::deserialize(const char* filePath) {
	std::ifstream recordsFile(filePath, std::ios::in);
	if (not recordsFile.is_open()) return qDebug() << "File not exist: " << filePath, std::nullopt;
	nlohmann::json recordsJson;
	recordsFile >> recordsJson;
	// Check if the "records" key exists and is an array
	if (!recordsJson.contains("records") || !recordsJson["records"].is_array())
		return qWarning() << "file does not containing any record.",
			   std::nullopt;  // Return an empty optional if the format is incorrect
	const auto& recordsJsonArray = recordsJson["records"];
	recordsCollection records;
	std::ranges::for_each(recordsJsonArray, [&](const auto& record) {
		if (recordsJsonArray.contains("name") && recordsJsonArray.contains("score") &&
			recordsJsonArray.contains("time"))
			records.emplace(Record{recordsJsonArray["name"], recordsJsonArray["score"], recordsJsonArray["time"]});
		else
			qWarning() << "Invalid record. Skipping.";
	});
	return std::make_optional(records);
}
inline absl::Status RecordSerializer::serialize(const recordsCollection& records, const char* filePath) {
	// std::ofstream recordsFile(filePath, std::ios::out);
	// if (not recordsFile.is_open()) return absl::PermissionDeniedError("file cannot be written");
	// nlohmann::json recordsJson = nlohmann::json::object();
	// nlohmann::json recordsArray = nlohmann::json::array();
	// std::ranges::for_each(records, [&](const Record& record) {
	// 	nlohmann::json jsonRecord;
	// 	jsonRecord.emplace_back("name", std::get<0>(record))
	// 			.emplace_back("score", std::get<1>(record))
	// 			.emplace_back("time", std::get<2>(record));
	// 	recordsJson.emplace_back(jsonRecord);
	// });
	// recordsJson.emplace_back("records", std::move(recordsArray));
	// recordsFile << recordsJson.dump(4);
	return absl::OkStatus();
}
inline constexpr RecordSerializer RecordSerializer;
}  // namespace opt2

CONNECT_NAMESPACE_END

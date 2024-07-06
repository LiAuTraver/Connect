#pragma once
#include <include/details.hpp>
#include <Models/Record.hpp>
#include <include/config.hpp>
#include <magic_enum.hpp>
#include <pch/absl.status.hh>
#include <pch/nlohmann.json.hh>
#include <pch/std.container.hh>
#include <pch/std.io.hh>
CONNECT_NAMESPACE_BEGIN
CONNECT_OPT_1_NAMESPACE_BEGIN
class RecordSerializer implements ISerializer {
public:
	RecordSerializer() = default;
	using size_type = qsizetype;
	using recordsCollection = std::set<Record, RecordComparator_fn>;
	using recordsCollectionOpt = std::optional<recordsCollection>;

public:
	template <typename = json>
	_NODISCARD recordsCollectionOpt deserialize(const char*,
												OpenModeFlag flag = ReadOnly | Text) const;
	template <typename = json>
	absl::Status serialize(const recordsCollection& records, const char*,
						   OpenModeFlag flag = WriteOnly) const;

private:
	static recordsCollectionOpt process(const QByteArray&) noexcept;

	static std::expected<QJsonArray, const char*> checkArray(const QByteArray& byteArray) {
		QJsonParseError parseError;
		QJsonDocument document(QJsonDocument::fromJson(byteArray, &parseError));

		if (parseError.error not_eq QJsonParseError::NoError)
			return qWarning() << "Failed to parse JSON: " << parseError.errorString(),
				   std::unexpected("Failed to parse JSON: ");

		if (not document.isArray())
			return qWarning() << "JSON is not an object; load data failed.",
				   std::unexpected("JSON is not an object; load data failed.");

		QJsonArray jsonArray = document.array();

		if (jsonArray.isEmpty())
			return qWarning() << "JSON array is empty. Nothing to do.",
				   std::unexpected("JSON array is empty. Nothing to do.");

		return jsonArray;
	}

	/* note: Qt itself is almost exception-safe, except for memory allocation failure etc.
	 * I do not consider it. */
	static recordsCollectionOpt toRecords(const QJsonArray&) noexcept;
};
template <typename>
inline RecordSerializer::recordsCollectionOpt RecordSerializer::deserialize(
	const char* filePath, OpenModeFlag flag) const {
	QFile file(filePath);
	if (not file.open(static_cast<QIODeviceBase::OpenModeFlag>(flag)))
		return qWarning() << "Could not open file.", std::nullopt;
	return process(file.readAll());
}
//! note: code here are highly nested
template <typename>
inline absl::Status RecordSerializer::serialize(const recordsCollection& records,
												const char* filePath, OpenModeFlag flag) const {
	QJsonArray recordsJsonArray;
	std::ranges::for_each(records, [&](const auto& record) mutable -> void {
		recordsJsonArray.append(QJsonObject{{"name", std::get<0>(record)},
											{"score", std::get<1>(record)},
											{"time", std::get<2>(record)}});
	});
	if (QFile file(filePath); not file.open(static_cast<QIODeviceBase::OpenModeFlag>(flag)))
		return qWarning() << "Failed to open file for writing:" << file.errorString(),
			   absl::PermissionDeniedError("Failed to open file for writing.");
	else
		return file.write(
				   QJsonDocument({"records", recordsJsonArray}).toJson(QJsonDocument::Indented)),
			   file.close(), absl::OkStatus();
}

inline RecordSerializer::recordsCollectionOpt RecordSerializer::process(
	const QByteArray& data) noexcept {
	auto jsonArrayExp = checkArray(data);
	if (not jsonArrayExp) {
		LOG(ERROR) << "Failed to parse json: " << jsonArrayExp.error();
		return std::nullopt;
	}

	QJsonArray recordsArray = jsonArrayExp.value()[1].toArray();
	return toRecords(recordsArray);
}

inline RecordSerializer::recordsCollectionOpt RecordSerializer::toRecords(
	const QJsonArray& jsonArray) noexcept {
	recordsCollection records;
	std::ranges::for_each(jsonArray, [&](const auto& array) mutable -> void {
		QJsonObject recordObject = array.toObject();
		records.emplace(
			Record{recordObject["name"].toString({}),
				   recordObject["score"].toInt(std::numeric_limits<size_type>::quiet_NaN()),
				   recordObject["time"].toInt(std::numeric_limits<size_type>::quiet_NaN())});
	});
	return std::make_optional(records);
}
inline constexpr RecordSerializer RecordSerializer;
CONNECT_OPT_1_NAMESPACE_END

// opt 2 is nothing but another choice because the error described above !
CONNECT_OPT_2_NAMESPACE_BEGIN
#pragma region folded
class RecordSerializer extends ISerializer {
public:
	RecordSerializer() = default;
	using size_type = qsizetype;
	using recordsCollection = std::set<Record, RecordComparator_fn>;
	using recordsCollectionOpt = std::optional<recordsCollection>;

public:
	_NODISCARD static recordsCollectionOpt deserialize(const char*);
	static absl::Status serialize(const recordsCollection&, const char*);
};
inline RecordSerializer::recordsCollectionOpt RecordSerializer::deserialize(const char* filePath) {
	std::ifstream recordsFile(filePath, std::ios::in);
	if (not recordsFile.is_open())
		return qDebug() << "File not exist: " << filePath, std::nullopt;
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
			records.emplace(Record{recordsJsonArray["name"], recordsJsonArray["score"],
								   recordsJsonArray["time"]});
		else
			qWarning() << "Invalid record. Skipping.";
	});
	return std::make_optional(records);
}
inline absl::Status RecordSerializer::serialize(const recordsCollection& records,
												const char* filePath) {
	// std::ofstream recordsFile(filePath, std::ios::out);
	// if (not recordsFile.is_open()) return absl::PermissionDeniedError("file cannot be
	// written"); nlohmann::json recordsJson = nlohmann::json::object(); nlohmann::json
	// recordsArray = nlohmann::json::array(); std::ranges::for_each(records, [&](const
	// Record& record) { 	nlohmann::json jsonRecord; 	jsonRecord.emplace_back("name",
	// std::get<0>(record)) 			.emplace_back("score", std::get<1>(record))
	// 			.emplace_back("time", std::get<2>(record));
	// 	recordsJson.emplace_back(jsonRecord);
	// });
	// recordsJson.emplace_back("records", std::move(recordsArray));
	// recordsFile << recordsJson.dump(4);
	return absl::OkStatus();
}
inline constexpr RecordSerializer RecordSerializer;
#pragma endregion
CONNECT_OPT_2_NAMESPACE_END

CONNECT_NAMESPACE_END

#pragma once
#include <Contracts/ISerializer.hpp>
#include <Helpers/Actions.hpp>
#include <Helpers/RecordComparator.hpp>
#include <Models/Record.hpp>
#include <include/config.hpp>
#include <magic_enum.hpp>
CONNECT_NAMESPACE_BEGIN

class RecordSerializer extends ISerializer{
public:
	RecordSerializer() = default;
	using size_type = qsizetype;
	using recordsCollection = std::set<Record, RecordComparator>;
	using recordsCollectionOpt = std::optional<recordsCollection>;

public:
	template<typename ext = json>
	_NODISCARD static recordsCollectionOpt deserialize(const char*,
													   OpenModeFlag flag = OpenModeFlag::ReadOnly | OpenModeFlag::Text);
	template<typename ext = json>
	static bool serialize(const recordsCollection& records, const char*, OpenModeFlag flag = OpenModeFlag::WriteOnly);

private:
	template<typename ext>
	static recordsCollectionOpt process(ext&&);

	/* note: Qt itself is almost exception-safe, except for memory allocation failure etc. I do not consider it. */
	template<typename ext>
	static recordsCollectionOpt toRecords(ext&&) noexcept;
};

template<typename ext>
RecordSerializer::recordsCollectionOpt RecordSerializer::deserialize(const char* filePath, OpenModeFlag flag) {
	QFile file(filePath);
	if (not file.open(static_cast<QIODeviceBase::OpenModeFlag>(flag)))
		return qWarning() << "Could not open file.", std::nullopt;
	return process(file.readAll());
}

//! note: code here are highly nested
template<typename ext>
bool RecordSerializer::serialize(const recordsCollection& records, const char* filePath, OpenModeFlag flag) {
	QJsonArray recordsJsonArray;
	std::ranges::for_each(records, [&](const auto& record) mutable -> void {
		recordsJsonArray.append(QJsonObject{
				{"name", std::get<0>(record)}, {"score", std::get<1>(record)}, {"time", std::get<2>(record)}});
	});
	if (QFile file(filePath); not file.open(static_cast<QIODeviceBase::OpenModeFlag>(flag))) {
		return qWarning() << "Failed to open file for writing:" << file.errorString(), false;
	} else {
		file.write(QJsonDocument({"records", recordsJsonArray}).toJson(QJsonDocument::Indented));
		return file.close(), true;
	}
}


template<typename ext>
RecordSerializer::recordsCollectionOpt RecordSerializer::process(ext&& data) {
	QJsonParseError parseError;
	QJsonDocument document(QJsonDocument::fromJson(data, &parseError));
	if (parseError.error) /* error is an enum and QJsonParseError::NoError is `0` */
		return qWarning() << "Failed to parse json: " << parseError.errorString(), std::nullopt;
	if (not document.isObject()) return qWarning() << "JSON is not an object; load data failed.", std::nullopt;
	return toRecords(document.object());
}

template<typename ext>
RecordSerializer::recordsCollectionOpt RecordSerializer::toRecords(ext&& object) noexcept {
	recordsCollection records;
	//! note: no need to use `try-catch` to wrap: Qt's `toXxx` functions are all exception-free
	//! fixme: not sure if i can replace this recordArray vvvv using above ^^^^: Might be UB.
	std::ranges::for_each(object["records"].toArray(), [&](const auto& array) mutable -> void {
		QJsonObject recordObject = array.toObject();
		records.emplace(Record{recordObject["name"].toString({}),
							   recordObject["score"].toInt(std::numeric_limits<size_type>::quiet_NaN()),
							   recordObject["time"].toInt(std::numeric_limits<size_type>::quiet_NaN())});
	});
	return std::make_optional(records);
}

inline constexpr RecordSerializer RecordSerializer;
CONNECT_NAMESPACE_END

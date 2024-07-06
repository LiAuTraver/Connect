#pragma once

#include <include/config.hpp>
#include <include/details.hpp>
#include <pch/absl.log.hh>
#include <pch/absl.status.hh>
#include <pch/qt.core.hh>
#include <pch/std.container.hh>
CONNECT_NAMESPACE_BEGIN
CONNECT_OPT_1_NAMESPACE_BEGIN
class ResourcesSerializer_fn implements ISerializer {
public:
	ResourcesSerializer_fn() = default;
	using size_type = qsizetype;
	using resourcesCollection = std::map<QString, std::vector<QString>>;
	using resourcesCollectionOpt = std::optional<resourcesCollection>;

public:
	_NODISCARD resourcesCollectionOpt deserialise(const std::filesystem::path& filePath,
												  OpenModeFlag flag = ReadOnly | Text) const;

	static std::expected<QJsonObject, const char*> checkArray(const QByteArray& byteArray);
};
inline ResourcesSerializer_fn::resourcesCollectionOpt ResourcesSerializer_fn::deserialise(
	const std::filesystem::path& filePath, OpenModeFlag flag) const {
	resourcesCollection resources;
	QFile file(filePath);
	if (not file.open(static_cast<QIODeviceBase::OpenModeFlag>(flag)))
		return qWarning() << "Could not open file.", std::nullopt;
	auto jsonObjectExp = checkArray(file.readAll());
	if (not jsonObjectExp) {
		LOG(ERROR) << "Failed to parse json: " << jsonObjectExp.error();
		return std::nullopt;
	}
	auto object = jsonObjectExp.value();
	for (auto it = object.begin(); it != object.end(); ++it) {
		auto key = it.key();
		auto res_array = it.value().toArray();
		std::vector<QString> ress;
		std::ranges::for_each(
			res_array, [&](const auto& val) { ress.emplace_back(val.toString()); });
		resources.insert_or_assign(key, std::move(ress));
	}
	return std::make_optional(resources);
}
inline std::expected<QJsonObject, const char*> ResourcesSerializer_fn::checkArray(
	const QByteArray& byteArray) {
	QJsonParseError parseError;
	QJsonDocument document(QJsonDocument::fromJson(byteArray, &parseError));

	if (parseError.error not_eq QJsonParseError::NoError)
		return qWarning() << "Failed to parse JSON: " << parseError.errorString(),
			   std::unexpected(fmt::format(fmt::runtime("Failed to parse JSON: {}"),
										   parseError.errorString().toStdString())
								   .c_str());

	if (not document.isObject())
		return qWarning() << "JSON is not an object; load data failed.",
			   std::unexpected("JSON is not an object; load data failed.");

	QJsonObject jsonObject = document.object();

	if (jsonObject.isEmpty())
		return qWarning() << "JSON array is empty. Nothing to do.",
			   std::unexpected("JSON array is empty. Nothing to do.");

	return jsonObject;
}
inline constexpr ResourcesSerializer_fn ResourcesSerializer;
CONNECT_OPT_1_NAMESPACE_END
CONNECT_NAMESPACE_END

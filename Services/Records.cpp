#include <Helpers/RecordSerializer.hpp>
#include <Services/Records.hpp>

constinit const char *Connect::Records::RECORD_FILE_PATH = R"(M:/Projects/Connect/Resources/records/records.json)";

void Connect::Records::printRecords() const {
	for (const auto &record: recordCollection) {
		const auto &[name, score, time] = record;
		qDebug() << "Name: " << name << " Score: " << score
				 << " Time: " << time;
		fmt::println("Name: {} Scroe: {} Time: {}",name.toStdString(),score,time);
	}
}
absl::Status Connect::Records::saveData(const char *filePath) const {
	return RecordSerializer.serialize(recordCollection, filePath);
}
absl::Status Connect::Records::loadData(const char *filePath) {
	auto recordsOpt = RecordSerializer.deserialize(filePath);
	if (not recordsOpt)
		return qDebug() << "failed to load data from file " << filePath,
			   absl::InvalidArgumentError("failed to load data from file ");
	return recordCollection = std::move(recordsOpt.value()), absl::OkStatus();
}

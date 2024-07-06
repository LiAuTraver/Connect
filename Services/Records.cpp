#include <Helpers/RecordSerializer.hpp>
#include <Services/Records.hpp>

std::string Connect::Records::RECORD_FILE_PATH = (std::filesystem::current_path() / "records.json").string();

void Connect::Records::printRecords() const {
	for (const auto &record: recordCollection) {
		const auto &[name, score, time] = record;
		qDebug() << "Name: " << name << " Score: " << score
				 << " Time: " << time;
		fmt::println("Name: {} Scroe: {} Time: {}",name.toStdString(),score,time);
	}
}
absl::Status Connect::Records::saveData(const char *filePath) const {
	return RecordSerializer.serialize<json>(recordCollection, filePath);
}
absl::Status Connect::Records::loadData(const char *filePath) {
	if (auto recordsOpt = RecordSerializer.deserialize<json>(filePath); not recordsOpt)
		return qDebug() << "failed to load data from file " << filePath,
			   absl::InvalidArgumentError("failed to load data from file ");
	else return recordCollection = std::move(recordsOpt.value()), absl::OkStatus();
}

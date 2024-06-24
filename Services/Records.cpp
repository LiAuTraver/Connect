#include <Helpers/RecordSerializer.hpp>
#include <Services/Records.hpp>

constinit const char *Connect::Records::RECORD_FILE_PATH = R"(M:/Projects/Connect/Resources/records/records.json)";

void Connect::Records::printRecords() const {
	for (const auto &record: records) {
		qDebug() << "Name: " << std::get<0>(record) << " Score: " << std::get<1>(record)
				 << " Time: " << std::get<2>(record);
	}
}
bool Connect::Records::saveData(const char *filePath) const {
	return RecordSerializer.serialize<json>(records, filePath);
}
bool Connect::Records::loadData(const char *filePath) {
	auto recordsOpt = RecordSerializer.deserialize<json>(filePath);
	if (not recordsOpt) return qDebug() << "failed to load data from file " << filePath << ". ", false;
	return records = std::move(recordsOpt.value()), true;
}
bool Connect::Records::addRecord(const Record &record) {
	//! note: emplace returns a pair: first is iterator, second indicates whether the emplacement success(returns true);
	return records.emplace(record).second;
}
Connect::Records::recordsCollection Connect::Records::getRecords() const noexcept { return records; }
Connect::Records &Connect::Records::setRecords(const std::set<Record, RecordComparator> &records) noexcept {
	return this->records = records, *this;
}
Connect::Records::size_type Connect::Records::deleteRecord(const Record &record) noexcept(
		noexcept(records.erase(record))) {
	return static_cast<size_type>(records.erase(record));
}

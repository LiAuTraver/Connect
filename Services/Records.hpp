#pragma once

#include <Models/Record.hpp>
#include <include/config.hpp>
#include <pch/absl.status.hh>
#include <pch/qt.core.hh>

CONNECT_NAMESPACE_BEGIN
class Records {
public:
	using size_type = qsizetype;
	using recordsCollection = std::set<Record, RecordComparator_fn>;
	using recordsCollectionOpt = std::optional<recordsCollection>;

public:
	explicit Records() = default;

public:
	CONNECT_FORCE_INLINE absl::Status OnInitialize(const char *filePath = RECORD_FILE_PATH.c_str()) {
		return loadData(filePath);
	}

	void printRecords() const;

	absl::Status saveData(const char *filePath = RECORD_FILE_PATH.c_str()) const;

	absl::Status loadData(const char *filePath = RECORD_FILE_PATH.c_str());

	//! fixme: ref or not? (multi-thread)
	_NODISCARD CONNECT_FORCE_INLINE bool addRecord(const Record &);

	//! If we put the inline function's definition into a .cpp file,
	//!		and if it is called from some other .cpp file,
	//!		we'll get an "unresolved external" error from the linker.
	//! Unless we put the definition in the same header file rather than in .cpp file.
	_NODISCARD CONNECT_FORCE_INLINE recordsCollection getCollectionClone() const noexcept;

	_NODISCARD CONNECT_FORCE_INLINE recordsCollection &getCollection() noexcept;

	_NODISCARD CONNECT_FORCE_INLINE Records &setCollection(const std::set<Record, RecordComparator_fn> &records) noexcept;

	//! fixme: seems not correct when multithreading.
	_NODISCARD CONNECT_FORCE_INLINE size_type
	deleteRecord(const Record &record) noexcept(noexcept(recordCollection.erase(record)));

public:
	/**
	 * note: When you define a static member variable in a class,
	 *				it must be declared in the header file and defined in a single source file.
	 *		If this definition appears in multiple source files,
	 *				the linker will find multiple definitions, leading to the LNK2005(MSVC) error.
	 */
	static std::string RECORD_FILE_PATH;

private:
	recordsCollection recordCollection{};
};

CONNECT_NAMESPACE_END

inline bool Connect::Records::addRecord(const Record &record) {
	//! note: emplace returns a pair: first is iterator, second indicates whether the emplacement success(returns true);
	return recordCollection.emplace(record).second;
}
Connect::Records::recordsCollection Connect::Records::getCollectionClone() const noexcept { return recordCollection; }

Connect::Records::recordsCollection &Connect::Records::getCollection() noexcept { return recordCollection; }

Connect::Records &Connect::Records::setCollection(const std::set<Record, RecordComparator_fn> &records) noexcept {
	return this->recordCollection = records, *this;
}
Connect::Records::size_type Connect::Records::deleteRecord(const Record &record) noexcept(
		noexcept(recordCollection.erase(record))) {
	return static_cast<size_type>(recordCollection.erase(record));
}

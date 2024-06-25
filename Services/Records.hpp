#pragma once

#include <Helpers/RecordComparator.hpp>
#include <Models/Record.hpp>
#include <include/config.hpp>
#include <pch/absl.status.hh>
#include <pch/qt.core.hh>

CONNECT_NAMESPACE_BEGIN
class Records {
public:
	using size_type = qsizetype;
	using recordsCollection = std::set<Record, RecordComparator>;
	using recordsCollectionOpt = std::optional<recordsCollection>;

public:
	explicit Records() = default;

public:
	CONNECT_FORCE_INLINE absl::Status OnInitialize(const char *filePath = RECORD_FILE_PATH) {
		return loadData(filePath);
	}

	void printRecords() const;

	absl::Status saveData(const char *filePath = RECORD_FILE_PATH) const;

	absl::Status loadData(const char *filePath = RECORD_FILE_PATH);

	//! fixme: ref or not? (multi-thread)
	_NODISCARD /* CONNECT_FORCE_INLINE */ bool addRecord(const Record &);

	_NODISCARD CONNECT_FORCE_INLINE recordsCollection getRecords() const noexcept;

	_NODISCARD CONNECT_FORCE_INLINE Records &setRecords(const std::set<Record, RecordComparator> &records) noexcept;

	//! fixme: seems not correct when multithreading.
	_NODISCARD CONNECT_FORCE_INLINE size_type
	deleteRecord(const Record &record) noexcept(noexcept(records.erase(record)));

public:
	/**
	 * note: When you define a static member variable in a class,
	 *				it must be declared in the header file and defined in a single source file.
	 *		If this definition appears in multiple source files,
	 *				the linker will find multiple definitions, leading to the LNK2005(MSVC) error.
	 */
	static constinit const char *RECORD_FILE_PATH;

private:
	recordsCollection records{};
};

CONNECT_NAMESPACE_END

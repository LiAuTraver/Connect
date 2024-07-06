#include <Helpers/RecordSerializer.hpp>
#include <ViewModels/addrecorddialog.hpp>
#include <Views/leaderboard.hpp>
#include <pch/std.utils.hh>

#include "ui_Leaderboard.h"

constinit const char* Connect::Leaderboard::WARNING_MESSAGE =
	R"(The library file oleaut32 which was used by this appication may be corrupted/outdated on your computer, so this feature may not work properly. Do you want to proceceed?)";

const QRegularExpression Connect::Leaderboard::invalidPattern{"[^a-zA-Z0-9 ]"};

Connect::Leaderboard::Leaderboard(QWidget* parent)
	: QWidget(parent),
	  ui(new Ui::Leaderboard),
	  leaderboardLayout(new QVBoxLayout(this)),
	  //! note: no need to pass this as parent bacause the buttonLayout was
	  //! intended to be a `sub-layout`, otherwise Qt would pop up a warning message when
	  //! running: @code QLayout: Attempting to add QLayout "" to Connect::Leaderboard "",
	  //! which already has a layout @endcode
	  buttonLayout(new QHBoxLayout(/*leaderboardLayout*/)),
	  tableView(new QTableView(this)),
	  importRecordButton(new QPushButton("Import from file...", this)),
	  closeButton(new QPushButton("Close", this)) {
	if (auto status = records.loadData(Records::RECORD_FILE_PATH.c_str()); status not_eq absl::OkStatus()) {
		qWarning() << "Load data failed: " << status.message().data();
	}
	this->setupTable();
	leaderboardLayout->addWidget(tableView);
	buttonLayout->addWidget(importRecordButton);
	buttonLayout->addWidget(closeButton);
	leaderboardLayout->addLayout(buttonLayout);
	connect(closeButton, &QPushButton::clicked, this, [this]() {
		this->saveData();
		emit this->onLeaderboradCloseButtonClicked();
	});
	connect(importRecordButton, &QPushButton::clicked, this,
			&Leaderboard::handleImportRecordButtonClicked);
	this->setLayout(leaderboardLayout);
	ui->setupUi(this);
}

Connect::Leaderboard::~Leaderboard() {
	this->saveData();
	delete ui;
}
void Connect::Leaderboard::saveData() const {
	if (auto res = this->records.saveData(Records::RECORD_FILE_PATH.c_str()); res not_eq absl::OkStatus())
		qWarning() << "Save data failed: " << res.message().data();
	else
		qDebug("Data saved.");
}

Connect::Leaderboard& Connect::Leaderboard::setupTable() {
	const auto rowCount =
		records.getCollection().size() <= 10 ? records.getCollection().size() : 10;
	// clang-format off
	auto recordModel = new QStandardItemModel(
		static_cast<int>(rowCount),
		3,
		this);
	// clang-format on
	recordModel->setHorizontalHeaderLabels({"Name", "Score", "Elapsed Time"});
	// auto index =
	// std::remove_cvref_t<Records::recordsCollection::iterator>(records.getCollection().begin());
	// in MSVC below would failed.
	auto index = records.getCollection().begin();
	for (int row = 0; row < rowCount; row++) {
		recordModel->setItem(row, 0, new QStandardItem(QString("%1").arg(std::get<0>(*index))));
		recordModel->setItem(row, 1, new QStandardItem(QString("%1").arg(std::get<1>(*index))));
		recordModel->setItem(row, 2, new QStandardItem(QString("%1").arg(std::get<2>(*index))));
		std::ranges::advance(index, 1);
	}
	tableView->setModel(recordModel);
	return *this;
}
absl::StatusOr<QString> Connect::Leaderboard::onAddingRecord() {
	auto addRecordDialog = new AddRecordDialog(this);
	switch (addRecordDialog->exec()) {
		case QDialog::Rejected:
			return absl::CancelledError("Operation cancelled.");
		case QDialog::Accepted:
			break;
		default:
			return absl::UnknownError("Should not be here.");
	}
	if (auto name = addRecordDialog->getInput(); name.isEmpty() or name.contains(invalidPattern))
		return absl::InvalidArgumentError("Please provide a valid name.");
	else
		return name;
}
void Connect::Leaderboard::acquireName(Record& pendingRecord) {
	bool flag = false;
	while (flag != true) {
		QMessageBox* messageBox = nullptr;
		// clang-format off
		switch (auto res = onAddingRecord();res.status().code()) {
		  case absl::StatusCode::kOk:
				std::get<0>(pendingRecord) = res.value();
				flag = true;
				messageBox = new QMessageBox(
					QMessageBox::Icon::Information,
					"Info",
					"Successfully added record.",
					QMessageBox::StandardButton::Ok,
					this);
				break;
		  case absl::StatusCode::kCancelled:
				flag = true;
				break;
		  case absl::StatusCode::kInvalidArgument:
				[[fallthrough]];
		  default:
				messageBox = new QMessageBox(
					QMessageBox::Icon::Warning,
					"Warning",
					res.status().message().data(),
					QMessageBox::StandardButton::Ok,
					this);
				break;
		}
		// clang-format on
		if (not messageBox)
			continue;
		messageBox->show();
		connect(messageBox, &QMessageBox::finished, this,
				[] { /* dummy function, empty handler */ });
		messageBox->exec();
	}
}

void Connect::Leaderboard::onGameWinChangeRecord(const qint64 score, const qint64 elapsedTime) {
	auto index = records.getCollection().cbegin();
	auto size = records.getCollection().size() <= 10 ? records.getCollection().size() : 10;
	auto pendingRecord = Record{"", score, elapsedTime};
	auto position = 0ULL;
	while (position < size) {
		if (RecordComparator(*index, pendingRecord) not_eq true)
			break;
		++position;
		++index;
	}
	if (position == size)
		return;
	this->acquireName(pendingRecord);
	if (std::get<0>(pendingRecord).isEmpty())
		std::get<0>(pendingRecord) = "NaN";
	if (this->records.addRecord(pendingRecord))
		qDebug("Successfully added record");
	else
		qWarning("Identical record found.");
}

// clang-format off
void Connect::Leaderboard::handleImportRecordButtonClicked() {
	auto messageBox = new QMessageBox(
		QMessageBox::Icon::Warning,
				"Warning",
				WARNING_MESSAGE,
				QMessageBox::StandardButton::NoButton,
				this);
	messageBox->addButton(tr("Proceed"), QMessageBox::AcceptRole);
	messageBox->addButton(tr("Close"), QMessageBox::RejectRole);
	messageBox->show();
	connect(messageBox, &QMessageBox::finished, this, &Leaderboard::handleMessageBoxButtonClicked);
	messageBox->exec();
}
void Connect::Leaderboard::handleMessageBoxButtonClicked() {
	auto messageBox = qobject_cast<QMessageBox*>(sender());
	if (not messageBox) return;
	if (messageBox->clickedButton()->text() == tr("Close")) return;
	if (messageBox->clickedButton()->text() != tr("Proceed"))
		return static_cast<void>(qCritical() << "You shouldn't be here.");
	if (auto newRecordsOpt =
		RecordSerializer.deserialize<json>(
			QFileDialog::getOpenFileName(
				this,
				tr("Open a file..."),
				".",
				tr("Json File (*.json);;All Files (*.*)")
				)
						.toStdString()
						.c_str()
						)) {
		std::ranges::for_each(newRecordsOpt.value(),
			[&](auto&& newRecord) {
			if (not records.addRecord(newRecord))
				qDebug() << "failed to add a record: already existed";
		   });
		this->setupTable();
		return;
						}
	/** fixme: ^^^^^^^^^^^^^^^^^^^^^^ the file path is nosense. NOT MY FAULT:
	 * The library file corrupted:
	 * mincore\com\oleaut32\dispatch\ups.cpp(2126)\OLEAUT32.dll!00007FFEFBAEEB3D:
	 * (caller: 00007FFEFBAEF1C2) ReturnHr(1) tid(3b70) 8002801D Library not registered.
	 * (lldb) print cStr // filaPath above
	 * (const char*) $2 =
	 * 0x000002bb8191f880 "��������������������������������������������������������������������
	 *
	 * or its my fault? memory allocation? see
	 * https://forum.qt.io/topic/152714/library-not-registered-error/11
	 */
	qDebug() << "No suitable records found in the file.";
}
// clang-format on


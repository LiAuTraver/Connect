#include <Helpers/RecordSerializer.hpp>
#include <Views/leaderboard.hpp>

#include "ui_Leaderboard.h"

constinit const char* Connect::Leaderboard::WARNING_MESSAGE =
		R"(The library file oleaut32 which was used by this appication may be corrupted/outdated on your computer, so this feature may not work properly. Do you want to proceceed?)";

Connect::Leaderboard::Leaderboard(QWidget* parent) :
	QWidget(parent), ui(new Ui::Leaderboard), leaderboardLayout(new QVBoxLayout(this)),
	buttonLayout(new QHBoxLayout(this)), tableView(new QTableView(this)),
	importRecordButton(new QPushButton("Import from file...", this)), closeButton(new QPushButton("Close", this)) {
	buttonLayout->addWidget(importRecordButton);
	buttonLayout->addWidget(closeButton);
	connect(closeButton, &QPushButton::clicked, this, &Connect::Leaderboard::onCloseButtonClicked);
	connect(importRecordButton, &QPushButton::clicked, this, &Connect::Leaderboard::onImportRecordButtonClicked);
	if (auto status = records.loadData(Records::RECORD_FILE_PATH); status not_eq absl::OkStatus()) {
		qWarning() << "Load data failed: " << status.message().data();
	}
	this->setupTable();
	leaderboardLayout->addWidget(tableView);
	leaderboardLayout->addLayout(buttonLayout);
	this->setLayout(leaderboardLayout);
	ui->setupUi(this);
}

Connect::Leaderboard::~Leaderboard() { delete ui; }

Connect::Leaderboard& Connect::Leaderboard::setupTable() {
	const auto rowCount = records.getCollection().size() <= 10 ? records.getCollection().size() : 10;
	// clang-format off
	auto recordModel = new QStandardItemModel(
		static_cast<int>(rowCount),
		3,
		this);
	// clang-format on
	recordModel->setHorizontalHeaderLabels({"Name", "Score", "Elapsed Time"});
	// in MSVC below would failed.
	// auto index = std::remove_cvref_t<Records::recordsCollection::iterator>(records.getCollection().begin());
	auto index = records.recordCollection.begin();
	for (int row = 0; row < rowCount; row++) {
		recordModel->setItem(row, 0, new QStandardItem(QString("%1").arg(std::get<0>(*index))));
		recordModel->setItem(row, 1, new QStandardItem(QString("%1").arg(std::get<1>(*index))));
		recordModel->setItem(row, 2, new QStandardItem(QString("%1").arg(std::get<2>(*index))));
		std::ranges::advance(index, 1);
	}
	tableView->setModel(recordModel);
	return *this;
}
// clang-format off
void Connect::Leaderboard::onImportRecordButtonClicked() {
	auto messageBox = new QMessageBox(
		QMessageBox::Icon::Warning,
				"Warning",
				WARNING_MESSAGE,
				QMessageBox::StandardButton::NoButton,
				this);
	messageBox->addButton(
		tr("Proceed"),
		QMessageBox::AcceptRole);
	messageBox->addButton(
		tr("Close"),
		QMessageBox::RejectRole);
	messageBox->show();
	connect(messageBox, &QMessageBox::finished, this, &Leaderboard::onMessageBoxButtonClicked);
	messageBox->exec();
}
void Connect::Leaderboard::onMessageBoxButtonClicked() {
	auto messageBox = qobject_cast<QMessageBox*>(sender());
	if (not messageBox) return;
	if (messageBox->clickedButton()->text() == tr("Close")) return;
	if (messageBox->clickedButton()->text() != tr("Proceed"))
		return static_cast<void>(qCritical() << "You shouldn't be here.");
	if (auto newRecordsOpt =
		RecordSerializer.deserialize(
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

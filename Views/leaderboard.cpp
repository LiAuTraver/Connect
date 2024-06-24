#include <Views/leaderboard.hpp>

#include "Helpers/RecordSerializer.hpp"
#include "ui_Leaderboard.h"

Connect::Leaderboard::Leaderboard(QWidget* parent) :
	QWidget(parent), ui(new Ui::Leaderboard), leaderboardLayout(new QHBoxLayout(this)),
	importRecordButton(new QPushButton("import from file...", this)), closeButton(new QPushButton("close", this)) {
	leaderboardLayout->addWidget(importRecordButton);
	leaderboardLayout->addWidget(closeButton);
	connect(closeButton, &QPushButton::clicked, this, &Connect::Leaderboard::onCloseButtonClicked);
	connect(importRecordButton, &QPushButton::clicked, this, &Connect::Leaderboard::onImportRecordButtonClicked);
	ui->setupUi(this);
}

Connect::Leaderboard::~Leaderboard() { delete ui; }
void Connect::Leaderboard::onImportRecordButtonClicked() {
	auto filePath =
			QFileDialog::getOpenFileName(this, tr("Open a file..."), ".", tr("Json File (*.json);;All Files (*.*)"))
					.toStdString()
					.c_str();
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
	if (auto newRecordsOpt = RecordSerializer.deserialize<json>(filePath); not newRecordsOpt)
		qDebug() << "No suitable records found in the file.";
	else
		std::ranges::for_each(newRecordsOpt.value(), [&](auto&& newRecord) {
			if (not records.addRecord(newRecord)) qDebug() << "failed to add record: already existed";
		});
}

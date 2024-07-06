#pragma once

#include <include/config.hpp>
#include <pch/qt.widgets.hh>

CONNECT_NAMESPACE_BEGIN
class AddRecordDialog extends public QDialog {
	Q_OBJECT

public:
	explicit AddRecordDialog(QWidget *parent = nullptr);
	~AddRecordDialog() override;

public:
	_NODISCARD CONNECT_FORCE_INLINE QString getInput() const noexcept;

private:
	QString name{};
	QLineEdit *nameInput;
	QLabel *nameLabel;
	QPushButton *addbutton;
	QPushButton *cancelbutton;
	QVBoxLayout *mainLayout;
	QHBoxLayout *buttonLayout;
private slots:
	void onAddButtonClicked();
};
QString AddRecordDialog::getInput() const noexcept { return name; }
CONNECT_NAMESPACE_END

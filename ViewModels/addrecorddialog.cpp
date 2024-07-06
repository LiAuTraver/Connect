#include <ViewModels/addrecorddialog.hpp>

Connect::AddRecordDialog::AddRecordDialog(QWidget *parent)
	: QDialog(parent),
	  nameInput(new QLineEdit(this)),
	  nameLabel(new QLabel("Input your name: ", this)),
	  addbutton(new QPushButton("Add", this)),
	  cancelbutton(new QPushButton("Cancel", this)),
	  mainLayout(new QVBoxLayout(this)),
	  buttonLayout(new QHBoxLayout(/*mainLayout*/)) {
	connect(addbutton, &QPushButton::clicked, this, &AddRecordDialog::onAddButtonClicked);
	connect(cancelbutton, &QPushButton::clicked, this, &QDialog::reject);
	mainLayout->addWidget(nameLabel);
	mainLayout->addWidget(nameInput);
	buttonLayout->addWidget(addbutton);
	buttonLayout->addWidget(cancelbutton);
	mainLayout->addLayout(buttonLayout);
	this->setLayout(mainLayout);
	this->setWindowTitle("New Record!");
	// QWindowsWindow::setGeometry: Unable to set geometry 215x53+1089+690 (frame: 239x117+1077+638)
	//                              on QWidgetWindow/"Connect::AddRecordDialogClassWindow" on
	//                              "\\.\DISPLAY1". Resulting geometry: 312x187+1089+690 (frame:
	//                              336x251+1077+638) margins: 12, 52, 12, 12 minimum size: 178x107
	//                              MINMAXINFO(maxSize=POINT(x=0, y=0), maxpos=POINT(x=0, y=0),
	//                              maxtrack=POINT(x=0, y=0), mintrack=POINT(x=336, y=251)))
	this->setMinimumSize(178, 107);

}
Connect::AddRecordDialog::~AddRecordDialog() = default;
void Connect::AddRecordDialog::onAddButtonClicked() {
	this->name = nameInput->text();
	this->accept();
}

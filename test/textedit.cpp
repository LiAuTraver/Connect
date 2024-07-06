// You may need to build the project (run Qt uic code generator) to get "ui_textEdit.h" resolved

#include "textedit.hpp"
#include "ui_textEdit.h"


textEdit::textEdit(QWidget *parent) :
    QWidget(parent), ui(new Ui::textEdit) {
    ui->setupUi(this);
	auto line = new QLineEdit(parent);
	line->setText("Password: ");
	line->setEchoMode(QLineEdit::Password);
}

textEdit::~textEdit() {
    delete ui;
}

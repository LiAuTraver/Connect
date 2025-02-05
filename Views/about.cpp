#include <Views/about.hpp>
#include <pch/qt.core.hh>
#include <pch/qt.widgets.hh>
#include "ui_About.h"


Connect::About::About(QWidget *parent) : QWidget(parent), ui(new Ui::About) {
	ui->setupUi(this);
	connect(this->ui->pushButton, &QPushButton::clicked, this, &About::onCloseButtonCicked);
	connect(this->ui->volumeSlider,&QSlider::valueChanged,this,&About::onVolumnSliderchanged);
}

Connect::About::~About() { delete ui; }

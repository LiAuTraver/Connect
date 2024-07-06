#pragma once
#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class textEdit; }
QT_END_NAMESPACE

class textEdit : public QWidget {
Q_OBJECT

public:
    explicit textEdit(QWidget *parent = nullptr);
    ~textEdit() override;

private:
    Ui::textEdit *ui;
};

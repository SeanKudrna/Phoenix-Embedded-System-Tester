#include "popup.h"
#include "ui_popup.h"

popup::popup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::popup)
{
    ui->setupUi(this);
}

popup::~popup()
{
    delete ui;
}

void popup::on_pushButton_clicked()
{
    this->close();
}

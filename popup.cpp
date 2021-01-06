#include "popup.h"
#include "ui_popup.h"

//Constructor
popup::popup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::popup)
{
    ui->setupUi(this);
}

//Deconstructor
popup::~popup()
{
    delete ui;
}

//Close window
void popup::on_pushButton_clicked()
{
    this->close();
}

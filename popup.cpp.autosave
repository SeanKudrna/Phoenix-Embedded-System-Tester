#include "popup.h"
#include "ui_popup.h"

//Constructor
popup::popup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::popup)
{
    ui->setupUi(this);
}//EOF constructor

//Deconstructor
popup::~popup()
{
    delete ui;
}//EOF deconstructor

//Close window
void popup::on_pushButton_clicked()
{
    this->close();
}//EOF window

#include "dactest.h"
#include "ui_dactest.h"
#include "testmenu.h"

dactest::dactest(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dactest)
{
    ui->setupUi(this);
}

dactest::~dactest()
{
    delete ui;
}

void dactest::on_pb_testmenu_clicked()
{
    testmenu *ptm = new testmenu();
    ptm->show();
    this->close();
}

#include "relaydriver.h"
#include "ui_relaydriver.h"
#include "testmenu.h"

relaydriver::relaydriver(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::relaydriver)
{
    ui->setupUi(this);
}

relaydriver::~relaydriver()
{
    delete ui;
}

void relaydriver::on_pb_testmenu_clicked()
{
    testmenu *ptm = new testmenu();

    //ptm->exec();
    ptm->show();
    this->close();

    //delete ptm;
}

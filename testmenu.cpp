#include "testmenu.h"
#include "ui_testmenu.h"
#include "mainwindow.h"
#include "powersupply2.h"
#include "dactest.h"
#include "relaydriver.h"
#include "capitalequipment.h"

extern CapitalEquipment *pce;

testmenu::testmenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::testmenu)
{
    ui->setupUi(this);

}

testmenu::~testmenu()
{
    delete ui;
}

void testmenu::on_pb_dmm_clicked()
{
    MainWindow *pmm = new MainWindow();

    pmm->show();
    this->close();

    // QUESTION / NOTE

    /*
     * Cannot
     *
     * delete pmm;
     *
     * -show() does not let you delete the pointer while viewing.
     * -window will close
     *
     * MainWindow inherits from QMainWindow rather than
     * QDialogue
     *
     * How should we handle this?
     *
     */
    //delete pmm;
}

void testmenu::on_pb_powersupply_clicked()
{
    pce->pMotorSupply->remoteMode(true);
    powersupply2 *pps = new powersupply2();

    //pps->exec();
    pps->show();
    this->close();
    //delete pps;
}

void testmenu::on_pb_relaydriver_clicked()
{
    relaydriver *prd = new relaydriver();

    //prd->exec();
    prd->show();
    this->close();

    //delete prd;
}

void testmenu::on_pb_dac_clicked()
{
    dactest *pd = new dactest();

    //pd->exec();
    pd->show();
    this->close();

    //delete pd;

}

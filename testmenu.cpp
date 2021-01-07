#include "testmenu.h"
#include "ui_testmenu.h"
#include "mainwindow.h"
#include "powersupply2.h"
#include "dactest.h"
#include "relaydriver.h"
#include "capitalequipment.h"

//Get CapitalEquipment object
extern CapitalEquipment *pce;

//Constructor
testmenu::testmenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::testmenu)
{
    ui->setupUi(this);

}//EOF Constructor

//Deconstrutor
testmenu::~testmenu()
{
    delete ui;
}//EOF Deconstructor

//Show meter UI (BK2831E)
void testmenu::on_pb_dmm_clicked()
{
    MainWindow *pmm = new MainWindow();

    pmm->show();
    this->close();
}//EOF show meter

//Show power supply UI (2901-2905)
void testmenu::on_pb_powersupply_clicked()
{
    pce->pMotorSupply->remoteMode(true);
    pce->pMotorSupply->reset();
    pce->pCharger->remoteMode(true);
    pce->pCharger->reset();
    powersupply2 *pps = new powersupply2();

    pps->show();
    this->close();
}//EOF show power supply

//Show relay UI
void testmenu::on_pb_relaydriver_clicked()
{
    relaydriver *prd = new relaydriver();

    prd->show();
    this->close();
}//EOF show relay

//Show DAC UI
void testmenu::on_pb_dac_clicked()
{
    dactest *pd = new dactest();

    pd->show();
    this->close();
}//EOF show dac

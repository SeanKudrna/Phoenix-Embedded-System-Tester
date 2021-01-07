#include "dactest.h"
#include "ui_dactest.h"
#include "testmenu.h"
#include "dac.cpp"
#include "capitalequipment.h"

//Constructor
dactest::dactest(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dactest)
{
    ui->setupUi(this);
}//EOF Constructor

//Deconstructor
dactest::~dactest()
{
    delete ui;
}//EOF Deconstructor

//Test menu button
void dactest::on_pb_testmenu_clicked()
{
    testmenu *ptm = new testmenu();
    ptm->show();
    this->close();
}//EOF test menu

//Set voltage on Dac 1
void dactest::on_pb_dac1_clicked()
{
    double voltage = ui->te_dac1->toPlainText().toDouble();
    pce->pDac->setChannelValue(MCP4728_CHANNEL_A, voltage, MCP4728_VREF_VDD, MCP4728_GAIN_1X, MCP4728_PD_MODE_NORMAL, false);
}//EOF set voltage 1

//Set voltage on Dac 2
void dactest::on_pb_dac2_clicked()
{
    double voltage = ui->te_dac2->toPlainText().toDouble();
    pce->pDac->setChannelValue(MCP4728_CHANNEL_B, voltage, MCP4728_VREF_VDD, MCP4728_GAIN_1X, MCP4728_PD_MODE_NORMAL, false);
}//EOF set voltage 2

//Set voltage on Dac 3
void dactest::on_pb_dac2_2_clicked()
{
    double voltage = ui->te_dac3->toPlainText().toDouble();
    pce->pDac->setChannelValue(MCP4728_CHANNEL_C, voltage, MCP4728_VREF_VDD, MCP4728_GAIN_1X, MCP4728_PD_MODE_NORMAL, false);
}//EOF set voltage 3

//Set voltage on Dac 4
void dactest::on_pb_dac3_clicked()
{
    double voltage = ui->te_dac4->toPlainText().toDouble();
    pce->pDac->setChannelValue(MCP4728_CHANNEL_D, voltage, MCP4728_VREF_VDD, MCP4728_GAIN_1X, MCP4728_PD_MODE_NORMAL, false);
}//EOF set voltage 4

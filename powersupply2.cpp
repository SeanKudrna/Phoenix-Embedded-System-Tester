#include "powersupply2.h"
#include "ui_powersupply2.h"
#include "testmenu.h"
#include "capitalequipment.h"
#include <iostream>
#include <string>

//Get CapitalEquipment object
extern CapitalEquipment *pce;


//Constructor
powersupply2::powersupply2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::powersupply2)
{
    ui->setupUi(this);

    //Setup timer and connect onTimer() method
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    timer->start(200);

    //Set defaults
    voltage = 0.0;
    flag = false;

    //0 = 2905, //1 = 2901
    config = 0;
}

//Deconstrutor
powersupply2::~powersupply2()
{
    delete ui;
}

//onTimer() executes every second
void powersupply2::onTimer()
{
    //If 2905, send measurment request to motor supply
    if (config == 0) {
        pce->pMotorSupply->getADC();
        pce->pMotorSupply->getNextData(&result);
    }

    //If 2901, send measurment request to charger
    else {
        pce->pCharger->getADC();
        pce->pCharger->getNextData(&result);
    }

    //Update result box in UI with updated information
    ui->te_ampreader->setHtml("<b><p align = 'center'>" + result + "</p></b>");
}

//Open test menu
void powersupply2::on_pb_testmenu_clicked()
{
    testmenu *ptm = new testmenu();
    ptm->show();
    //delete ptm;
    this->close();
}

//Increase voltage button
void powersupply2::on_pb_increasev_clicked()
{
    //Get current voltage setting
    QString current = ui->te_enablestatus->toPlainText();

    //If current voltage is < 61 (max)
    if (current.toDouble() < 61){

        //Add 0.1 to current voltage
        double New = (current.toDouble() + 0.1);

        //Update UI result box
        ui->te_enablestatus->setHtml("<b><p align = 'center'>" + QString::number(New) + "</p></b>");

        //If 2905, send commands to motor supply
        if (config == 0) {

            //voltage = pce->pMotorSupply->getVDC() + .1;
            pce->pMotorSupply->setSTEP(0.1);

            //pc->->pMotorSupply->setVDC(voltage);
            pce->pMotorSupply->increaseVOLTS();
        }

        //If 2901 send commands to charger
        else {

            //voltage = pce->pMotorSupply->getVDC() + .1;
            pce->pCharger->setSTEP(0.1);

            //pc->->pMotorSupply->setVDC(voltage);
            pce->pCharger->increaseVOLTS();
        }
    }
}

//Reset supply
void powersupply2::on_pb_reset_clicked()
{
    pce->pMotorSupply->reset();
    ui->te_enablestatus->setHtml("<b><p align = 'center'>0</p></b>");

}

//Decrease voltage button
void powersupply2::on_pb_decreasev_clicked()
{
    //Get current voltage setting
    QString current = ui->te_enablestatus->toPlainText();

    //If current voltage is > 0 (min)
    if (current.toDouble() > 0){

        //Subtract 0.1 from current voltage
        double New = (current.toDouble() - 0.1);

        //Update UI result box
        ui->te_enablestatus->setStyleSheet("text-align: center;");
        ui->te_enablestatus->setHtml("<b><p align = 'center'>" + QString::number(New) + "</p></b>");


        //If 2905, send commands to motor supply
        if (config == 0) {

            //voltage = pce->pMotorSupply->getVDC() - .1;
            pce->pMotorSupply->setSTEP(0.1);

            //pce->pMotorSupply->setVDC(voltage);
            pce->pMotorSupply->decreaseVOLTS();
        }

        //If 2901 send commands to charger
        else {

            //voltage = pce->pMotorSupply->getVDC() - .1;
            pce->pCharger->setSTEP(0.1);

            //pce->pMotorSupply->setVDC(voltage);
            pce->pCharger->decreaseVOLTS();
        }
    }
}

//Select Voltage (input)
void powersupply2::on_pb_voltageselect_clicked()
{
    //Get current voltage
    QString voltage = ui->te_voltagesetting->toPlainText();

    //If user input <= 61 and >= 0 (between min and max)
    if (voltage.toDouble() <= 61 && voltage.toDouble() >= 0){

        //If 2905, send command to motor supply
        if (config == 0)
            pce->pMotorSupply->setVOLTS(voltage.toDouble());

        //If 2901, send command to charger
        else
            pce->pCharger->setVOLTS(voltage.toDouble());

        //Update UI result box
        ui->te_enablestatus->setHtml("<b><p align = 'center'>" + voltage + "</p></b>");
        ui->te_voltagesetting->clear();
    }
}


//Clear errors
void powersupply2::on_pb_remote_clicked()
{
    //If 2905, send command to motor supply
    if (config == 0)
        pce->pMotorSupply->clearErrors();

    //If 2901, send command to charger
    else
        pce->pCharger->clearErrors();
}

//Apply voltage (on / off)
void powersupply2::on_cb_applyvoltage_stateChanged(int state)
{
    //If voltage is on
    if (state == 0){

        //Update UI result box
        ui->te_voltagestatus->setHtml("<b><p align = 'center'>OFF</p></b>");

        //If 2905, turn off voltage output on motor supply
        if (config == 0)
            pce->pMotorSupply->triggerVOLTS(0);

        //If 2901, turn off voltage output on charger
        else
            pce->pCharger->triggerVOLTS(0);

    }//EOF Turn off voltage

    //If voltage is off
    else{

        //Update UI result box
        ui->te_voltagestatus->setHtml("<b><p align = 'center'>ON</p></b>");

        //If 2905, turn on voltage output on motor
        if (config == 0)
            pce->pMotorSupply->triggerVOLTS(1);

        //If 2901, turn on voltage output on charger
        else
            pce->pCharger->triggerVOLTS(1);

    }//EOF Turn on voltage
}

//Select amps (input)
void powersupply2::on_pb_ampsselect_clicked()
{
    //Get current amps
    QString amps = ui->te_ampssetting->toPlainText();

    //If 2905, validate is between respective min/max on motor supply, update UI, send command, then erase input box.
    if (config == 0) {
        if (amps.toDouble() <= 25.1 && amps.toDouble() >= 0){
            QString amps = ui->te_ampssetting->toPlainText();
            pce->pMotorSupply->setAMPS(amps.toDouble());
            ui->te_ampsresult->setHtml("<b><p align = 'center'>" + amps + "</p></b>");
            ui->te_ampssetting->clear();
        }
    }

    //If 2901, validate is between respective min/max on charger, update UI, send command, then erase input box.
    else {
        if (amps.toDouble() <= 10.1 && amps.toDouble() >= 0){
            QString amps = ui->te_ampssetting->toPlainText();
            pce->pCharger->setAMPS(amps.toDouble());
            ui->te_ampsresult->setHtml("<b><p align = 'center'>" + amps + "</p></b>");
            ui->te_ampssetting->clear();
        }
    }
}


//Decrease amps
void powersupply2::on_pb_decreasea_clicked()
{
    //Get current amps
    QString current = ui->te_ampsresult->toPlainText();

    //If current amps > 0
    if (current.toDouble() > 0){

        //Subtract 0.1 from amps
        double New = (current.toDouble() - 0.1);

        //Update UI result box
        ui->te_ampsresult->setStyleSheet("text-align: center;");
        ui->te_ampsresult->setHtml("<b><p align = 'center'>" + QString::number(New) + "</p></b>");


        //If 2905, send commands to motor supply
        if (config == 0) {
            //voltage = pce->pMotorSupply->getVDC() - .1;
            pce->pMotorSupply->setSTEPA(0.1);

            //pce->pMotorSupply->setVDC(voltage);
            pce->pMotorSupply->decreaseAMPS();
        }

        //If 2901, send commands to charger
        else {
            //voltage = pce->pMotorSupply->getVDC() - .1;
            pce->pCharger->setSTEPA(0.1);

            //pce->pMotorSupply->setVDC(voltage);
            pce->pCharger->decreaseAMPS();
        }
    }
}

//Increase amps
void powersupply2::on_pb_increasea_clicked()
{
    //Get current amps
    QString current = ui->te_ampsresult->toPlainText();

    //If 2905
    if (config == 0) {

        //Verify current amps < 25.1 (max)
        if (current.toDouble() < 25.1){

            //Add 0.1 to current amps
            double New = (current.toDouble() + 0.1);

            //Update UI result box
            ui->te_ampsresult->setHtml("<b><p align = 'center'>" + QString::number(New) + "</p></b>");

            //voltage = pce->pMotorSupply->getVDC() + .1;
            pce->pMotorSupply->setSTEPA(0.1);

            //pc->->pMotorSupply->setVDC(voltage);
            pce->pMotorSupply->increaseAMPS();
        }
    }

    //If 2901
    else {

        //Verifiy current amps < 10.l (max)
        if (current.toDouble() < 10.1){

            //Add 0.1 to current amps
            double New = (current.toDouble() + 0.1);

            //Update UI result box
            ui->te_ampsresult->setHtml("<b><p align = 'center'>" + QString::number(New) + "</p></b>");

            //voltage = pce->pMotorSupply->getVDC() + .1;
            pce->pCharger->setSTEPA(0.1);

            //pc->->pMotorSupply->setVDC(voltage);
            pce->pCharger->increaseAMPS();
        }
    }
}


//Change config (switch between 2905 and 2901 control)
void powersupply2::on_pb_config_clicked()
{
    //If 2905, switch to 2901, update UI status box and reset charger
    if (config == 0) {
        config = 1;
        ui->te_configdisplay->setHtml("<b><p align = 'center'>BK Precision 2901</p></b>");
        ui->pb_config->setText("Switch to 2905 Config");
        pce->pCharger->reset();
        ui->te_ampsresult->setHtml("<b><p align = 'center'>10.1</p></b>");
        ui->te_enablestatus->setHtml("<b><p align = 'center'>0</p></b>");

    }

    //If 201, swich to 2905, update UI status box and reset motor supply
    else {
        config = 0;
        ui->te_configdisplay->setHtml("<b><p align = 'center'>BK Precision 2905</p></b>");
        ui->pb_config->setText("Switch to 2901 Config");
        pce->pMotorSupply->reset();
        ui->te_ampsresult->setHtml("<b><p align = 'center'>25.1</p></b>");
        ui->te_enablestatus->setHtml("<b><p align = 'center'>0</p></b>");
    }
}

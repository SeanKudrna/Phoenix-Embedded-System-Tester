#include "powersupply2.h"
#include "ui_powersupply2.h"
#include "testmenu.h"
#include "capitalequipment.h"
#include <iostream>
#include <string>

extern CapitalEquipment *pce;


powersupply2::powersupply2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::powersupply2)
{
    ui->setupUi(this);

    //set defaults
    voltage = 0.0;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    timer->start(200);
    flag = false;

    config = 0; //0 = 2905, //1 = 2901
}

powersupply2::~powersupply2()
{
    delete ui;
}

void powersupply2::onTimer()
{
    if (config == 0) {
        pce->pMotorSupply->getADC();
        pce->pMotorSupply->getNextData(&result);
    }
    else {
        pce->pCharger->getADC();
        pce->pCharger->getNextData(&result);
    }

    ui->te_ampreader->setHtml("<b><p align = 'center'>" + result + "</p></b>");
    //ui->te_ampreader->append(result);
}

void powersupply2::on_pb_testmenu_clicked()
{
    testmenu *ptm = new testmenu();
    ptm->show();
    //delete ptm;
    this->close();
}


void powersupply2::on_pb_increasev_clicked()
{
    QString current = ui->te_enablestatus->toPlainText();
    if (current.toDouble() < 61){
        double New = (current.toDouble() + 0.1);
        ui->te_enablestatus->setHtml("<b><p align = 'center'>" + QString::number(New) + "</p></b>");

        if (config == 0) {
            //voltage = pce->pMotorSupply->getVDC() + .1;
            pce->pMotorSupply->setSTEP(0.1);

            //pc->->pMotorSupply->setVDC(voltage);
            pce->pMotorSupply->increaseVOLTS();
        }
        else {
            //voltage = pce->pMotorSupply->getVDC() + .1;
            pce->pCharger->setSTEP(0.1);

            //pc->->pMotorSupply->setVDC(voltage);
            pce->pCharger->increaseVOLTS();
        }
    }
}


void powersupply2::on_pb_reset_clicked()
{
    pce->pMotorSupply->reset();
    ui->te_enablestatus->setHtml("<b><p align = 'center'>0</p></b>");

}

void powersupply2::on_pb_decreasev_clicked()
{
    QString current = ui->te_enablestatus->toPlainText();

    if (current.toDouble() > 0){
        double New = (current.toDouble() - 0.1);
        ui->te_enablestatus->setStyleSheet("text-align: center;");
        ui->te_enablestatus->setHtml("<b><p align = 'center'>" + QString::number(New) + "</p></b>");


        if (config== 0) {
            //voltage = pce->pMotorSupply->getVDC() - .1;
            pce->pMotorSupply->setSTEP(0.1);

            //pce->pMotorSupply->setVDC(voltage);
            pce->pMotorSupply->decreaseVOLTS();
        }
        else {
            //voltage = pce->pMotorSupply->getVDC() - .1;
            pce->pCharger->setSTEP(0.1);

            //pce->pMotorSupply->setVDC(voltage);
            pce->pCharger->decreaseVOLTS();
        }
    }

}


void powersupply2::on_pb_voltageselect_clicked()
{
    //connect( ui->pb_voltageselect, SIGNAL(clicked()), this, SLOT(keyboardButtonPressed()) );
    QString voltage = ui->te_voltagesetting->toPlainText();
    if (voltage.toDouble() <= 61 && voltage.toDouble() >= 0){
        if (config == 0)
            pce->pMotorSupply->setVOLTS(voltage.toDouble());
        else
            pce->pCharger->setVOLTS(voltage.toDouble());
        //ui->te_enablestatus->setAlignment(Qt::AlignCenter);
        ui->te_enablestatus->setHtml("<b><p align = 'center'>" + voltage + "</p></b>");
        ui->te_voltagesetting->clear();
        //voltage.toDouble();
    }
}



void powersupply2::on_pb_remote_clicked()
{
    if (config == 0)
        pce->pMotorSupply->clearErrors();
    else
        pce->pCharger->clearErrors();
}

void powersupply2::on_cb_applyvoltage_stateChanged(int state)
{
    if (state == 0){
        ui->te_voltagestatus->setHtml("<b><p align = 'center'>OFF</p></b>");
        if (config == 0)
            pce->pMotorSupply->triggerVOLTS(0);
        else
            pce->pCharger->triggerVOLTS(0);

    }//EOF Turn off voltage
    else{
        ui->te_voltagestatus->setHtml("<b><p align = 'center'>ON</p></b>");
        if (config == 0)
            pce->pMotorSupply->triggerVOLTS(1);
        else
            pce->pCharger->triggerVOLTS(1);
    }//EOF Turn on voltage
}

void powersupply2::on_pb_ampsselect_clicked()
{
    QString amps = ui->te_ampssetting->toPlainText();

    if (config == 0) {
        if (amps.toDouble() <= 25.1 && amps.toDouble() >= 0){
            QString amps = ui->te_ampssetting->toPlainText();
            pce->pMotorSupply->setAMPS(amps.toDouble());
            ui->te_ampsresult->setHtml("<b><p align = 'center'>" + amps + "</p></b>");
            ui->te_ampssetting->clear();
        }
    }
    else {
        if (amps.toDouble() <= 10.1 && amps.toDouble() >= 0){
            QString amps = ui->te_ampssetting->toPlainText();
            pce->pCharger->setAMPS(amps.toDouble());
            ui->te_ampsresult->setHtml("<b><p align = 'center'>" + amps + "</p></b>");
            ui->te_ampssetting->clear();
        }

    }
}

void powersupply2::on_pb_decreasea_clicked()
{
    QString current = ui->te_ampsresult->toPlainText();

    if (current.toDouble() > 0){
        double New = (current.toDouble() - 0.1);
        ui->te_ampsresult->setStyleSheet("text-align: center;");
        ui->te_ampsresult->setHtml("<b><p align = 'center'>" + QString::number(New) + "</p></b>");

        if (config == 0) {
            //voltage = pce->pMotorSupply->getVDC() - .1;
            pce->pMotorSupply->setSTEPA(0.1);

            //pce->pMotorSupply->setVDC(voltage);
            pce->pMotorSupply->decreaseAMPS();
        }
        else {
            //voltage = pce->pMotorSupply->getVDC() - .1;
            pce->pCharger->setSTEPA(0.1);

            //pce->pMotorSupply->setVDC(voltage);
            pce->pCharger->decreaseAMPS();
        }
    }
}

void powersupply2::on_pb_increasea_clicked()
{
    QString current = ui->te_ampsresult->toPlainText();

    if (config == 0) {
        if (current.toDouble() < 25.1){
            double New = (current.toDouble() + 0.1);
            ui->te_ampsresult->setHtml("<b><p align = 'center'>" + QString::number(New) + "</p></b>");

            //voltage = pce->pMotorSupply->getVDC() + .1;
            pce->pMotorSupply->setSTEPA(0.1);

            //pc->->pMotorSupply->setVDC(voltage);
            pce->pMotorSupply->increaseAMPS();
        }
    }
    else {
        if (current.toDouble() < 10.1){
            double New = (current.toDouble() + 0.1);
            ui->te_ampsresult->setHtml("<b><p align = 'center'>" + QString::number(New) + "</p></b>");

            //voltage = pce->pMotorSupply->getVDC() + .1;
            pce->pCharger->setSTEPA(0.1);

            //pc->->pMotorSupply->setVDC(voltage);
            pce->pCharger->increaseAMPS();
        }
    }
}

void powersupply2::on_pb_config_clicked()
{
    //Switch to other config
    if (config == 0) {
        config = 1;
        ui->te_configdisplay->setHtml("<b><p align = 'center'>BK Precision 2901</p></b>");
        ui->pb_config->setText("Switch to 2905 Config");
        pce->pCharger->reset();
        ui->te_ampsresult->setHtml("<b><p align = 'center'>10.1</p></b>");
        ui->te_enablestatus->setHtml("<b><p align = 'center'>0</p></b>");

    }
    else {
        config = 0;
        ui->te_configdisplay->setHtml("<b><p align = 'center'>BK Precision 2905</p></b>");
        ui->pb_config->setText("Switch to 2901 Config");
        pce->pMotorSupply->reset();
        ui->te_ampsresult->setHtml("<b><p align = 'center'>25.1</p></b>");
        ui->te_enablestatus->setHtml("<b><p align = 'center'>0</p></b>");
    }
}

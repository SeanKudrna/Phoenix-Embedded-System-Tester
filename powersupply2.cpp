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
}

powersupply2::~powersupply2()
{
    delete ui;
}

void powersupply2::onTimer()
{
    pce->pMotorSupply->getADC();
    pce->pMotorSupply->getNextData(&result);
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

        //voltage = pce->pMotorSupply->getVDC() + .1;
        pce->pMotorSupply->setSTEP(0.1);

        //pc->->pMotorSupply->setVDC(voltage);
        pce->pMotorSupply->increaseVOLTS();
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


        //voltage = pce->pMotorSupply->getVDC() - .1;
        pce->pMotorSupply->setSTEP(0.1);

        //pce->pMotorSupply->setVDC(voltage);
        pce->pMotorSupply->decreaseVOLTS();
    }

}


void powersupply2::on_pb_voltageselect_clicked()
{
    //connect( ui->pb_voltageselect, SIGNAL(clicked()), this, SLOT(keyboardButtonPressed()) );
    QString voltage = ui->te_voltagesetting->toPlainText();
    if (voltage.toDouble() <= 61 && voltage.toDouble() >= 0){
        pce->pMotorSupply->setVOLTS(voltage.toDouble());
        //ui->te_enablestatus->setAlignment(Qt::AlignCenter);
        ui->te_enablestatus->setHtml("<b><p align = 'center'>" + voltage + "</p></b>");
        ui->te_voltagesetting->clear();
        //voltage.toDouble();
    }
}



void powersupply2::on_pb_remote_clicked()
{
    pce->pMotorSupply->clearErrors();
}

void powersupply2::on_cb_applyvoltage_stateChanged(int state)
{
    if (state == 0){
        ui->te_voltagestatus->setHtml("<b><p align = 'center'>OFF</p></b>");
        pce->pMotorSupply->triggerVOLTS(0);

    }//EOF Turn off voltage
    else{
        ui->te_voltagestatus->setHtml("<b><p align = 'center'>ON</p></b>");
        pce->pMotorSupply->triggerVOLTS(1);


    }//EOF Turn on voltage
}

void powersupply2::on_pb_ampsselect_clicked()
{
    QString amps = ui->te_ampssetting->toPlainText();
    if (amps.toDouble() <= 10.1 && amps.toDouble() >= 0){
        QString amps = ui->te_ampssetting->toPlainText();
        pce->pMotorSupply->setAMPS(amps.toDouble());
        ui->te_ampsresult->setHtml("<b><p align = 'center'>" + amps + "</p></b>");
        ui->te_ampssetting->clear();
    }
}

void powersupply2::on_pb_decreasea_clicked()
{
    QString current = ui->te_ampsresult->toPlainText();

    if (current.toDouble() > 0){
        double New = (current.toDouble() - 0.1);
        ui->te_ampsresult->setStyleSheet("text-align: center;");
        ui->te_ampsresult->setHtml("<b><p align = 'center'>" + QString::number(New) + "</p></b>");


        //voltage = pce->pMotorSupply->getVDC() - .1;
        pce->pMotorSupply->setSTEPA(0.1);

        //pce->pMotorSupply->setVDC(voltage);
        pce->pMotorSupply->decreaseAMPS();
    }
}

void powersupply2::on_pb_increasea_clicked()
{
    QString current = ui->te_ampsresult->toPlainText();
    if (current.toDouble() < 10.1){
        double New = (current.toDouble() + 0.1);
        ui->te_ampsresult->setHtml("<b><p align = 'center'>" + QString::number(New) + "</p></b>");

        //voltage = pce->pMotorSupply->getVDC() + .1;
        pce->pMotorSupply->setSTEPA(0.1);

        //pc->->pMotorSupply->setVDC(voltage);
        pce->pMotorSupply->increaseAMPS();
    }
}

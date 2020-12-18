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
}

powersupply2::~powersupply2()
{
    delete ui;
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
    double New = (current.toDouble() + 0.1);
    ui->te_enablestatus->setHtml("<b><p align = 'center'>" + QString::number(New) + "</p></b>");

    //voltage = pce->pMotorSupply->getVDC() + .1;
    pce->pMotorSupply->setSTEP(0.1);

    //pce->pMotorSupply->setVDC(voltage);
    pce->pMotorSupply->increaseVOLTS();
}


void powersupply2::on_pb_reset_clicked()
{
    pce->pMotorSupply->reset();
}

void powersupply2::on_pb_decreasev_clicked()
{
    QString current = ui->te_enablestatus->toPlainText();
    double New = (current.toDouble() - 0.1);
    ui->te_enablestatus->setStyleSheet("text-align: center;");
    ui->te_enablestatus->setHtml("<b><p align = 'center'>" + QString::number(New) + "</p></b>");

    //voltage = pce->pMotorSupply->getVDC() - .1;
    pce->pMotorSupply->setSTEP(0.1);

    //pce->pMotorSupply->setVDC(voltage);
    pce->pMotorSupply->decreaseVOLTS();

}


void powersupply2::on_pb_voltageselect_clicked()
{
    //connect( ui->pb_voltageselect, SIGNAL(clicked()), this, SLOT(keyboardButtonPressed()) );
    QString voltage = ui->te_voltagesetting->toPlainText();
    pce->pMotorSupply->setVOLTS(voltage.toDouble());
     //ui->te_enablestatus->setAlignment(Qt::AlignCenter);
    ui->te_enablestatus->setHtml("<b><p align = 'center'>" + voltage + "</p></b>");
    //voltage.toDouble();

}



void powersupply2::on_pb_remote_clicked()
{
    pce->pMotorSupply->clearErrors();
}

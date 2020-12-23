#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "capitalequipment.h"
#include "testmenu.h"
#include "popup.h"
#include <string>
#include <QMessageBox>

extern CapitalEquipment *pce;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    timer->start(1000);
    count = 0;
    getData = false;
    flag = false;


    countReading = 0;
    testIterations = 0;
}



MainWindow::~MainWindow()
{
    delete ui;
}



enum states{
    SS_VAC,
    SS_OHMS,
    SS_VDC,
    SS_READ,
    SS_ERROR,
    SS_COMPLETE
};
static states state;

bool MainWindow::stateMachine(void)
{
    bool callAgain = true;



    switch(state)
    {
        case SS_VAC:{
            pce->pMeter->setVAC();
            ui->te_result->append("...Testing Switch to VAC...");

            state = SS_OHMS;
            break;
        }

        case SS_OHMS:{
            pce->pMeter->setOHMS();
            ui->te_result->append("...Testing Switch to OHMS...");

            state = SS_VDC;
            break;
        }

        case SS_VDC:{
            pce->pMeter->setVDC();
            ui->te_result->append("...Testing Switch to VDC...");

            ui->te_result->append("\n...Now Reading voltage on VDC...");
            state = SS_READ;
            break;
        }

        case SS_READ:{

            pce->pMeter->measure();
            pce->pMeter->getNextData(&result);
            ui->te_result->append(result);

            //Count the reading only if result is not empty
            if (result != "")
                countReading++;

            if (countReading == 3)
            {
                testIterations++;
                ui->te_result->append("\nCompleted test iteration " + QString::number(testIterations) + "\n");
                countReading = 0;
                state = SS_VAC;
            }

            break;
        }

        case SS_ERROR:{
            break;
        }

        case SS_COMPLETE:{
            callAgain = false;
            break;
        }
    }//swtich

    return callAgain;
}



void MainWindow::onTimer()
{

    //Timer clock (right-hand box in ui)
    count++;
    ui->te_timer->append(QString::number(count));
    if (count <= 4 && pce->completed ==3)
    {
        ui->pb_statusbar->setValue((count*25 ));


        pce->pMeter->getId();
        pce->pMotorSupply->getId();
        pce->pCharger->getId();


    }

    if (count == 4 && pce->completed ==3)
    {
        QString MeterID;
        QString SupplyID;
        QString ChargerID;


        pce->pMeter->getNextData(&MeterID);
        pce->pMotorSupply->getNextData(&SupplyID);
        pce->pCharger->getNextData(&ChargerID);


        ui->lbl_status->hide();
        ui->pb_statusbar->hide();



        if (!pce->pMeter->equipmentValidation(MeterID)){
            popup *ppu = new popup();
            ppu->exec();
        }


         else if (!pce->pMotorSupply->equipmentValidation(SupplyID)){
            popup *ppu = new popup();
            ppu->exec();
        }

       else if(!pce->pCharger->equipmentValidation(ChargerID)){
            popup *ppu = new popup();
            ppu->exec();
        }


    }


    if (getData)
        stateMachine();
    else {
        if (flag)
            ui->te_result->append(" ");
    }

}

void MainWindow::on_pb_get_clicked()
{

    //If machine is running
    if (getData)
    {
        //Update text on button to say START
        ui->pb_get->setText("Start");

        if (!flag)
            flag = true;

        //Update state to false
        getData = false;
        //state = SS_COMPLETE;
    }

    //If machine is stopped
    else
    {
        //Update text on button to say STOP
        ui->pb_get->setText("Stop");

        //Update state to true
        getData = true;
        //state = SS_VAC;
    }

}

void MainWindow::on_rb_ac_clicked()
{    
   pce->pMeter->setVAC();
   ui->te_result->append("\n...Now Reading voltage on VAC...\n");
}

void MainWindow::on_rb_dc_clicked()
{
    pce->pMeter->setVDC();
    ui->te_result->append("\n...Now Reading voltage on VDC...\n");
}

void MainWindow::on_rb_ohms_clicked()
{
    pce->pMeter->setOHMS();
    ui->te_result->append("\n...Now Reading resistance in OHMS ...\n");
}

void MainWindow::on_pb_reset_clicked()
{
    pce->pMeter->reset();
    testIterations = 0;
}

void MainWindow::on_pb_clear_clicked()
{
    ui->te_result->clear();
    ui->te_timer->clear();
}

void MainWindow::on_pb_testm_clicked()
{
    testmenu *ptm = new testmenu();
    //ptm->exec();
    ptm->show();
    this->close();

    //delete ptm;
}


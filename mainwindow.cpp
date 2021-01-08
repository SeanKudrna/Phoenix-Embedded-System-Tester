#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "capitalequipment.h"
#include "testmenu.h"
#include "popup.h"
#include <string>
#include <QMessageBox>

//Get CapitalEquipment object
extern CapitalEquipment *pce;

//Constructor
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Setup timer, and link with onTimer() method
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    timer->start(1000);
    count = 0;
    getData = false;
    flag = false;

    //Set Default counts/bools
    countReading = 0;
    testIterations = 0;

    probeStatus = false;
    equStatus = 0;
    ui->pb_statusbar->setValue(0);
    ui->tb_verificationResult->hide();

}//EOF constructor

//Deconstructor
MainWindow::~MainWindow()
{
    delete ui;
}//EOF deconstructor

//Different testing states for DMM
enum states{
    SS_VAC,
    SS_OHMS,
    SS_VDC,
    SS_READ,
    SS_ERROR,
    SS_COMPLETE
};

//Instantiate one state
static states state;

//State machine (automated testing)
bool MainWindow::stateMachine(void)
{
    //Set run again to true
    bool callAgain = true;

    //Switch based on current state
    switch(state)
    {
        //If in VAC state, set meter to VAC and display a message then move on to next state
        case SS_VAC:{
            pce->pMeter->setVAC();
            ui->te_result->append("...Testing Switch to VAC...");

            state = SS_OHMS;
            break;
        }//EOF VAC

        //If in OHMS state, set meter to OHMS and display a message then move on to the next state
        case SS_OHMS:{
            pce->pMeter->setOHMS();
            ui->te_result->append("...Testing Switch to OHMS...");

            state = SS_VDC;
            break;
        }//EOF OHMS

        //If in VDC state, set meter to VDC and display a message then move on to the next state
        case SS_VDC:{
            pce->pMeter->setVDC();
            ui->te_result->append("...Testing Switch to VDC...");

            ui->te_result->append("\n...Now Reading voltage on VDC...");
            state = SS_READ;
            break;
        }//EOF VDC

        //If in READ state, complete 3 voltage measurments then loop back to the first state
        case SS_READ:{
            pce->pMeter->measure();
            pce->pMeter->getNextData(&result);
            ui->te_result->append(result);

            //Count the reading only if result is not empty
            if (result != "")
                countReading++;

            //If all three readings are completed
            if (countReading == 3)
            {
                //Add 1 to completed test count, display a message and reset countReading before continuing
                testIterations++;
                ui->te_result->append("\nCompleted test iteration " + QString::number(testIterations) + "\n");
                countReading = 0;
                state = SS_VAC;
            }//EOF if

            break;
        }//EOF READ

        //Error case, unused
        case SS_ERROR:{
            break;
        }//EOF ERROR

        //Complete state, unused
        case SS_COMPLETE:{
            callAgain = false;
            break;
        }//EOF COMPLETE
    }//EOF SWITCH

    return callAgain;
}//EOF StateMachine()

//onTimer executes every second
void MainWindow::onTimer()
{

    //Timer clock (right-hand box in ui)
    count++;
    ui->te_timer->append(QString::number(count));

    //Below is commented out when serial port detection is off
    /*
    //Get probe status
    probeStatus = pce->Probe->getStatus();
    equStatus = pce->getCompletedStatus();


    //If probe has finished, and objects have not been created, create them.
    //If create() is commented out, serial detection is disabled and
    //Equipment objects are created in capitalequipment constructor.
    if (probeStatus && equStatus == 0)
        //pce->create();
    */


    //While the clock is under 8 sec, and devices are constructed send IDN commands to devices.
    if (count < 8 /*&& equStatus == 3*/)
    {
        //Update status bar in UI
        ui->pb_statusbar->setValue((count*12.5));

        pce->pMeter->getId();
        pce->pMotorSupply->getId();
        pce->pCharger->getId();

    }//EOF if

    //Once clock hits 8 seconds, complete equipment validation.
    if (count == 8 /*&& equStatus == 3*/)
    {
        QString MeterID;
        QString SupplyID;
        QString ChargerID;

        //Retrieve ID information from IDN command
        pce->pMeter->getNextData(&MeterID);
        pce->pMotorSupply->getNextData(&SupplyID);
        pce->pCharger->getNextData(&ChargerID);

        ui->lbl_status->hide();
        ui->pb_statusbar->hide();


        //Hide status bar in UI
        ui->lbl_status->hide();
        ui->pb_statusbar->hide();

        //If meter was unable to be validated, display popup
        if (!pce->pMeter->equipmentValidation(MeterID)){
            popup *ppu = new popup();
            ppu->exec();
        }//EOF if

        //If motor supply was unable to be validated, display popup
       else if (!pce->pMotorSupply->equipmentValidation(SupplyID)){
            popup *ppu = new popup();
            ppu->exec();
        }//EOF else if

        //If charger was unable to be validated, display popup
       else if(!pce->pCharger->equipmentValidation(ChargerID)){
            popup *ppu = new popup();
            ppu->exec();
        }//EOF else if

       else{
            ui->tb_verificationResult->show();
        }
    }//EOF if

    //If START button is clicked, execute stateMachine() automated testing
    if (getData)
        stateMachine();

    //If STOP button is clicked, end stateMachine() automated testing
    else {
        if (flag)
            ui->te_result->append(" ");
    }//EOF else
}//EOF onTimer()

//Logic behind automated testing button
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
    }//EOF if

    //If machine is stopped
    else
    {
        //Update text on button to say STOP
        ui->pb_get->setText("Stop");
        ui->tb_verificationResult->hide();


        //Update state to true
        getData = true;
        //state = SS_VAC;
    }//EOF else

}//EOF test

//Set meter to VAC and display
void MainWindow::on_rb_ac_clicked()
{    
   pce->pMeter->setVAC();
   ui->te_result->append("\n...Now Reading voltage on VAC...\n");
}//EOF VAC

//Set meter to VDC and display
void MainWindow::on_rb_dc_clicked()
{
    pce->pMeter->setVDC();
    ui->te_result->append("\n...Now Reading voltage on VDC...\n");
}//EOF VDC

//Set meter to OHMS and display
void MainWindow::on_rb_ohms_clicked()
{
    pce->pMeter->setOHMS();
    ui->te_result->append("\n...Now Reading resistance in OHMS ...\n");
}//EOF OHMS

//Reset meter and completed tests counter
void MainWindow::on_pb_reset_clicked()
{
    pce->pMeter->reset();
    testIterations = 0;
}//EOF reset

//Clear UI result boxes
void MainWindow::on_pb_clear_clicked()
{
    ui->te_result->clear();
    ui->te_timer->clear();
}//EOF clear

//Open new test menu
void MainWindow::on_pb_testm_clicked()
{
    testmenu *ptm = new testmenu();
    ptm->show();
    this->close();
}//EOF test menu


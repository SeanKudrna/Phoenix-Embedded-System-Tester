#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "capitalequipment.h"
#include "testmenue.h"
extern CapitalEquipment *pce;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_get_clicked()
{
    QString result;
    pce->pMeter->measure();
    pce->pMeter->getNextData(&result);

    ui->te_result->clear();
    ui->te_result->append(result);

}

void MainWindow::on_rb_ac_clicked()
{
   pce->pMeter->setVAC();
}

void MainWindow::on_rb_dc_clicked()
{
    pce->pMeter->setVDC();
}

void MainWindow::on_rb_ohms_clicked()
{
    pce->pMeter->setOHMS();
}

void MainWindow::on_pb_reset_clicked()
{
    pce->pMeter->reset();
}

void MainWindow::on_pb_clear_clicked()
{
    ui->te_result->clear();
}

void MainWindow::on_pb_testm_clicked()
{
    testmenue w;
    w.show;
}

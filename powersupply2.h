#ifndef POWERSUPPLY2_H
#define POWERSUPPLY2_H

#include <QDialog>

namespace Ui {
class powersupply2;
}

class powersupply2 : public QDialog
{
    Q_OBJECT

public:
    explicit powersupply2(QWidget *parent = nullptr);
    ~powersupply2();

private slots:
    void on_pb_testmenu_clicked();

    void on_pb_increasev_clicked();

    void on_pb_reset_clicked();

    void on_pb_decreasev_clicked();

    void on_pb_voltageselect_clicked();

    void on_pb_remote_clicked();

    void on_cb_applyvoltage_stateChanged(int arg1);

    void on_pb_ampsselect_clicked();

    void onTimer();

    void on_pb_decreasea_clicked();

    void on_pb_increasea_clicked();

    void on_pb_config_clicked();

private:
    Ui::powersupply2 *ui;
    double voltage;
    QTimer *timer;
    bool flag;
    QString result;
    int config;
};

#endif // POWERSUPPLY2_H

#ifndef TESTMENU_H
#define TESTMENU_H

#include <QDialog>

namespace Ui {
class testmenu;
}

class testmenu : public QDialog
{
    Q_OBJECT

public:
    explicit testmenu(QWidget *parent = nullptr);
    ~testmenu();

private slots:
    void on_pb_dmm_clicked();

    void on_pb_powersupply_clicked();

    void on_pb_relaydriver_clicked();

    void on_pb_dac_clicked();

private:
    Ui::testmenu *ui;
};

#endif // TESTMENU_H

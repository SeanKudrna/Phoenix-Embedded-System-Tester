#ifndef DACTEST_H
#define DACTEST_H

#include <QDialog>

namespace Ui {
class dactest;
}

class dactest : public QDialog
{
    Q_OBJECT

public:
    explicit dactest(QWidget *parent = nullptr);
    ~dactest();

private slots:
    void on_pb_testmenu_clicked();

    void on_pb_dac1_clicked();

    void on_pb_dac2_clicked();

    void on_pb_dac2_2_clicked();

    void on_pb_dac3_clicked();

private:
    Ui::dactest *ui;
};

#endif // DACTEST_H

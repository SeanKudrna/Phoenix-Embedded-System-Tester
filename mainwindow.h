#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QTimer>
#include "QDebug"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_get_clicked();
    void on_rb_ac_clicked();
    void on_rb_dc_clicked();
    void on_rb_ohms_clicked();
    void on_pb_reset_clicked();
    void on_pb_clear_clicked();
    void onTimer();
    void on_pb_testm_clicked();
    bool stateMachine();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QString result;
    long count;
    int countReading;
    bool getData;
    bool flag;
    int testIterations;
};

#endif // MAINWINDOW_H

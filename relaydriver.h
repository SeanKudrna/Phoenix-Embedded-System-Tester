#ifndef RELAYDRIVER_H
#define RELAYDRIVER_H

#include <QDialog>

namespace Ui {
class relaydriver;
}

class relaydriver : public QDialog
{
    Q_OBJECT

public:
    explicit relaydriver(QWidget *parent = nullptr);
    ~relaydriver();

private slots:
    void on_pb_testmenu_clicked();

private:
    Ui::relaydriver *ui;
};

#endif // RELAYDRIVER_H

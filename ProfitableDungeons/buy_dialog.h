#ifndef BUY_DIALOG_H
#define BUY_DIALOG_H

#include <QDialog>
#include <QString>
#include "building.h"

namespace Ui {
class BuyDialog;
}

class BuyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BuyDialog(QWidget *parent,
                       Building *building,
                       bool selling);
    ~BuyDialog();
    bool accepted_buying = false;

private slots:
    void on_button_box_accepted();
    void on_button_box_rejected();

private:
    Ui::BuyDialog *ui;
};

#endif // BUY_DIALOG_H

#ifndef BUY_DIALOG_H
#define BUY_DIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class BuyDialog;
}

class BuyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BuyDialog(QWidget *parent = nullptr,
                       QString building_name = QString(""),
                       int gold_price = 0);
    ~BuyDialog();
    bool accepted_buying = false;

private slots:
    void on_button_box_accepted();

    void on_button_box_rejected();

private:
    Ui::BuyDialog *ui;
};

#endif // BUY_DIALOG_H

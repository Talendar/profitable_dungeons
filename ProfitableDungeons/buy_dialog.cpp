#include "buy_dialog.h"
#include "ui_buy_dialog.h"

BuyDialog::BuyDialog(QWidget *parent, QString building_name, int gold_price) :
    QDialog(parent),
    ui(new Ui::BuyDialog)
{
    ui->setupUi(this);
    ui->title->setText("< " + building_name + " >");
    ui->text->setText(
        QString("<html><head/><body><p>Do you want to build a ") + \
        "<span style=' font-weight:600;'>" + building_name + "</span>"
        " for <span style=' font-weight:600; color:#edd400;'>" + \
        QString::number(gold_price) + " gold</span>?</p></body></html>");
}

BuyDialog::~BuyDialog() {
    delete ui;
}

void BuyDialog::on_button_box_accepted() {
    this->accepted_buying = true;
}

void BuyDialog::on_button_box_rejected() {}

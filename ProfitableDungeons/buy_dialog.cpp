#include "buy_dialog.h"
#include "ui_buy_dialog.h"

BuyDialog::BuyDialog(QWidget *parent, Building *building, bool selling) :
    QDialog(parent),
    ui(new Ui::BuyDialog)
{
    ui->setupUi(this);
    ui->building_name->setText(building->getName());
    ui->building_img->setPixmap(building->getBuiltImg());

    QString op(selling ? "SELL" : "UPGRADE");
    this->setWindowTitle(op);

    ui->text->setText(
        QString("<html><head/><body><p>Do you want to %1 the ").arg(op) + \
        "<span style=' font-weight:600;'>" + building->getName() + "</span>"
        " for <span style=' font-weight:600; color:#edd400;'>" + \
        QString::number(selling ? building->getSellCost() : building->getCost()) + \
        " gold</span>?</p></body></html>");
}

BuyDialog::~BuyDialog() {
    delete ui;
}

void BuyDialog::on_button_box_accepted() {
    this->accepted_buying = true;
}

void BuyDialog::on_button_box_rejected() {}

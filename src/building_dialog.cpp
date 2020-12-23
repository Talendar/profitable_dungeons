#include "building_dialog.h"
#include "ui_building_dialog.h"


/**
 * Constructor.
 */
BuildingDialog::BuildingDialog(QWidget *parent, Building *building) :
    QDialog(parent),
    ui(new Ui::BuildingDialog)
{
    ui->setupUi(this);
    setFixedSize(size());

    ui->building_name->setText(building->getName());
    ui->tier->setText(QString("(lv %1)").arg(building->getTier()));

    ui->building_img->setPixmap(building->getBuiltImg());
    this->setWindowTitle(building->getName());

    ui->gold_per_tick->setText(QString::number(building->getGPT()));
    ui->upgrade_cost->setText(QString::number(building->getCost()));
    ui->selling_cost->setText(QString::number(building->getSellCost()));
    ui->tick_interval->setText(QString("").sprintf("%.2f s", building->getTickInterval() / 1000.0));

    if(building->getTier() == 0) {
        ui->upgrade_button->setText("Buy");
        ui->sell_button->setVisible(false);
    }
}


/**
 * Destructor.
 */
BuildingDialog::~BuildingDialog() {
    delete ui;
}


/**
 * Returns the current state of the dialog.
 */
BuildingDialog::State BuildingDialog::getState() {
    return this->state;
}


/**
 * Called when the dialog "Back" button is clicked.
 */
void BuildingDialog::on_back_button_clicked() {
    this->state = State::NO_ACTION;
    this->close();
}


/**
 * Called when the dialog "Sell" button is clicked.
 */
void BuildingDialog::on_sell_button_clicked() {
    this->state = State::SELL;
    this->close();
}


/**
 * Called when the dialog "Upgrade" button is clicked.
 */
void BuildingDialog::on_upgrade_button_clicked() {
    this->state = State::UPGRADE;
    this->close();
}

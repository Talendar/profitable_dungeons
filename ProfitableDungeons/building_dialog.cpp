#include "building_dialog.h"
#include "ui_building_dialog.h"


/**
 * Constructor.
 */
BuildingDialog::BuildingDialog(QWidget *parent, QString name) :
    QDialog(parent),
    ui(new Ui::BuildingDialog)
{
    ui->setupUi(this);
    setFixedSize(size());
    ui->building_name->setText("< " + name + " >");
    this->setWindowTitle(name);
}


/**
 * Destructor.
 */
BuildingDialog::~BuildingDialog() {
    delete ui;
}

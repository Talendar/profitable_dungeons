#include "tavern_dialog.h"
#include "ui_tavern_dialog.h"


TavernDialog::TavernDialog(QWidget *parent, QLabel *gold_label) :
    QDialog(parent),
    ui(new Ui::TavernDialog)
{
    ui->setupUi(this);
    setFixedSize(size());
    this->gold_label = gold_label;
}


TavernDialog::~TavernDialog() {
    delete ui;
}


void TavernDialog::on_pushButton_clicked() {
    gold_label->setText("<html><head/><body><p><span style='font-size:12pt; color:#edd400;'>Gold: 99999</span></p></body></html>");
    gold_label->update();
}

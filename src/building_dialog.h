#ifndef BUILDING_DIALOG_H
#define BUILDING_DIALOG_H

#include <QDialog>
#include <QtWidgets>
#include "building.h"

namespace Ui {
class BuildingDialog;
}

class BuildingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BuildingDialog(QWidget *parent,
                            Building *building);
    ~BuildingDialog();

    enum class State {NO_ACTION, UPGRADE, SELL};
    State getState();

private slots:
    void on_back_button_clicked();
    void on_sell_button_clicked();
    void on_upgrade_button_clicked();

private:
    Ui::BuildingDialog *ui;
    State state = State::NO_ACTION;
};

#endif // BUILDING_DIALOG_H

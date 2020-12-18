#ifndef BUILDING_DIALOG_H
#define BUILDING_DIALOG_H

#include <QDialog>
#include <QtWidgets>

namespace Ui {
class BuildingDialog;
}

class BuildingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BuildingDialog(QWidget *parent = nullptr,
                            QString name = QString(""));
    ~BuildingDialog();

private:
    Ui::BuildingDialog *ui;
};

#endif // BUILDING_DIALOG_H

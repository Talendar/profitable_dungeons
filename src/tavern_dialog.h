#ifndef TAVERN_DIALOG_H
#define TAVERN_DIALOG_H

#include <QDialog>
#include <QDebug>
#include <QtWidgets>

namespace Ui {
class TavernDialog;
}

class TavernDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TavernDialog(QWidget *parent = nullptr, QLabel *gold_label = nullptr);
    ~TavernDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::TavernDialog *ui;
    QLabel *gold_label;
};

#endif // TAVERN_DIALOG_H

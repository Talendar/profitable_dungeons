#ifndef INITIAL_WINDOW_H
#define INITIAL_WINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include<game_window.h>

namespace Ui {
class InitialWindow;
}

class InitialWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit InitialWindow(QWidget *parent = nullptr);
    ~InitialWindow();

private slots:
    void on_quit_btn_clicked();

    void on_new_game_btn_clicked();

    void on_load_game_btn_clicked();

private:
    Ui::InitialWindow *ui;
};

#endif // INITIAL_WINDOW_H

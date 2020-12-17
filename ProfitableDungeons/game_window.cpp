#include "game_window.h"
#include "ui_game_window.h"


/**
 * Constructor.
 */
GameWindow::GameWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    setFixedSize(size());

    // centering the window
    QRect desktopRect = QApplication::desktop()->availableGeometry(this);
    QPoint center = desktopRect.center();
    move(center.x() - width() * 0.5, center.y() - height() * 0.5);
}


/**
 * Destructor.
 */
GameWindow::~GameWindow() {
    delete ui;
}


/**
 * Tavern.
 */
void GameWindow::on_tavern_clicked() {
    TavernDialog *dialog = new TavernDialog(nullptr, this->ui->gold_label);
    dialog->show();
}

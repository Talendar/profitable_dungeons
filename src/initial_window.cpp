#include "initial_window.h"
#include "ui_initial_window.h"


InitialWindow::InitialWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::InitialWindow)
{
    ui->setupUi(this);
    setFixedSize(size());

    // centering the window
    QRect desktopRect = QApplication::desktop()->availableGeometry(this);
    QPoint center = desktopRect.center();
    move(center.x() - width() * 0.5, center.y() - height() * 0.5);
}


InitialWindow::~InitialWindow() {
    delete ui;
}


// NEW GAME BTN
void InitialWindow::on_new_game_btn_clicked()
{
    GameWindow *window = new GameWindow;
    window->show();
    this->close();
}


// LOAD GAME BTN
void InitialWindow::on_load_game_btn_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this,
           tr("Saved Game File"), "./saved_games",
           tr("Profitable Dungeons Saved Game (*.pd)"));

    if(fileName != nullptr) {
        GameWindow *window = new GameWindow(nullptr, fileName);
        window->show();
        this->close();
    }
}


// QUIT BTN
void InitialWindow::on_quit_btn_clicked() {
    QCoreApplication::exit();
}

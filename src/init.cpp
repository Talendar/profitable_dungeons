#include <QApplication>
#include <initial_window.h>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    InitialWindow *window = new InitialWindow;

    window->show();
    return app.exec();
}

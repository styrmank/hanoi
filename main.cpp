#include "mainwindow.hh"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    bool startGame = true;
    MainWindow w(startGame);
    if(startGame)
    {
        w.show();
        return a.exec();
    }
    return 0;
}

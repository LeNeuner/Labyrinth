#include "labymainwindow.h"
#include <QApplication>

#include "globals.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("fusion");

    LabyMainWindow w;
    w.setWindowTitle("Labyrinth 1.0");
    w.setWindowIcon(QIcon(":AppIcon"));
    w.setMinimumWidth(APP_WIDTH);
    w.setMinimumHeight(APP_HEIGHT);
    w.show();

    return a.exec();
}

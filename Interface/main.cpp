#include <QApplication>
#include <QtWidgets>
#include "interface.h"
#include <iostream>

int main(int argc, char * argv[]) {
    QApplication app(argc,argv);

    Interface fenetre;
    fenetre.showMaximized();

    return app.exec();
}

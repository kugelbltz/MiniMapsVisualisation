#include <QApplication>
#include <QtWidgets>
#include "interface.h"

int main(int argc, char * argv[]) {
    QApplication app(argc,argv);

    Interface fenetre;
    fenetre.show();

    return app.exec();
}

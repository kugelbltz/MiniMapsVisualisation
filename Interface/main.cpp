#include <QApplication>
#include <QtWidgets>
#include "interface.h"
#include <iostream>


int main(int argc, char * argv[]) {

    QApplication app(argc,argv);

    // SET STYLESHEET
    QFile stylesheetFile(":/Stylesheets/Ressources/stylesheet.txt");
    stylesheetFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&stylesheetFile);
    QString stylesheet = in.readAll();
    qApp->setStyleSheet(stylesheet);

    Interface fenetre;
    fenetre.showMaximized();

    return app.exec();
}

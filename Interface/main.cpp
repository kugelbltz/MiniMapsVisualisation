#include <QApplication>
#include <QtWidgets>
#include "interface.h"
#include <iostream>

#include <QSplashScreen>
#include <QPixmap>

int main(int argc, char * argv[]) {

    QApplication app(argc,argv);

    // SET STYLESHEET
    QFile stylesheetFile(":/Stylesheets/interfaceStylesheet.txt");
    stylesheetFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&stylesheetFile);
    QString stylesheet = in.readAll();
    qApp->setStyleSheet(stylesheet);


    QSplashScreen splash(QPixmap(":/Images/splash.png"));
    splash.show();
    splash.showMessage("Wait a minute... or five",Qt::AlignHCenter|Qt::AlignBottom, Qt::black);
    Interface fenetre;




    fenetre.showMaximized();
    splash.finish(&fenetre);

    return app.exec();
}

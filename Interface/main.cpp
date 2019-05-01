#include <QApplication>
#include <QtWidgets>
#include "interface.h"
#include <iostream>

#include <stdio.h>
#include <list>
#include <iterator>
#include <tuple>
#include <vector>
#include <map>
#include <climits>
#include <fstream>
#include <cmath>
#include <ctime>
#include <sstream>
#include <chrono>


#include "AlgoSources/Position.h"
#include "AlgoSources/Label.h"
#include "AlgoSources/Cost.h"
#include "AlgoSources/Arc.h"
#include "AlgoSources/Node.h"
#include "AlgoSources/Graph.h"
#include "AlgoSources/functions.h"
#include "AlgoSources/Json.h"


int main(int argc, char * argv[]) {

    QApplication app(argc,argv);

    // SET STYLESHEET
    QFile stylesheetFile(":/Stylesheets/interfaceStylesheet.txt");
    stylesheetFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&stylesheetFile);
    QString stylesheet = in.readAll();
    qApp->setStyleSheet(stylesheet);

    Interface fenetre;
    fenetre.showMaximized();

    return app.exec();
}

#include <QApplication>
#include <QtWidgets>
#include "interface.h"
#include <iostream>

#include <QSplashScreen>
#include <QPixmap>
#include <QFileDialog>

int main(int argc, char * argv[]) {

    QApplication app(argc,argv);

    // STATIC OR DYNAMIC MODE
    QMessageBox::StandardButton staticMode;
    staticMode = QMessageBox::question(nullptr, "Choose a launch mode", "Do you want to launch static mode ?", QMessageBox::Yes|QMessageBox::No);


    // CHOOSE DATA FOLDER
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::DirectoryOnly);
    QString dirName = dialog.getExistingDirectory();

    QStringList dataDirFiles = QDir(dirName).entryList();
    QStringList requiredFiles;

    if (staticMode == QMessageBox::Yes) {
        requiredFiles = QStringList("output.json");
    } else {
        requiredFiles = QStringList({"nodes.co", "graphWalk.cr", "transports0.txt"});
    }


    QStringList missingFiles;
    for (int i = 0; i < requiredFiles.size(); ++i) {
        if (!dataDirFiles.contains(requiredFiles.at(i)))
            missingFiles.push_back(requiredFiles.at(i));
    }

    if (!missingFiles.isEmpty()) {
        QMessageBox::critical(nullptr, "Some files are missing", "Make those files are in the data folder :\n\t- " + missingFiles.join("\n\t- "));
        return 0;
    }


    QSplashScreen splash(QPixmap(":/Images/splash.png"));
    splash.show();


    // SET STYLESHEET
    QFile stylesheetFile(":/Stylesheets/interfaceStylesheet.txt");
    stylesheetFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&stylesheetFile);
    QString stylesheet = in.readAll();
    qApp->setStyleSheet(stylesheet);

    splash.showMessage("Building the interface. Wait a minute... or five",Qt::AlignHCenter|Qt::AlignBottom, Qt::black);

    bool isInStaticMode = (staticMode == QMessageBox::Yes);
    Interface fenetre(dirName, isInStaticMode);


    fenetre.showMaximized();
    splash.finish(&fenetre);


    return app.exec();
}



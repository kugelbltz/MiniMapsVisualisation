#include "interface.h"
#include "ui_interface.h"
#include <QGraphicsPixmapItem>
#include <iostream>
#include "itineraire.h"
#include <QDir>
#include "carte.h"
#include <QQuickView>
#include <QMetaObject>
#include <QVariant>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QQmlEngine>
#include <QQmlContext>
#include <QQuickItem>
#include <QHash>

using namespace std;

Interface::Interface(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Interface)
{
    ui->setupUi(this);

    ui->testMap->setSource(QUrl::fromLocalFile("../Interface/map.qml"));
    QObject * object = ui->testMap->rootObject();
    QObject::connect(object, SIGNAL(mapPressed(QVariant, QVariant)), this, SLOT(mouseCoordinates(QVariant, QVariant)));



    /* LEAVE AT */
    ui->depTimeEdit->setTime(QTime::currentTime());

    ui->centralwidget->setStyleSheet("QLineEdit {border: 2px solid white;"
                                     "border-radius: 10px;"
                                     "padding: 0 8px;"
                                     "background-color: white}"

                                     "QPushButton#search, QPushButton#swap {border: 2px solid #FFA543;"
                                     "border-radius: 5px;"
                                     "font: 14pt Abel;"
                                     "background-color: #FFA543;"
                                     "color: white}"

                                     "QLabel#start, QLabel#end, QLabel#criterias {font: 14pt Abel}"

                                     "QLabel#depTime, QGroupBox#options, QGroupBox#privTrans {font: 11pt Abel}"
                                     );
}

Interface::~Interface()
{
    delete ui;
}


void Interface::addItineraries() {
    // Enlever les itineraires
    // il faut enlever les fichiers itineraires aussi !!!
    //deconnexion du signal aussi !
    for (int i(0); i < m_itineraires.length(); i++) {
        ui->itineraryLayout->removeWidget(m_itineraires.at(i));
        delete m_itineraires.at(i);
    }
    m_itineraires.clear();

    // Recuperer les entrées et sorties
    QString start = ui->startEdit->text();
    QString end = ui->endEdit->text();

    // Les envoyer au calculateur d'itinéraire et récuperer le nombre d'itinéraires
    // generayion des fichiers itineraires

    /* ENVOIE DES DONNEES */

    bool price = ui->price->isChecked();
    bool connections = ui->connections->isChecked();
    bool co2 = ui->co2->isChecked();
    bool effort = ui->effort->isChecked();
    int startNode = 5;
    int endNode = 12;
    QString startTime = ui->depTimeEdit->time().toString("HH:mm");
    QString mode;

    if (ui->walking->isChecked())
        mode = "walk";
    else if (ui->bike->isChecked())
        mode = "bike";
    else
        mode = "car";


    QJsonObject data {
        {"criterias", QJsonObject {
                {"price", price},
                {"connections", connections},
                {"co2", co2},
                {"effort", effort}
            }
        },
        {"start", startNode},
        {"dest", endNode},
        {"startTime", startTime},
        {"mode", mode}
    };

    qDebug() << data;

    int n(3);
    //int n = algo(data)


    for (int i(1); i <= n; i++) {
        QString filename = QDir::currentPath() + "/../TextFiles/path_" + QString::number(i) + ".txt";
        m_itineraires.push_back(new Itineraire(filename));
    }

    for (int i(0); i < n; i++) {
        connect(m_itineraires.at(i), SIGNAL(showMoreInfo(QJsonArray, QStringList, Itineraire *)), this, SLOT(displayItinerary(QJsonArray, QStringList, Itineraire *)));
    }

    // C'est là qu'on fait appelle a la partie algo.


    ui->techArea->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    for (int i(0); i < n ; i++) {
        ui->techLayout->insertWidget(i,m_itineraires.at(i));
    }
}

void Interface::on_swap_clicked() {
    QString temp = ui->startEdit->text();
    ui->startEdit->setText(ui->endEdit->text());
    ui->endEdit->setText(temp);
}

void Interface::on_search_clicked() {
    if (!ui->endEdit->text().isEmpty()&&!ui->startEdit->text().isEmpty())
        addItineraries();
}

void Interface::displayItinerary(QJsonArray paths, QStringList colors, Itineraire * itinerary) {

    for (int i(0); i < m_itineraires.length(); i++) {
        if (itinerary != m_itineraires.at(i)) {
            m_itineraires.at(i)->hideMoreInfo();
        }
    }


    QVariant returnedValue;
    QObject * object = ui->testMap->rootObject()->findChild<QObject*>("mapObject");
    QMetaObject::invokeMethod(object, "deleteRoute", Q_RETURN_ARG(QVariant, returnedValue));

    for (int i(0); i < paths.size(); i++) {
        QVariant path = paths.at(i);
        QVariant color = colors.at(i);
        QMetaObject::invokeMethod(object, "loadSection",
                                  Q_RETURN_ARG(QVariant, returnedValue),
                                  Q_ARG(QVariant, color),
                                  Q_ARG(QVariant, path));
    }
}

void Interface::mouseCoordinates(QVariant lat, QVariant lon) {
    bool s = ui->startEdit->text().isEmpty();
    bool e = ui->endEdit->text().isEmpty();

    if (s) {
        ui->startEdit->setText(lat.toString() + ", " + lon.toString());
    } else if (!s&&!e){
        ui->startEdit->setText(lat.toString() + ", " + lon.toString());
        ui->endEdit->setText("");
    }
    else {
        ui->endEdit->setText(lat.toString() + ", " + lon.toString());
    }
}

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


    //TEST

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
    int n(1);
    // int n = algo(end, start)


    for (int i(1); i <= n; i++) {
        QString filename = QDir::currentPath() + "/../TextFiles/path_" + QString::number(i) + ".txt";
        m_itineraires.push_back(new Itineraire(filename));
    }

    for (int i(0); i < n; i++) {
        connect(m_itineraires.at(i), SIGNAL(moreInfoClicked(QJsonArray, QStringList)), this, SLOT(displayItinerary(QJsonArray, QStringList)));
    }

    // C'est là qu'on fait appelle a la partie algo.

    for (int i(0); i < n ; i++) {
        ui->itineraryLayout->insertWidget(i+1, m_itineraires.at(i));
    }
}

void Interface::on_swap_clicked() {
    QString temp = ui->startEdit->text();
    ui->startEdit->setText(ui->endEdit->text());
    ui->endEdit->setText(temp);
}

void Interface::on_search_clicked() {
    addItineraries();
}

void Interface::displayItinerary(QJsonArray paths, QStringList colors) {
    QVariant returnedValue;
    QObject * object = ui->testMap->rootObject()->findChild<QObject*>("mapObject");

    for (int i(0); i < paths.size(); i++) {
        QVariant path = paths.at(i);
        QVariant color = colors.at(i);
        //QVariant color = m_transportColor[(i%2 == 0) ? "tram" : "walking"]; // c'est juste pour tester
        // il faudra un atre tableau ou il y aura la couleur ou le type de transport
        QMetaObject::invokeMethod(object, "loadSection",
                                  Q_RETURN_ARG(QVariant, returnedValue),
                                  Q_ARG(QVariant, color),
                                  Q_ARG(QVariant, path));

    }
}

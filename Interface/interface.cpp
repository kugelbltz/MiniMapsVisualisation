#include "interface.h"
#include "ui_interface.h"
#include <QGraphicsPixmapItem>
#include <iostream>
#include "itineraire.h"
#include <QDir>
#include "carte.h"
#include <QQuickView>

using namespace std;

Interface::Interface(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Interface)
{
    ui->setupUi(this);

    /* CARTE : NAVIGATION ET MISE EN PLACE */

    //m_carte = new Carte(this);
    //ui->horizontalLayout->addWidget(m_carte);

    //QQuickWidget * view = new QQuickWidget;
    ui->testMap->setSource(QUrl::fromLocalFile("../Interface/map.qml"));
}

Interface::~Interface()
{
    delete ui;
}

void Interface::addItineraries() {
    for (int i(0); i < m_itineraires.length(); i++) {
        ui->itineraryLayout->removeWidget(m_itineraires.at(i));
        delete m_itineraires.at(i);
    }
    m_itineraires.clear();
    // Ca marche pas tres bien il faut enlever les itineraires précédents
    getItineraires(0,0,0,0);

    // C'est là qu'on fait appelle a la partie algo.

    for (int i(0); i < m_itineraires.length(); i++) {
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

void Interface::getItineraires(qreal startLat, qreal startLon, qreal endLat, qreal endLon) {
    m_itineraires.push_back(new Itineraire("15h30 : Chatelet\nM >> Ligne 1 direction Reims\n16h : Marne la Vallée\n:) >> Marcher 30 min\n16h30 : DisneyLand Paris\nB >> Bus 45 direction Magny-le-Hongre Ciale\n...", this));
    m_itineraires.push_back(new Itineraire("15h30 : Chatelet\nM >> Ligne 1 direction Reims\n16h : Marne la Vallée\n:) >> Marcher 30 min\n16h30 : DisneyLand Paris\nB >> Bus 45 direction Magny-le-Hongre Ciale\n...", this));
}

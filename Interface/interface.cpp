#include "interface.h"
#include "ui_interface.h"
#include <QGraphicsPixmapItem>
#include <iostream>
#include <fstream>
#include "itineraire.h"
#include <QDir>
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
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QEventLoop>
#include <QProcess>
#include <map>
#include <QDebug>
#include <QMap>

#include "AlgoSources/functions.h"
#include "AlgoSources/Network.h"


using namespace std;

Interface::Interface(QString dataDir, bool isStatic, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Interface),
    m_network(dataDir.toStdString() + "/transports.txt", dataDir.toStdString() + "/footpaths.txt"),
    m_isStatic(isStatic),
    m_dataDir(dataDir)
{
    ui->setupUi(this);

    ui->testMap->setSource(QUrl("qrc:/Qml/map.qml"));
    QObject * object = ui->testMap->rootObject();
    QObject::connect(object, SIGNAL(mapPressed(QVariant, QVariant)), this, SLOT(displayMouseCoordinates(QVariant, QVariant)));

    /* LEAVE AT */
    ui->depTimeEdit->setTime(QTime::currentTime());

    ui->sortBy->hide();
    ui->progressBar->hide();

    /* MESSAGE */
    ui->status->setText("Click on the map to select beginning and end point");

    /* ALGO */
    QString graph_file(dataDir + "/graphWalk.cr");
    QString nodes_file(dataDir + "/nodes.co");

    if (!m_isStatic) {
        init_graph_complete(m_graph, m_nodes, graph_file.toStdString(), nodes_file.toStdString());
    }


}

Interface::~Interface()
{
    delete ui;
}


void Interface::clearItineraryList() {
    for (int i(0); i < m_itineraires.length(); i++) {
        ui->itineraryLayout->removeWidget(m_itineraires.at(i));
        disconnect(m_itineraires.at(i), SIGNAL(showMoreInfo(QJsonArray, QStringList, QList<bool>,Itineraire *)),
                   this, SLOT(displayItinerary(QJsonArray, QStringList, QList<bool>, Itineraire *)));
        delete m_itineraires.at(i);
    }
    m_itineraires.clear();
}

QJsonObject Interface::getItineraryData() {
    ui->progressBar->setValue(20);
    ui->status->setText("Generating algorithm input");

    ui->progressBar->setValue(40);
    ui->status->setText("Calculating itineraries");

    m_input = generateAlgorithmInput();

    qint64 start_node = qint64(m_input["start"].toDouble());
    qint64 end_node = qint64(m_input["dest"].toDouble());
    qreal start_time = qreal(m_input["startTime"].toDouble());

    QJsonObject criteriaObj = m_input["criteria"].toObject();
    map<string,bool> criteria;

    criteria["price"] = criteriaObj["price"].toBool();
    criteria["connections"] = criteriaObj["connections"].toBool();
    criteria["co2"] = criteriaObj["co2"].toBool();
    criteria["effort"] = criteriaObj["effort"].toBool();
    criteria["height"] = criteriaObj["height"].toBool();

    QString result = QString::fromStdString(fusion(m_graph, m_nodes, m_network, start_node, end_node, start_time, criteria));

    QJsonDocument doc = QJsonDocument::fromJson(result.toUtf8());
    QJsonObject itineraryData = doc.object();

    return itineraryData;


}

void Interface::setItineraryList(QJsonObject itineraryData) {

    QJsonArray itineraries = itineraryData["itineraries"].toArray();

    int n = itineraryData["nb_itineraries"].toInt();


    for (int i(0); i < n; i++) {
        QJsonObject itinerary = itineraries[i].toObject();
        m_itineraires.push_back(new Itineraire(itinerary));
        connect(m_itineraires.at(i), SIGNAL(showMoreInfo(QJsonArray, QStringList, QList<bool>, Itineraire *)), this, SLOT(displayItinerary(QJsonArray, QStringList, QList<bool>,Itineraire *)));
    }
}

void Interface::displayItineraryList() {
    ui->techArea->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    for (int i(0); i < m_itineraires.length() ; i++) {
        ui->techLayout->insertWidget(i,m_itineraires.at(i));
    }
}

void Interface::hideItineraryList() {
    for (int i(0); i < m_itineraires.length() ; i++) {
        ui->techLayout->removeWidget(m_itineraires.at(i));
    }
}

void Interface::on_search_clicked() {
    if (!m_isStatic && (ui->endEdit->text().isEmpty() || ui->startEdit->text().isEmpty()))
        return;

    ui->search->setDisabled(true);

    ui->status->show();
    ui->progressBar->show();
    ui->sortBy->hide();

    ui->status->setText("Clearing previous list");
    ui->progressBar->setValue(0);

    clearItineraryList();

    QJsonObject itineraryData;

    if (m_isStatic) {

        QFile outputFile(m_dataDir + "/output.json");
        if (outputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {

            QString result = outputFile.readAll();

            QJsonDocument doc = QJsonDocument::fromJson(result.toUtf8());
            itineraryData = doc.object();

        }
        outputFile.close();



    } else {
        itineraryData = getItineraryData();
    }


    setItineraryList(itineraryData);
    sortItineraryList(Criterion::DURATION);
    ui->progressBar->setValue(80);

    if (m_itineraires.size() == 0) {
        ui->status->setText("Sorry, we could not find any itinerary...");
    } else {
        ui->status->setText("A few itineraries were found.\nClick on an itinerary card to get more information");
        setSortBy();
        ui->sortBy->show();
    }


    ui->search->setDisabled(false);
    displayItineraryList();
    ui->progressBar->setValue(100);
    ui->progressBar->hide();
}

void Interface::on_swap_clicked() {

}

void Interface::displayItinerary(QJsonArray paths, QStringList colors, QList<bool> isSectionPublic, Itineraire * itinerary) {

    for (int i(0); i < m_itineraires.length(); i++) {
        if (itinerary != m_itineraires.at(i)) {
            m_itineraires.at(i)->hideMoreInfo();
        }
    }

    QVariant returnedValue;
    QObject * object = ui->testMap->rootObject()->findChild<QObject*>("mapObject");
    QMetaObject::invokeMethod(object, "deleteRoute", Q_RETURN_ARG(QVariant, returnedValue));

    QVariant markerALocation = paths.first().toArray().last();
    QVariant markerBLocation = paths.last().toArray().first();

    QMetaObject::invokeMethod(object, "showMarkers",
                              Q_RETURN_ARG(QVariant, returnedValue),
                              Q_ARG(QVariant, markerALocation),
                              Q_ARG(QVariant, markerBLocation));

    for (int i(0); i < paths.size(); i++) {
        QVariant path = paths.at(i);
        QVariant color = colors.at(i);
        QVariant isPublic = isSectionPublic.at(i);
        QMetaObject::invokeMethod(object, "loadSection",
                                  Q_RETURN_ARG(QVariant, returnedValue),
                                  Q_ARG(QVariant, color),
                                  Q_ARG(QVariant, path),
                                  Q_ARG(QVariant, isPublic));
    }
}

void Interface::displayMouseCoordinates(QVariant lat, QVariant lon) {
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

QJsonObject Interface::generateAlgorithmInput() {
    bool includePrice = ui->price->isChecked();
    bool includeConnections = ui->connections->isChecked();
    bool includeCo2 = ui->co2->isChecked();
    bool includeEffort = ui->effort->isChecked();
    bool includeHeight = ui->height->isChecked();

    QStringList mouseCord = ui->startEdit->text().split(", ");
    qint64 startNodeId = nodeAPI.getNearestNodeId(mouseCord[0].toDouble(), mouseCord[1].toDouble());

    mouseCord = ui->endEdit->text().split(", ");
    qint64 endNodeId = nodeAPI.getNearestNodeId(mouseCord[0].toDouble(), mouseCord[1].toDouble());

    int departureTime = qRound(ui->depTimeEdit->time().msecsSinceStartOfDay() / 60000.0);
    QString privateTransportMode;

    if (ui->walking->isChecked())
        privateTransportMode = "walking";
    else if (ui->bike->isChecked())
        privateTransportMode = "bike";
    else
        privateTransportMode = "car";


    QJsonObject data {
        {"criteria", QJsonObject {
                {"price", includePrice},
                {"connections", includeConnections},
                {"co2", includeCo2},
                {"effort", includeEffort},
                {"height", includeHeight}
            }
        },
        {"start", startNodeId},
        {"dest", endNodeId},
        {"startTime", departureTime},
        {"mode", privateTransportMode}
    };

    return data;
}

void Interface::sortItineraryList(Criterion criterion) {


    for (int i(m_itineraires.size() - 1); i >= 1; i--) {
        for (int j(0); j <= i-1; j++) {

            bool shouldSwap = false;

            if (criterion == Criterion::PRICE) {
                shouldSwap = m_itineraires.at(j+1)->getPrice() < m_itineraires.at(j)->getPrice();
            }
            else  if (criterion == Criterion::CO2) {
                shouldSwap = m_itineraires.at(j+1)->getCo2() < m_itineraires.at(j)->getCo2();
            }
            else  if (criterion == Criterion::EFFORT) {
                shouldSwap = m_itineraires.at(j+1)->getEffort() < m_itineraires.at(j)->getEffort();

            }
            else  if (criterion == Criterion::DURATION) {
                shouldSwap = m_itineraires.at(j+1)->getDuration() < m_itineraires.at(j)->getDuration();
            }
            else  if (criterion == Criterion::CONNECTIONS) {
                shouldSwap = m_itineraires.at(j+1)->getConnections() < m_itineraires.at(j)->getConnections();
           } else  if (criterion == Criterion::HEIGHT) {
                shouldSwap = m_itineraires.at(j+1)->getHeight() < m_itineraires.at(j)->getHeight();
           }

           if (shouldSwap) {
                Itineraire * tmp = m_itineraires.at(j+1);
                m_itineraires.replace(j+1, m_itineraires.at(j));
                m_itineraires.replace(j,tmp);
            }
        }
    }
}

void Interface::on_sortBy_currentTextChanged(QString criterion) {

    hideItineraryList();


    if (criterion == "Price") {
        sortItineraryList(Criterion::PRICE);
    }

    if (criterion == "Duration") {
        sortItineraryList(Criterion::DURATION);
    }

    else if (criterion == "Effort") {
        sortItineraryList(Criterion::EFFORT);
    }
    else if (criterion == "CO2 emissions") {
        sortItineraryList(Criterion::CO2);
    }
    else if (criterion == "Connections") {
        sortItineraryList(Criterion::CONNECTIONS);
    } else if (criterion == "Height difference") {

        sortItineraryList(Criterion::HEIGHT);
    }


    displayItineraryList();
}

void Interface::setSortBy() {

    ui->sortBy->clear();

    bool includePrice;
    bool includeConnections;
    bool includeCo2;
    bool includeEffort;
    bool includeHeight;

    if (m_isStatic) {
        includePrice = true;
        includeConnections = true;
        includeCo2 = true;
        includeEffort = true;
        includeHeight = true;
    } else {

        QJsonObject criteria = m_input["criteria"].toObject();

        includePrice = criteria["price"].toBool();
        includeConnections = criteria["connections"].toBool();
        includeCo2 = criteria["co2"].toBool();
        includeEffort = criteria["effort"].toBool();
        includeHeight = criteria["height"].toBool();
    }



    QStringList sortByList;

    sortByList.push_back("Duration");

    if (includePrice)
        sortByList.push_back("Price");

    if (includeEffort)
        sortByList.push_back("Effort");

    if (includeCo2)
        sortByList.push_back("CO2 emissions");

    if (includeConnections)
        sortByList.push_back("Connections");
    if (includeHeight)
        sortByList.push_back("Height difference");


    ui->sortBy->addItems(sortByList);
}

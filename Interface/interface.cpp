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

#include "AlgoSources/functions.h"
#include "AlgoSources/Network.h"


using namespace std;

Interface::Interface(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Interface),
    m_network("Data/r.txt", "")
{
    ui->setupUi(this);

    ui->testMap->setSource(QUrl("qrc:/Qml/map.qml"));
    QObject * object = ui->testMap->rootObject();
    QObject::connect(object, SIGNAL(mapPressed(QVariant, QVariant)), this, SLOT(displayMouseCoordinates(QVariant, QVariant)));

    /* LEAVE AT */
    ui->depTimeEdit->setTime(QTime::currentTime());

    ui->status->hide();
    ui->progressBar->hide();


    /* ALGO */
    QString graph_file("Data/graphWalk.cr");
    QString nodes_file("Data/nodes.co");

    qDebug() << "Initializing graph";
    init_graph_complete(m_graph, m_nodes, graph_file.toStdString(), nodes_file.toStdString());
    qDebug() << "Graph completed";
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

void Interface::getItineraryData() {
    ui->progressBar->setValue(20);
    ui->status->setText("Generating algorithm input");

    ui->progressBar->setValue(40);
    ui->status->setText("Calculating itineraries");

    QJsonObject input = generateAlgorithmInput();
    qDebug() << input;



    qint64 start_node = qint64(input["start"].toDouble());
    qint64 end_node = qint64(input["dest"].toDouble());

//    if (start_node == 0 || end_node == 0) {
//        ui->status->setText("Could not find node");
//        //should send a signal
//        return;
//    }

    QStringList arguments = {"Data/graphWalk.cr",
                            "Data/nodes.co",
                            "Data/userInput.json",
                            "Data/output.json",
                            QString::number(start_node),
                            QString::number(end_node)};

    QString result = QString::fromStdString(fusion(m_graph, m_nodes, m_network, start_node, end_node));

    QFile jSonFile("Data/output.json");
    if (jSonFile.open(QIODevice::ReadWrite|QIODevice::Truncate)) {
            QTextStream stream(&jSonFile);
            QJsonDocument doc = QJsonDocument::fromJson(result.toUtf8());
            QString strJson(doc.toJson(QJsonDocument::Indented));
            stream << strJson << endl;
     }
    jSonFile.close();

    /*
    QProcess itineraryCalculator;
    itineraryCalculator.start(QDir::currentPath() + "/../Algo/bin/Debug/Algo.exe", arguments);
    itineraryCalculator.waitForFinished(-1);
    */

}

void Interface::setItineraryList() {

    QString jSonFileStr;
    QFile jSonFile("Data/output.json");
    jSonFile.open(QIODevice::ReadOnly | QIODevice::Text);
    jSonFileStr = jSonFile.readAll();
    jSonFile.close();

    QJsonDocument jSonDocument = QJsonDocument::fromJson(jSonFileStr.toUtf8());
    QJsonObject itineraires = jSonDocument.object();
    QJsonArray it = itineraires["itineraries"].toArray();

    int n = itineraires["nb_itineraries"].toInt();


    for (int i(0); i < n; i++) {
        QJsonObject itinerary = it[i].toObject();
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

void Interface::on_search_clicked() {
    if (ui->endEdit->text().isEmpty() || ui->startEdit->text().isEmpty())
        return;

    ui->search->setDisabled(true);

    ui->status->show();
    ui->progressBar->show();

    ui->status->setText("Clearing previous list");
    ui->progressBar->setValue(0);

    clearItineraryList();
    getItineraryData();
    setItineraryList();

    ui->progressBar->setValue(80);

    if (m_itineraires.size() == 0) {
        ui->status->setText("Sorry, we could not find any itinerary...");
    } else {
        ui->status->setText("Done !");
    }


    ui->search->setDisabled(false);
    displayItineraryList();
    ui->progressBar->setValue(100);

    //ui->status->hide();
    //ui->progressBar->hide();
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

    QStringList mouseCord = ui->startEdit->text().split(", ");
    qint64 startNodeId = nodeAPI.getNearestNodeId(mouseCord[0].toDouble(), mouseCord[1].toDouble());

    mouseCord = ui->endEdit->text().split(", ");
    qint64 endNodeId = nodeAPI.getNearestNodeId(mouseCord[0].toDouble(), mouseCord[1].toDouble());

    QString departureTime = ui->depTimeEdit->time().toString("HH:mm");
    QString privateTransportMode;

    if (ui->walking->isChecked())
        privateTransportMode = "walking";
    else if (ui->bike->isChecked())
        privateTransportMode = "bike";
    else
        privateTransportMode = "car";


    QJsonObject data {
        {"criterias", QJsonObject {
                {"price", includePrice},
                {"connections", includeConnections},
                {"co2", includeCo2},
                {"effort", includeEffort}
            }
        },
        {"start", startNodeId},
        {"dest", endNodeId},
        {"startTime", departureTime},
        {"mode", privateTransportMode}
    };

    QFile jSonFile("Data/userInput.json");
    if (jSonFile.open(QIODevice::ReadWrite|QIODevice::Truncate)) {
            QTextStream stream(&jSonFile);
            QJsonDocument doc(data);
            QString strJson(doc.toJson(QJsonDocument::Indented));
            stream << strJson << endl;
     }
    jSonFile.close();

    return data;
}

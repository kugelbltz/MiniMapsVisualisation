#include "itineraire.h"
#include "ui_itineraire.h"
#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDir>
#include <QTime>
#include <QJsonArray>
#include <QJsonObject>

Itineraire::Itineraire(QString filename, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Itineraire)
{
    ui->setupUi(this);

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    QString steps;
    QString startTime;
    QString endTime;

    while (!in.atEnd()) {
        QString info = in.readLine();
        QString nodes = in.readLine();

        QStringList infoList = info.split(" ");
        QStringList nodesList = nodes.split(" ");

        getPath(nodesList);

        if (startTime.isEmpty())
            startTime = infoList.at(2);
        endTime = infoList.at(3);

        QString type = (infoList.at(0) == "walking") ? "walking" : infoList.at(1);
        steps += type;
        steps += " - ";

        m_colors.push_back(m_transportColor[type]);

    }

    file.close();

    steps.replace(steps.length()-2, 2, "");

    QTime s = QTime::fromString(startTime, "h:mm");
    QTime e = QTime::fromString(endTime, "h:mm");

    QTime duration = e.addSecs(-(s.hour()*3600 + s.minute()*60));

    ui->duration->setText(QString::number(duration.minute()) + " min");
    ui->timeSlot->setText(startTime + " - " + endTime);
    ui->steps->setText(steps);
    ui->fullDescription->setText(filename);
    ui->fullDescription->setReadOnly(true);
    ui->fullDescription->hide();

    connect(ui->moreInfo, SIGNAL(clicked()), this, SLOT(toggleFullDescription()));
}

// SET TRANSPORT COLOR CODE
QHash<QString, QString> Itineraire::initTransportColor() {
    QHash<QString, QString> hash;
    hash["tram"] = "indianred";
    hash["bus"] = "grey";
    hash["walking"] = "cadetblue";
    return hash;
}

QHash<QString, QString> Itineraire::m_transportColor = initTransportColor();

Itineraire::~Itineraire()
{
    delete ui;
}

void Itineraire::toggleFullDescription() {
    emit moreInfoClicked(m_paths, m_colors);

    bool state = ui->fullDescription->isHidden();
    (state) ? ui->fullDescription->show() : ui->fullDescription->hide();
}




void Itineraire::getPath(QStringList nodes) {
    QJsonArray path;

    for (int i(0); i < nodes.length() ; i++) {
        QStringList coordinates = getNodeCoordinate(nodes.at(i).toInt());
        QJsonObject point
        {
            {"latitude", coordinates.at(0).toDouble()},
            {"longitude", coordinates.at(1).toDouble()}
        };
        path.push_back(point);
    }
    m_paths.push_back(path);
}


QStringList Itineraire::getNodeCoordinate(int nodeId) {
    QString filename = QDir::currentPath() + "/../TextFiles/nodes.txt";
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return QStringList({"0","0"});

    QTextStream in(&file);
    while (!in.atEnd()) {
        QStringList nodeInfo = in.readLine().split(" ");
        if (nodeInfo.at(0).toInt() == nodeId) {
            nodeInfo.removeFirst();
            return nodeInfo;
        }
    }

    file.close();
    return QStringList({"0","0"});
}

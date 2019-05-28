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
#include <QFile>
#include <QtMath>


Itineraire::Itineraire(QJsonObject description, QWidget *parent)  :
    QWidget(parent),
    ui(new Ui::Itineraire)
{
    ui->setupUi(this);
    setMouseTracking(true);
    ui->fullDescription->setAcceptRichText(true);

    QJsonObject criterias = description["criteria"].toObject();
    QJsonArray sections = description["sections"].toArray();


    QString steps;

    int itStartTime = sections.last().toObject()["start"].toInt();
    int itEndTime = sections.first().toObject()["end"].toInt();

    duration = criterias["time"].toInt();

    QString endName = nodeAPI.getNodeName(qint64(sections.first().toObject()["nodes"].toArray().first().toDouble()));

    for (int i(sections.size()-1); i >= 0; i--) {
        QJsonObject section = sections[i].toObject();
        QJsonArray nodes = section["nodes"].toArray();
        int routeId = section["idTransport"].toInt();
        int sectionStartTime = section["start"].toInt();
        int sectionEndTime = section["end"].toInt();

        QString firstNodeName = nodeAPI.getNodeName(qint64(nodes.last().toDouble()));

        getPath(nodes);

        QString sectionDescription;
        if (!section["public"].toBool()) {
            sectionDescription = getSectionDescription(sectionStartTime, sectionEndTime);
        } else {
            int nbStops = nodes.size(); //peut etre -1
            sectionDescription = getSectionDescription(sectionStartTime, sectionEndTime, nbStops, routeId);
        }

        ui->fullDescription->setCurrentFont(QFont("Raleway", 13, 63));
        QString sectionStartTimeStr = minToQTime(sectionStartTime).toString("hh:mm");
        ui->fullDescription->append(sectionStartTimeStr + " : " + firstNodeName);
        ui->fullDescription->setCurrentFont(QFont("Raleway", 9));
        ui->fullDescription->append("\t " + sectionDescription);

        QStringList routeInfo = nodeAPI.getRouteInfo(routeId);
        if (routeInfo[0] == "") {
            m_colors.push_back(m_transportColor["walking"]);
            steps += "walking";
        } else {
            m_colors.push_back(m_transportColor[routeInfo[0]]);
            steps += routeInfo[0];
        }

        steps += " - ";

        bool isPublic = section["public"].toBool();
        m_isSectionPublic.push_back(isPublic);

    }

    steps.replace(steps.length()-2, 2, "");

    ui->duration->setText(QString::number(duration) + " min");
    ui->timeSlot->setText(minToQTime(itStartTime).toString("hh:mm") + " - " + minToQTime(itEndTime).toString("hh:mm"));
    ui->steps->setText(steps);

    setCriterias(criterias);

    ui->fullDescription->setCurrentFont(QFont("Raleway", 13, 63));
    ui->fullDescription->append(minToQTime(itEndTime).toString("hh:mm") + " : " + endName);
    ui->fullDescription->setReadOnly(true);
    hideMoreInfo();

    ui->frame->setStyleSheet("QWidget {background-color:lightgray}"

                             "QFrame#frame {border: 0px;"
                             "border-radius:5px}"

                             "QLabel#duration, QLabel#timeSlot {font: 13pt Abel}"

                             "QLabel#steps {font: 17pt Abel}");
}


void Itineraire::setCriterias(QJsonObject criterias) {

    price = criterias["price"].toDouble();
    ui->priceValue->setText(QString::number(price) + " €");

    co2 = criterias["co2"].toDouble();
    ui->co2Value->setText(QString::number(co2) + " g");

    effort = criterias["effort"].toInt();
    ui->effortValue->setText(QString::number(effort) + " kCal");

    connections = criterias["connections"].toInt();
    ui->connectionsValue->setText(QString::number(connections));
}

qreal Itineraire::getPrice() {
    return price;
}

int Itineraire::getConnections() {
    return connections;
}

qreal Itineraire::getCo2() {
    return co2;
}

int Itineraire::getEffort() {
    return effort;
}

int Itineraire::getDuration() {
    return duration;
}

QString Itineraire::getSectionDescription(int sectionStartTime, int sectionEndTime, int nbStop, int routeId) {
    QString sectionDescription;

    int sectionDuration = sectionEndTime - sectionStartTime;

    if (nbStop == 0) {
        sectionDescription += "Walk for " + QString::number(sectionDuration) + " minutes";
    } else {
        QStringList routeInfo = nodeAPI.getRouteInfo(routeId);

        sectionDescription += routeInfo[1] + " direction " + routeInfo[2];
        sectionDescription += "\n\t" + QString::number(nbStop) + " stop(s) - " + QString::number(sectionDuration) + " minute(s)";
    }

    return sectionDescription;
}

void Itineraire::getPath(QJsonArray nodes) {
    QJsonArray path;

    for (int i(0); i < nodes.size(); i++) {
        qreal coordinates[2];
        nodeAPI.getNodeCoordinates(qint64(nodes[i].toDouble()), coordinates);

        if (qAbs(coordinates[0]) > 90.0  && qAbs(coordinates[1]) > 180.0)
            continue;

        QJsonObject point
        {
            {"latitude", coordinates[0]},
            {"longitude", coordinates[1]}
        };

        path.push_back(point);
    }
    m_paths.push_back(path);
}


// SET TRANSPORT COLOR CODE
QHash<QString, QString> Itineraire::initTransportColor() {
    QHash<QString, QString> hash;
    hash["tram"] = "#353FCC";
    hash["bus"] = "#209962";
    hash["walking"] = "#000000";
    hash["driving"] = "#FFA937";
    hash["biking"] = "#CC338D";
    return hash;
}

QHash<QString, QString> Itineraire::m_transportColor = initTransportColor();

Itineraire::~Itineraire()
{
    delete ui;
}



void Itineraire::mousePressEvent(QMouseEvent* e) {
    if(e->button() == Qt::LeftButton) {
        bool state = ui->fullDescription->isHidden();
        (state) ? ui->fullDescription->show() : ui->fullDescription->hide();
        (state) ? ui->line->show() : ui->line->hide();
        (state) ? ui->line2->show() : ui->line2->hide();
        (state) ? ui->criterias->show() : ui->line2->hide();

        (state) ? emit showMoreInfo(m_paths, m_colors, m_isSectionPublic, this) : hideMoreInfo();
    }
}

void Itineraire::hideMoreInfo() {
    ui->fullDescription->hide();
    ui->line->hide();
    ui->line2->hide();
    ui->criterias->hide();
}

QTime minToQTime(int min) {
    int h = min / 60;
    int m = min % 60;
    return QTime(h,m);
}

int QTimeToInt(QTime time) {
    return time.hour() * 60 + time.minute();
}

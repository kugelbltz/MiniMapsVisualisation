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

    QString startTime = sections[0].toObject()["start"].toString();
    QString endTime = sections[sections.size()-1].toObject()["end"].toString();
    QString duration = QString::number(criterias["time"].toInt());
    QString endName = nodeAPI.getNodeName(sections[sections.size()-1].toObject()["nodes"].toArray()[0].toInt());

    for (int i(0); i < sections.size();i++) {
        QJsonObject section = sections[i].toObject();
        QString name = nodeAPI.getNodeName(qint64(section["nodes"].toArray()[0].toInt()));

        getPath(section["nodes"].toArray());

        QString sectionDescription;
        if (!section["public"].toBool()) {
            sectionDescription = getSectionDescription(section["start"].toString(), section["end"].toString());
        } else {
            int nbStops = section["nodes"].toArray().size();
            sectionDescription = getSectionDescription(section["start"].toString(), section["end"].toString(), nbStops);
        }

        QString type = section["type"].toString();
        m_colors.push_back(m_transportColor[type]);

        steps += type;
        steps += " - ";

        ui->fullDescription->setCurrentFont(QFont("Raleway", 13, 63));
        ui->fullDescription->append(section["start"].toString() + " : " + name);
        ui->fullDescription->setCurrentFont(QFont("Raleway", 9));
        ui->fullDescription->append("\t " + sectionDescription);
    }

    steps.replace(steps.length()-2, 2, "");

    ui->duration->setText(duration + " min");
    ui->timeSlot->setText(startTime + " - " + endTime);
    ui->steps->setText(steps);

    setCriterias(criterias);

    ui->fullDescription->setCurrentFont(QFont("Raleway", 13, 63));
    ui->fullDescription->append(endTime + " : " + endName);
    ui->fullDescription->setReadOnly(true);
    hideMoreInfo();

    ui->frame->setStyleSheet("QWidget {background-color:lightgray}"

                             "QFrame#frame {border: 0px;"
                             "border-radius:10px}"

                             "QLabel#duration, QLabel#timeSlot {font: 13pt Abel}"

                             "QLabel#steps {font: 17pt Abel}");
}


void Itineraire::setCriterias(QJsonObject criterias) {
    QString distance = QString::number(criterias["distance"].toInt());
    ui->distanceValue->setText(distance + " m");

    QString heightDifference = QString::number(criterias["height"].toInt());
    ui->heightDifferenceValue->setText(heightDifference + " m");

    QString price = QString::number(criterias["price"].toDouble());
    ui->priceValue->setText(price + " €");

    QString co2 = QString::number(criterias["co2"].toDouble());
    ui->co2Value->setText(co2 + " g");

    QString effort = QString::number(criterias["effort"].toInt());
    ui->effortValue->setText(effort + " kCal");

    QString connections = QString::number(criterias["connections"].toInt());
    ui->connectionsValue->setText(connections);
}

QString Itineraire::getSectionDescription(QString start, QString end, int nbStop) {
    QString sectionDescription;

    QTime startTime = QTime::fromString(start, "hh:mm");
    QTime endTime = QTime::fromString(end, "hh:mm");
    int minutes = qCeil(startTime.secsTo(endTime)/60.0);

    if (nbStop == 0) {
        sectionDescription += "Marcher pendant " + QString::number(minutes) + " minutes";
    } else {
        QString lineName = "Ligne B";
        QString lineDirection = "Berge de la Garonne";
        sectionDescription += lineName + " direction " + lineDirection;
        sectionDescription += "\n\t" + QString::number(nbStop) + " arrêt(s) - " + QString::number(minutes) + " minute(s)";
    }

    return sectionDescription;
}

void Itineraire::getPath(QJsonArray nodes) {
    QJsonArray path;

    for (int i(0); i < nodes.size(); i++) {
        qreal coordinates[2];
        nodeAPI.getNodeCoordinates(qint64(nodes[i].toDouble()), coordinates);

        if (coordinates[0] < 0 && coordinates[1] > 180.0)
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



void Itineraire::mousePressEvent(QMouseEvent* e) {
    if(e->button() == Qt::LeftButton) {
        bool state = ui->fullDescription->isHidden();
        (state) ? ui->fullDescription->show() : ui->fullDescription->hide();
        (state) ? ui->line->show() : ui->line->hide();
        (state) ? ui->line2->show() : ui->line2->hide();
        (state) ? ui->criterias->show() : ui->line2->hide();

        (state) ? emit showMoreInfo(m_paths, m_colors, this) : hideMoreInfo();
    }
}

void Itineraire::hideMoreInfo() {
    ui->fullDescription->hide();
    ui->line->hide();
    ui->line2->hide();
    ui->criterias->hide();
}

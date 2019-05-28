#ifndef ITINERAIRE_H
#define ITINERAIRE_H

#include <QWidget>
#include <QVariant>
#include <QStringList>
#include <QJsonArray>
#include <QMouseEvent>
#include <QEvent>
#include <QTextStream>
#include <nodeapirequest.h>
#include <QTime>
#include <QJsonObject>

namespace Ui {
class Itineraire;
}

class Itineraire : public QWidget
{
    Q_OBJECT

public:
    explicit Itineraire(QJsonObject description, QWidget *parent = nullptr);
    ~Itineraire();
    void getPath(QJsonArray nodes);
    static QHash<QString, QString> initTransportColor();
    void mousePressEvent(QMouseEvent*);
    void hideMoreInfo();
    QString getSectionDescription(int sectionStartTime, int sectionEndTime, int nbStop = 0, int routeId = 0);
    void setCriterias(QJsonObject criterias);

    qreal getPrice();
    int getConnections();
    qreal getCo2();
    int getEffort();
    int getDuration();

private:
    Ui::Itineraire *ui;
    QJsonArray m_paths;
    QStringList m_colors;
    QList<bool> m_isSectionPublic;
    static QHash<QString, QString> m_transportColor;
    NodeAPIRequest nodeAPI;

    qreal price;
    int connections;
    qreal co2;
    int effort;
    int duration;


signals:
    void showMoreInfo(QJsonArray, QStringList, QList<bool>,Itineraire *);
};

QTime minToQTime(int min);
int QTimeToInt(QTime time);


#endif // ITINERAIRE_H

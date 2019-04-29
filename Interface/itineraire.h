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
    QString getSectionDescription(QString start, QString end, int nbStop = 0);
    void setCriterias(QJsonObject criterias);

private:
    Ui::Itineraire *ui;
    QJsonArray m_paths;
    QStringList m_colors;
    static QHash<QString, QString> m_transportColor;
    NodeAPIRequest nodeAPI;


signals:
    void showMoreInfo(QJsonArray, QStringList, Itineraire *);
};

#endif // ITINERAIRE_H

#ifndef INTERFACE_H
#define INTERFACE_H

#include <QMainWindow>
#include "itineraire.h"
#include <QVector>
#include <QHash>
#include <QJsonArray>
#include <QStringList>
#include <QJsonObject>
#include <QNetworkReply>
#include <nodeapirequest.h>

#include <map>

namespace Ui {
class Interface;
}

class Interface : public QMainWindow
{
    Q_OBJECT

public:
    explicit Interface(QWidget *parent = nullptr);
    ~Interface();
    QJsonObject generateAlgorithmInput();
    void clearItineraryList();
    void getItineraryData();
    void setItineraryList();
    void displayItineraryList();
    void emptyFile(QString filename);

private slots:
    void on_swap_clicked();
    void on_search_clicked();
    void displayItinerary(QJsonArray, QStringList, Itineraire *);
    void displayMouseCoordinates(QVariant, QVariant);

private:
    Ui::Interface *ui;
    QVector<Itineraire*> m_itineraires;
    NodeAPIRequest nodeAPI;
};

#endif // INTERFACE_H

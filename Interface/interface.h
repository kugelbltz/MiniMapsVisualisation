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
#include "AlgoSources/Arc.h"
#include "AlgoSources/Graph.h"
#include "AlgoSources/Position.h"
#include "AlgoSources/Network.h"

namespace Ui {
class Interface;
}

class Interface : public QMainWindow
{
    Q_OBJECT

public:
    enum class Criterion { DURATION, CO2, EFFORT, CONNECTIONS, PRICE, HEIGHT };
    explicit Interface(QString dataDir, bool isStatic, QWidget *parent = nullptr);
    ~Interface();
    QJsonObject generateAlgorithmInput();
    void clearItineraryList();
    QJsonObject getItineraryData();
    void setItineraryList(QJsonObject itineraryData);
    void displayItineraryList();
    void hideItineraryList();
    void sortItineraryList(Criterion criterion);
    void setSortBy();


private slots:
    void on_swap_clicked();
    void on_search_clicked();
    void displayItinerary(QJsonArray, QStringList, QList<bool>, Itineraire *);
    void displayMouseCoordinates(QVariant, QVariant);
    void on_sortBy_currentTextChanged(QString);

private:
    Ui::Interface *ui;
    QVector<Itineraire*> m_itineraires;
    NodeAPIRequest nodeAPI;

    Graph m_graph;
    std::map<long long, Position> m_nodes;
    Network m_network;
    QJsonObject m_input;
    bool m_isStatic;
    QString m_dataDir;

};


#endif // INTERFACE_H

#ifndef INTERFACE_H
#define INTERFACE_H

#include <QMainWindow>
#include <QGraphicsPixmapItem>
#include "carte.h"
#include "itineraire.h"
#include <QVector>
#include <QHash>
#include <QJsonArray>
#include <QStringList>

namespace Ui {
class Interface;
}

class Interface : public QMainWindow
{
    Q_OBJECT

public:
    explicit Interface(QWidget *parent = nullptr);
    ~Interface();
    void addItineraries();

private slots:
    void on_swap_clicked();
    void on_search_clicked();
    void displayItinerary(QJsonArray, QStringList, Itineraire *);
    void mouseCoordinates(QVariant, QVariant);

private:
    Ui::Interface *ui;
    Carte * m_carte;
    QVector<Itineraire*> m_itineraires;
};

#endif // INTERFACE_H

#ifndef INTERFACE_H
#define INTERFACE_H

#include <QMainWindow>
#include <QGraphicsPixmapItem>
#include "carte.h"
#include "itineraire.h"
#include <QVector>

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
    void getItineraires(qreal startLat, qreal startLon, qreal endLat, qreal endLon);

private slots:
    void on_swap_clicked();
    void on_search_clicked();

private:
    Ui::Interface *ui;

    Carte * m_carte;

    QVector<Itineraire*> m_itineraires;
};

#endif // INTERFACE_H

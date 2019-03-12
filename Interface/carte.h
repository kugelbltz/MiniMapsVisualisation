#ifndef CARTE_H
#define CARTE_H

#include <QWidget>
#include <QGraphicsItem>
#include <QGraphicsScene>

namespace Ui {
class Carte;
}

class Carte : public QWidget
{
    Q_OBJECT

public:
    explicit Carte(QWidget *parent = nullptr);
    ~Carte();
    QPoint toXY(qreal lat, qreal lon);

private:
    Ui::Carte *ui;
    qreal m_scale;
    QGraphicsPixmapItem * m_mapItem;
    QGraphicsScene * m_mapScene;

private slots:
    void zoom(int value);
};

#endif // CARTE_H

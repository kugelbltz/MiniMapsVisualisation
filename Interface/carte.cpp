#include "carte.h"
#include "ui_carte.h"
#include <QDir>
#include <QGraphicsPixmapItem>
#include <iostream>
#include <QtMath>


static const qreal NORTH = 44.903;
static const qreal SOUTH = 44.776;
static const qreal WEST = -0.687;
static const qreal EAST = -0.481;

Carte::Carte(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Carte)
{
    ui->setupUi(this);
    QImage image(QDir::currentPath() + "/../Assets/map.jpg");
    m_mapItem = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    m_mapScene = new QGraphicsScene;
    ui->mapDisplay->setScene(m_mapScene);
    m_mapScene->addItem(m_mapItem);
    m_scale = qreal(ui->zoom->value()/100.0);

    QPoint test = toXY(44.8107262,-0.5775296);
    QGraphicsRectItem * rect = m_mapScene->addRect(test.x(),test.y(), 100, 100);

    QList<QGraphicsItem *> list = m_mapScene->items();
    for (int i = 0; i < list.size(); ++i) {
        list.at(i)->setScale(m_scale);
    }

    m_mapScene->setSceneRect(0,0, m_mapItem->pixmap().width()*m_scale,m_mapItem->pixmap().height()*m_scale);
    ui->mapDisplay->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->mapDisplay->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->mapDisplay->show();

    connect(ui->zoom, SIGNAL(valueChanged(int)), this, SLOT(zoom(int)));
}

Carte::~Carte()
{
    delete ui;
}

void Carte::zoom(int value) {
    m_scale = value/100.0;
    m_mapScene->setSceneRect(0,0, m_mapItem->pixmap().width()*m_scale,m_mapItem->pixmap().height()*m_scale);

    QList<QGraphicsItem *> list = m_mapScene->items();
    for (int i = 0; i < list.size(); ++i) {
        list.at(i)->setScale(m_scale);
    }


    //m_mapItem->setScale(m_scale);
}

QPoint Carte::toXY(qreal lat, qreal lon) {
    qreal phi = qDegreesToRadians(lat);
    qreal lambda = qDegreesToRadians(lon);

    int w = int(m_mapItem->pixmap().width()*360/(qAbs(EAST-WEST)));
    int h = int(m_mapItem->pixmap().height()*180/(qAbs(NORTH-SOUTH)));

    int x = int(w * (lambda + 180)/360);
    int y = int(h/2 - w/(2*M_PI)*qLn(qTan(M_PI_4 + phi/2)));

    int x0 = int(w * (WEST + 180)/360);
    int y0 = int(h/2 - w/(2*M_PI)*qLn(qTan(M_PI_4 + NORTH/2)));

    x -= x0; // Enfaite non, c'est leur position en X et Y qu'il faut que je mette
    y -= y0;

    std::cout << x << std::endl;
    std::cout << y << std::endl;

    return QPoint(x,y);
}


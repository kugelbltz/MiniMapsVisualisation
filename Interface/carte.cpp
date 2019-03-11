#include "carte.h"
#include "ui_carte.h"
#include <QDir>
#include <QGraphicsPixmapItem>
#include <iostream>

Carte::Carte(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Carte)
{
    ui->setupUi(this);
    QImage image(QDir::currentPath() + "/../Assets/bg.jpg");
    m_mapItem = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    m_mapScene = new QGraphicsScene;
    ui->mapDisplay->setScene(m_mapScene);
    m_mapScene->addItem(m_mapItem);
    m_scale = qreal(ui->zoom->value()/100.0);


    m_mapItem->setScale(m_scale);

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
    m_mapItem->setScale(m_scale);
}


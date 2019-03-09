#include "interface.h"
#include "ui_interface.h"
#include <QGraphicsPixmapItem>
#include <iostream>

using namespace std;

Interface::Interface(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Interface)
{
    ui->setupUi(this);

    QImage image("C:/Users/User/OneDrive/Documents/Enseirb/S8/ProjetAvance/Interface/Assets/bg.jpg");
    m_carte = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    m_scene = new QGraphicsScene;
    ui->carte->setScene(m_scene);
    m_scene->addItem(m_carte);
    m_scale = qreal(ui->zoom->value()/100.0);
    m_carte->setScale(m_scale);

    m_scene->setSceneRect(0,0, m_carte->pixmap().width()*m_scale,m_carte->pixmap().height()*m_scale);

    ui->carte->show();
    ui->description->hide();
    ui->fullDescription->hide();

}

Interface::~Interface()
{
    delete ui;
}

void Interface::on_zoom_valueChanged(int value) {
    m_scale = value/100.0;
    m_scene->setSceneRect(0,0, m_carte->pixmap().width()*m_scale,m_carte->pixmap().height()*m_scale);
    m_carte->setScale(m_scale);
}

void Interface::on_up_pressed() {
    ui->carte->viewport()->scroll(0,1);
}

void Interface::on_down_pressed() {
    QPointF test = ui->carte->mapToScene(ui->carte->rect().center());
    ui->carte->centerOn(test.x(),test.y());
}

void Interface::on_left_pressed() {
    QPointF test = ui->carte->mapToScene(ui->carte->rect()).boundingRect().center();
    ui->carte->centerOn(test.x(),test.y());
}

void Interface::on_right_pressed() {
    QPointF test = ui->carte->mapToScene(ui->carte->rect()).boundingRect().center();
    ui->carte->centerOn(test.x(),test.y());
}

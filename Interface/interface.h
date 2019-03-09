#ifndef INTERFACE_H
#define INTERFACE_H

#include <QMainWindow>
#include <QGraphicsPixmapItem>

namespace Ui {
class Interface;
}

class Interface : public QMainWindow
{
    Q_OBJECT

public:
    explicit Interface(QWidget *parent = nullptr);
    ~Interface();
private slots:
    void on_zoom_valueChanged(int value);
    void on_up_pressed();
    void on_down_pressed();
    void on_left_pressed();
    void on_right_pressed();
private:
    Ui::Interface *ui;
    QGraphicsPixmapItem * m_carte;
    QGraphicsScene * m_scene;
    qreal m_scale;
};

#endif // INTERFACE_H

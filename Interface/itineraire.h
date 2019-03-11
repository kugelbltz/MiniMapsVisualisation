#ifndef ITINERAIRE_H
#define ITINERAIRE_H

#include <QWidget>

namespace Ui {
class Itineraire;
}

class Itineraire : public QWidget
{
    Q_OBJECT

public:
    explicit Itineraire(QString fullDescription, QWidget *parent = nullptr);
    ~Itineraire();

private:
    Ui::Itineraire *ui;

private slots:
    void toggleFullDescription();
};

#endif // ITINERAIRE_H

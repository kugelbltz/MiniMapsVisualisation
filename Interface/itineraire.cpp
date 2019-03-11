#include "itineraire.h"
#include "ui_itineraire.h"
#include <iostream>

Itineraire::Itineraire(QString fullDescription, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Itineraire)
{
    ui->setupUi(this);

    ui->duration->setText("45 min");
    ui->timeSlot->setText("15:30 - 16h15");
    ui->steps->setText("1 > 45 > marche > A");
    ui->fullDescription->setText(fullDescription);
    ui->fullDescription->hide();

    connect(ui->moreInfo, SIGNAL(clicked()), this, SLOT(toggleFullDescription()));
}

Itineraire::~Itineraire()
{
    delete ui;
}

void Itineraire::toggleFullDescription() {
    bool state = ui->fullDescription->isHidden();
    (state) ? ui->fullDescription->show() : ui->fullDescription->hide();
}

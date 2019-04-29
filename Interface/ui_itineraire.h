/********************************************************************************
** Form generated from reading UI file 'itineraire.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ITINERAIRE_H
#define UI_ITINERAIRE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Itineraire
{
public:
    QVBoxLayout *verticalLayout_2;
    QFrame *frame;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *itineraireLayout;
    QGridLayout *gridLayout_2;
    QLabel *timeSlot;
    QLabel *duration;
    QLabel *steps;
    QFrame *line;
    QWidget *criterias;
    QFormLayout *criteriasLayout;
    QLabel *distance;
    QLabel *distanceValue;
    QLabel *price;
    QLabel *priceValue;
    QLabel *connections;
    QLabel *connectionsValue;
    QLabel *heightDifference;
    QLabel *heightDifferenceValue;
    QLabel *co2Value;
    QLabel *effort;
    QLabel *effortValue;
    QLabel *co2;
    QFrame *line2;
    QTextEdit *fullDescription;

    void setupUi(QWidget *Itineraire)
    {
        if (Itineraire->objectName().isEmpty())
            Itineraire->setObjectName(QString::fromUtf8("Itineraire"));
        Itineraire->resize(391, 528);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Itineraire->sizePolicy().hasHeightForWidth());
        Itineraire->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(Itineraire);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        frame = new QFrame(Itineraire);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Plain);
        verticalLayout_3 = new QVBoxLayout(frame);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 0, -1, -1);
        itineraireLayout = new QVBoxLayout();
        itineraireLayout->setObjectName(QString::fromUtf8("itineraireLayout"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        timeSlot = new QLabel(frame);
        timeSlot->setObjectName(QString::fromUtf8("timeSlot"));

        gridLayout_2->addWidget(timeSlot, 0, 0, 1, 1);

        duration = new QLabel(frame);
        duration->setObjectName(QString::fromUtf8("duration"));

        gridLayout_2->addWidget(duration, 0, 2, 2, 1);

        steps = new QLabel(frame);
        steps->setObjectName(QString::fromUtf8("steps"));

        gridLayout_2->addWidget(steps, 1, 0, 1, 2);


        itineraireLayout->addLayout(gridLayout_2);

        line = new QFrame(frame);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        itineraireLayout->addWidget(line);

        criterias = new QWidget(frame);
        criterias->setObjectName(QString::fromUtf8("criterias"));
        criteriasLayout = new QFormLayout(criterias);
        criteriasLayout->setObjectName(QString::fromUtf8("criteriasLayout"));
        criteriasLayout->setContentsMargins(-1, 1, -1, -1);
        distance = new QLabel(criterias);
        distance->setObjectName(QString::fromUtf8("distance"));

        criteriasLayout->setWidget(0, QFormLayout::LabelRole, distance);

        distanceValue = new QLabel(criterias);
        distanceValue->setObjectName(QString::fromUtf8("distanceValue"));

        criteriasLayout->setWidget(0, QFormLayout::FieldRole, distanceValue);

        price = new QLabel(criterias);
        price->setObjectName(QString::fromUtf8("price"));

        criteriasLayout->setWidget(1, QFormLayout::LabelRole, price);

        priceValue = new QLabel(criterias);
        priceValue->setObjectName(QString::fromUtf8("priceValue"));

        criteriasLayout->setWidget(1, QFormLayout::FieldRole, priceValue);

        connections = new QLabel(criterias);
        connections->setObjectName(QString::fromUtf8("connections"));

        criteriasLayout->setWidget(2, QFormLayout::LabelRole, connections);

        connectionsValue = new QLabel(criterias);
        connectionsValue->setObjectName(QString::fromUtf8("connectionsValue"));

        criteriasLayout->setWidget(2, QFormLayout::FieldRole, connectionsValue);

        heightDifference = new QLabel(criterias);
        heightDifference->setObjectName(QString::fromUtf8("heightDifference"));

        criteriasLayout->setWidget(3, QFormLayout::LabelRole, heightDifference);

        heightDifferenceValue = new QLabel(criterias);
        heightDifferenceValue->setObjectName(QString::fromUtf8("heightDifferenceValue"));

        criteriasLayout->setWidget(3, QFormLayout::FieldRole, heightDifferenceValue);

        co2Value = new QLabel(criterias);
        co2Value->setObjectName(QString::fromUtf8("co2Value"));

        criteriasLayout->setWidget(4, QFormLayout::FieldRole, co2Value);

        effort = new QLabel(criterias);
        effort->setObjectName(QString::fromUtf8("effort"));

        criteriasLayout->setWidget(5, QFormLayout::LabelRole, effort);

        effortValue = new QLabel(criterias);
        effortValue->setObjectName(QString::fromUtf8("effortValue"));

        criteriasLayout->setWidget(5, QFormLayout::FieldRole, effortValue);

        co2 = new QLabel(criterias);
        co2->setObjectName(QString::fromUtf8("co2"));

        criteriasLayout->setWidget(4, QFormLayout::LabelRole, co2);


        itineraireLayout->addWidget(criterias);

        line2 = new QFrame(frame);
        line2->setObjectName(QString::fromUtf8("line2"));
        line2->setFrameShape(QFrame::HLine);
        line2->setFrameShadow(QFrame::Sunken);

        itineraireLayout->addWidget(line2);

        fullDescription = new QTextEdit(frame);
        fullDescription->setObjectName(QString::fromUtf8("fullDescription"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(fullDescription->sizePolicy().hasHeightForWidth());
        fullDescription->setSizePolicy(sizePolicy1);
        fullDescription->setFrameShape(QFrame::NoFrame);
        fullDescription->setFrameShadow(QFrame::Plain);

        itineraireLayout->addWidget(fullDescription);


        verticalLayout->addLayout(itineraireLayout);


        verticalLayout_3->addLayout(verticalLayout);


        verticalLayout_2->addWidget(frame);


        retranslateUi(Itineraire);

        QMetaObject::connectSlotsByName(Itineraire);
    } // setupUi

    void retranslateUi(QWidget *Itineraire)
    {
        Itineraire->setWindowTitle(QApplication::translate("Itineraire", "Form", nullptr));
        timeSlot->setText(QApplication::translate("Itineraire", "TextLabel", nullptr));
        duration->setText(QApplication::translate("Itineraire", "TextLabel", nullptr));
        steps->setText(QApplication::translate("Itineraire", "TextLabel", nullptr));
        distance->setText(QApplication::translate("Itineraire", "Distance", nullptr));
        distanceValue->setText(QApplication::translate("Itineraire", "25 g", nullptr));
        price->setText(QApplication::translate("Itineraire", "Price", nullptr));
        priceValue->setText(QApplication::translate("Itineraire", "72 kCal", nullptr));
        connections->setText(QApplication::translate("Itineraire", "Connections", nullptr));
        connectionsValue->setText(QApplication::translate("Itineraire", "TextLabel", nullptr));
        heightDifference->setText(QApplication::translate("Itineraire", "Height difference", nullptr));
        heightDifferenceValue->setText(QApplication::translate("Itineraire", "TextLabel", nullptr));
        co2Value->setText(QApplication::translate("Itineraire", "TextLabel", nullptr));
        effort->setText(QApplication::translate("Itineraire", "Effort", nullptr));
        effortValue->setText(QApplication::translate("Itineraire", "TextLabel", nullptr));
        co2->setText(QApplication::translate("Itineraire", "CO2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Itineraire: public Ui_Itineraire {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ITINERAIRE_H

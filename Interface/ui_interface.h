/********************************************************************************
** Form generated from reading UI file 'interface.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERFACE_H
#define UI_INTERFACE_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QtQuickWidgets/QQuickWidget"

QT_BEGIN_NAMESPACE

class Ui_Interface
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *itineraryLayout;
    QHBoxLayout *horizontalLayout_2;
    QFormLayout *formLayout;
    QLabel *start;
    QLineEdit *startEdit;
    QLabel *end;
    QLineEdit *endEdit;
    QPushButton *swap;
    QFrame *line;
    QGridLayout *gridLayout;
    QFormLayout *formLayout_2;
    QLabel *depTime;
    QTimeEdit *depTimeEdit;
    QPushButton *search;
    QGroupBox *options;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *co2;
    QCheckBox *effort;
    QCheckBox *connections;
    QCheckBox *price;
    QCheckBox *height;
    QLabel *criterias;
    QGroupBox *privTrans;
    QVBoxLayout *verticalLayout;
    QRadioButton *walking;
    QRadioButton *bike;
    QRadioButton *car;
    QFrame *line_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents_2;
    QVBoxLayout *verticalLayout_4;
    QProgressBar *progressBar;
    QLabel *status;
    QComboBox *sortBy;
    QWidget *techArea;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *techLayout;
    QSpacerItem *verticalSpacer;
    QQuickWidget *testMap;
    QMenuBar *menubar;
    QMenu *menuQuit;
    QMenu *menuIcon;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Interface)
    {
        if (Interface->objectName().isEmpty())
            Interface->setObjectName(QString::fromUtf8("Interface"));
        Interface->setEnabled(true);
        Interface->resize(874, 563);
        Interface->setStyleSheet(QString::fromUtf8("font: 8pt \"Raleway\";"));
        centralwidget = new QWidget(Interface);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMaximumSize(QSize(600, 16777215));
        widget->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_3 = new QHBoxLayout(widget);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        itineraryLayout = new QVBoxLayout();
        itineraryLayout->setObjectName(QString::fromUtf8("itineraryLayout"));
        itineraryLayout->setSizeConstraint(QLayout::SetMaximumSize);
        itineraryLayout->setContentsMargins(0, -1, -1, -1);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        start = new QLabel(widget);
        start->setObjectName(QString::fromUtf8("start"));

        formLayout->setWidget(0, QFormLayout::LabelRole, start);

        startEdit = new QLineEdit(widget);
        startEdit->setObjectName(QString::fromUtf8("startEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, startEdit);

        end = new QLabel(widget);
        end->setObjectName(QString::fromUtf8("end"));

        formLayout->setWidget(1, QFormLayout::LabelRole, end);

        endEdit = new QLineEdit(widget);
        endEdit->setObjectName(QString::fromUtf8("endEdit"));
        endEdit->setStyleSheet(QString::fromUtf8(""));

        formLayout->setWidget(1, QFormLayout::FieldRole, endEdit);


        horizontalLayout_2->addLayout(formLayout);

        swap = new QPushButton(widget);
        swap->setObjectName(QString::fromUtf8("swap"));

        horizontalLayout_2->addWidget(swap);


        itineraryLayout->addLayout(horizontalLayout_2);

        line = new QFrame(widget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        itineraryLayout->addWidget(line);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(-1, 0, -1, -1);
        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        depTime = new QLabel(widget);
        depTime->setObjectName(QString::fromUtf8("depTime"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, depTime);

        depTimeEdit = new QTimeEdit(widget);
        depTimeEdit->setObjectName(QString::fromUtf8("depTimeEdit"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, depTimeEdit);


        gridLayout->addLayout(formLayout_2, 1, 0, 1, 1);

        search = new QPushButton(widget);
        search->setObjectName(QString::fromUtf8("search"));
        search->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(search, 3, 0, 1, 2);

        options = new QGroupBox(widget);
        options->setObjectName(QString::fromUtf8("options"));
        verticalLayout_2 = new QVBoxLayout(options);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        co2 = new QCheckBox(options);
        co2->setObjectName(QString::fromUtf8("co2"));

        verticalLayout_2->addWidget(co2);

        effort = new QCheckBox(options);
        effort->setObjectName(QString::fromUtf8("effort"));

        verticalLayout_2->addWidget(effort);

        connections = new QCheckBox(options);
        connections->setObjectName(QString::fromUtf8("connections"));

        verticalLayout_2->addWidget(connections);

        price = new QCheckBox(options);
        price->setObjectName(QString::fromUtf8("price"));

        verticalLayout_2->addWidget(price);

        height = new QCheckBox(options);
        height->setObjectName(QString::fromUtf8("height"));

        verticalLayout_2->addWidget(height);


        gridLayout->addWidget(options, 1, 1, 2, 1);

        criterias = new QLabel(widget);
        criterias->setObjectName(QString::fromUtf8("criterias"));

        gridLayout->addWidget(criterias, 0, 0, 1, 2);

        privTrans = new QGroupBox(widget);
        privTrans->setObjectName(QString::fromUtf8("privTrans"));
        verticalLayout = new QVBoxLayout(privTrans);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        walking = new QRadioButton(privTrans);
        walking->setObjectName(QString::fromUtf8("walking"));
        walking->setChecked(true);

        verticalLayout->addWidget(walking);

        bike = new QRadioButton(privTrans);
        bike->setObjectName(QString::fromUtf8("bike"));
        bike->setCheckable(false);

        verticalLayout->addWidget(bike);

        car = new QRadioButton(privTrans);
        car->setObjectName(QString::fromUtf8("car"));
        car->setCheckable(false);

        verticalLayout->addWidget(car);


        gridLayout->addWidget(privTrans, 2, 0, 1, 1);


        itineraryLayout->addLayout(gridLayout);

        line_2 = new QFrame(widget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        itineraryLayout->addWidget(line_2);

        scrollArea = new QScrollArea(widget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 580, 185));
        verticalLayout_4 = new QVBoxLayout(scrollAreaWidgetContents_2);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        progressBar = new QProgressBar(scrollAreaWidgetContents_2);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(24);
        progressBar->setTextVisible(false);
        progressBar->setInvertedAppearance(false);

        verticalLayout_4->addWidget(progressBar);

        status = new QLabel(scrollAreaWidgetContents_2);
        status->setObjectName(QString::fromUtf8("status"));
        QFont font;
        font.setFamily(QString::fromUtf8("Raleway"));
        font.setPointSize(8);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        status->setFont(font);
        status->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(status);

        sortBy = new QComboBox(scrollAreaWidgetContents_2);
        sortBy->addItem(QString());
        sortBy->addItem(QString());
        sortBy->addItem(QString());
        sortBy->addItem(QString());
        sortBy->addItem(QString());
        sortBy->setObjectName(QString::fromUtf8("sortBy"));

        verticalLayout_4->addWidget(sortBy);

        techArea = new QWidget(scrollAreaWidgetContents_2);
        techArea->setObjectName(QString::fromUtf8("techArea"));
        verticalLayout_5 = new QVBoxLayout(techArea);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        techLayout = new QVBoxLayout();
        techLayout->setObjectName(QString::fromUtf8("techLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        techLayout->addItem(verticalSpacer);


        verticalLayout_5->addLayout(techLayout);


        verticalLayout_4->addWidget(techArea);

        scrollArea->setWidget(scrollAreaWidgetContents_2);

        itineraryLayout->addWidget(scrollArea);


        horizontalLayout_3->addLayout(itineraryLayout);


        horizontalLayout->addWidget(widget);

        testMap = new QQuickWidget(centralwidget);
        testMap->setObjectName(QString::fromUtf8("testMap"));
        testMap->setResizeMode(QQuickWidget::SizeRootObjectToView);

        horizontalLayout->addWidget(testMap);

        Interface->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Interface);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setEnabled(true);
        menubar->setGeometry(QRect(0, 0, 874, 26));
        menubar->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 165, 67);\n"
"color: rgb(255, 255, 255);\n"
"font: 12pt \"Abel\";"));
        menubar->setNativeMenuBar(false);
        menuQuit = new QMenu(menubar);
        menuQuit->setObjectName(QString::fromUtf8("menuQuit"));
        menuIcon = new QMenu(menubar);
        menuIcon->setObjectName(QString::fromUtf8("menuIcon"));
        menuIcon->setEnabled(true);
        menuIcon->setMaximumSize(QSize(16777207, 16777215));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Images/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        menuIcon->setIcon(icon);
        Interface->setMenuBar(menubar);
        statusbar = new QStatusBar(Interface);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Interface->setStatusBar(statusbar);

        menubar->addAction(menuIcon->menuAction());
        menubar->addAction(menuQuit->menuAction());

        retranslateUi(Interface);

        QMetaObject::connectSlotsByName(Interface);
    } // setupUi

    void retranslateUi(QMainWindow *Interface)
    {
        Interface->setWindowTitle(QApplication::translate("Interface", "MainWindow", nullptr));
        start->setText(QApplication::translate("Interface", "Start :", nullptr));
        startEdit->setPlaceholderText(QApplication::translate("Interface", "Click on the map or type coordinates", nullptr));
        end->setText(QApplication::translate("Interface", "Destination :", nullptr));
        endEdit->setPlaceholderText(QApplication::translate("Interface", "Click on the map or type coordinates", nullptr));
        swap->setText(QApplication::translate("Interface", "SWAP", nullptr));
        depTime->setText(QApplication::translate("Interface", "Leave at :", nullptr));
        search->setText(QApplication::translate("Interface", "Search", nullptr));
        options->setTitle(QApplication::translate("Interface", "Search for best itineraries given :", nullptr));
        co2->setText(QApplication::translate("Interface", "CO2 emissions", nullptr));
        effort->setText(QApplication::translate("Interface", "effort", nullptr));
        connections->setText(QApplication::translate("Interface", "connections", nullptr));
        price->setText(QApplication::translate("Interface", "price", nullptr));
        height->setText(QApplication::translate("Interface", "height difference", nullptr));
        criterias->setText(QApplication::translate("Interface", "Criterias", nullptr));
        privTrans->setTitle(QApplication::translate("Interface", "Private transportation", nullptr));
        walking->setText(QApplication::translate("Interface", "walking", nullptr));
        bike->setText(QApplication::translate("Interface", "biking (not available)", nullptr));
        car->setText(QApplication::translate("Interface", "driving (not available)", nullptr));
        status->setText(QApplication::translate("Interface", "Status", nullptr));
        sortBy->setItemText(0, QApplication::translate("Interface", "Duration", nullptr));
        sortBy->setItemText(1, QApplication::translate("Interface", "CO2 emissions", nullptr));
        sortBy->setItemText(2, QApplication::translate("Interface", "Effort", nullptr));
        sortBy->setItemText(3, QApplication::translate("Interface", "Connections", nullptr));
        sortBy->setItemText(4, QApplication::translate("Interface", "Price", nullptr));

        menuQuit->setTitle(QApplication::translate("Interface", "Quit", nullptr));
        menuIcon->setTitle(QApplication::translate("Interface", "Icon", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Interface: public Ui_Interface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFACE_H

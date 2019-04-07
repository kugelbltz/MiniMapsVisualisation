#ifndef ITINERAIRE_H
#define ITINERAIRE_H

#include <QWidget>
#include <QVariant>
#include <QStringList>
#include <QJsonArray>
#include <QMouseEvent>
#include <QEvent>

namespace Ui {
class Itineraire;
}

class Itineraire : public QWidget
{
    Q_OBJECT

public:
    explicit Itineraire(QString filename, QWidget *parent = nullptr);
    ~Itineraire();
    void getPath(QStringList nodes);
    QStringList getNodeCoordinate(int nodeId);
    static QHash<QString, QString> initTransportColor();
    void mousePressEvent(QMouseEvent*);
    void hideMoreInfo();

private:
    Ui::Itineraire *ui;
    QJsonArray m_paths;
    QStringList m_colors;
    static QHash<QString, QString> m_transportColor;

signals:
    void showMoreInfo(QJsonArray, QStringList, Itineraire *);
};

#endif // ITINERAIRE_H

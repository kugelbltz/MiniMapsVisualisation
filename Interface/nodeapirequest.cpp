#include "nodeapirequest.h"
#include <QNetworkAccessManager>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>

NodeAPIRequest::NodeAPIRequest()
{

}

QJsonObject NodeAPIRequest::nodeAPIGetRequest(QString url) {
    QNetworkAccessManager * manager = new QNetworkAccessManager();
    QEventLoop loop;

    QObject::connect(manager, SIGNAL(finished(QNetworkReply *)), &loop, SLOT(quit()));

    QNetworkReply * rep = manager->get(QNetworkRequest(QUrl(url)));
    loop.exec();

    QString replyString(rep->readAll());

    QJsonDocument jsonResponse = QJsonDocument::fromJson(replyString.toUtf8());
    QJsonObject jsonObj = jsonResponse.object();

    return jsonObj;
}

QString NodeAPIRequest::getNodeName(qint64 nodeId) {
    QString url = "http://localhost:8000/coord/" + QString::number(nodeId);
    QJsonObject reply = nodeAPIGetRequest(url);

    if (reply.contains("name")) {
        return reply["name"].toString();
    } else {
        return "Unnamed";
    }
}

QStringList NodeAPIRequest::getRouteInfo(int routeId) {
    QString url = "http://localhost:8000/route/" + QString::number(routeId);
    QJsonObject reply = nodeAPIGetRequest(url);

    QStringList info;

    info.push_back(reply["type"].toString());
    info.push_back(reply["name"].toString());
    info.push_back(reply["destination"].toString());

    return info;
}

void NodeAPIRequest::getNodeCoordinates(qint64 nodeId, qreal nodeCoordinate[2]) {
    QString url = "http://localhost:8000/coord/" + QString::number(nodeId);
    QJsonObject reply = nodeAPIGetRequest(url);

    nodeCoordinate[0] = reply["latitude"].toDouble();
    nodeCoordinate[1] = reply["longitude"].toDouble();
}

qint64 NodeAPIRequest::getNearestNodeId(qreal lat, qreal lon) {
    QString url = "http://localhost:8000/near/" + QString::number(lat) + "/" + QString::number(lon);
    QJsonObject reply = nodeAPIGetRequest(url);
    return qint64(reply["id"].toDouble());
}

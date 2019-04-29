#ifndef NODEAPIREQUEST_H
#define NODEAPIREQUEST_H

#include <QJsonArray>

class NodeAPIRequest
{
public:
    NodeAPIRequest();
    void getNodeCoordinates(qint64 nodeId, qreal nodeCoordinate[2]);
    qint64 getNearestNodeId(qreal lat, qreal lon);
    QString getNodeName(qint64 nodeId);
    QJsonObject nodeAPIGetRequest(QString url);
};

#endif // NODEAPIREQUEST_H

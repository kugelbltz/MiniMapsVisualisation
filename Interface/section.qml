import QtQuick 2.12
import QtLocation 5.6
import QtPositioning 5.6

Item {
    id: theObject;

    MapPolyline {
        id: polyLine;
        objectName: "polyLineName";
        line.width: 3;
    }

    function createStops() {
        var stops = [];
        var path = polyLine.path;
        for (var i = 0; i < path.length ; i++) {
            var lat = path[i]["latitude"];
            var lon = path[i]["longitude"];
            var color = polyLine.line.color;

            var qml = "import QtQuick 2.0; import QtLocation 5.6; import QtPositioning 5.6; MapCircle { radius: 15; border.width: 2; border.color: \"white\";color:\"white\"; center: QtPositioning.coordinate("+ lat + ", "+ lon +");}"

            var stop = Qt.createQmlObject(qml, theObject);
            stops.push(stop);
        }
        return stops;
    }
}

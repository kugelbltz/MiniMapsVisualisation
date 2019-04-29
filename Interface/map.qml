import QtQuick 2.0
import QtLocation 5.6
import QtPositioning 5.6
import QtQuick 2.12

Item {
    id: item
    width: 512
    height: 512
    visible: true
    signal mapPressed(var lat, var lon)

    Plugin {
        id: mapPlugin
        name: "osm"
    }

    Map {
        objectName: "mapObject"
        id: map
        anchors.fill: parent
        plugin: mapPlugin
        //center: QtPositioning.coordinate(48.86, 2.35) // Paris
        center: QtPositioning.coordinate(44.83, -0.58) // BDX
        zoomLevel: 12.4 // plus le chiffre est grand plus c'est zoomé

        MapQuickItem {
            id: start
            objectName: "start"
            visible: false
            coordinate: QtPositioning.coordinate(44.83, -0.58)
            anchorPoint.x: startImg.width/2
            anchorPoint.y: startImg.height - 5
            sourceItem: Image {
                id: startImg
                source: "qrc:/Icons/Ressources/marker48.png"
            }
        }

        MapQuickItem {
            id: end
            objectName: "end"
            visible: false
            coordinate: QtPositioning.coordinate(50.83, -0.58)
            anchorPoint.x: endImg.width/2
            anchorPoint.y: endImg.height - 5
            sourceItem: Image {
                id: endImg
                source: "qrc:/Icons/Ressources/marker48.png"
            }
        }

        function loadSection(c, p) { // Ici il faudrait ajouter le type, comme ca on aura une variable globale qui fera correspondre le type de transport a une couleu
            var component = Qt.createComponent("qrc:/Qml/section.qml")
            if (component.status === Component.Ready) {
                var section = component.createObject(map)
                section.children[0].line.color = c
                section.children[0].path = p

                // Centrer au milieu
                var midLat = (p[0]["latitude"] + p[p.length-1]["latitude"])/2;
                var midLon = (p[0]["longitude"] + p[p.length-1]["longitude"])/2;

                map.center = QtPositioning.coordinate(midLat,midLon);
                // Zoomer
                var point1 = QtPositioning.coordinate(p[0]["latitude"], p[0]["longitude"]);
                var point2 = QtPositioning.coordinate(p[p.length-1]["latitude"], p[p.length-1]["longitude"]);
                var dist = point1.distanceTo(point2) + 100;

                var myZoom = (dist + 7000) / 600;

                map.zoomLevel = myZoom;
                //var stops = section.createStops();

                map.addMapItem(section.children[0])
                for (var i = 0; i < stops.length; i++) {
                    map.addMapItem(stops[i]);
                }
              }
            }


        function deleteRoute() {
            var len = map.mapItems.length
            for (var i = 2; i < len; i++) {
                map.removeMapItem(map.mapItems[2]);
            }
        }

        MouseArea {
            anchors.fill: parent
            onPressed: {
                var lat = map.toCoordinate(Qt.point(mouse.x,mouse.y)).latitude
                var lon = map.toCoordinate(Qt.point(mouse.x,mouse.y)).longitude

                if (lat < 44.903 && lat > 44.776 && lon < -0.481 && lon > -0.687) {
                    item.mapPressed(lat, lon)
                    !(start.visible) ? start.visible = true : ((start.visible&&end.visible) ? end.visible = false : end.visible = true);
                    if (start.visible&&!end.visible) start.coordinate = QtPositioning.coordinate(lat, lon);
                    if (end.visible) end.coordinate = QtPositioning.coordinate(lat, lon);
                }
            }
        }
    }
}
//Ajouter un bouton pour revenir a la vue d'origine
// et des boutons pour zoomer et tout

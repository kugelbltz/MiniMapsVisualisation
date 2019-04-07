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
        zoomLevel: 13 // plus le chiffre est grand plus c'est zoomé

        MapQuickItem {
            id: start
            objectName: "start"
            visible: false
            coordinate: QtPositioning.coordinate(44.83, -0.58)
            anchorPoint.x: startImg.width/2
            anchorPoint.y: startImg.height - 5
            sourceItem: Image {
                id: startImg
                source: "qrc:/icons/Assets/marker48.png"
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
                source: "qrc:/icons/Assets/marker48.png"
            }
        }

        Rectangle {
            color: "red"
            height: 25
            width: 25
            radius:5
            x:0
            y:25

            MouseArea {
                anchors.fill: parent
                hoverEnabled: true;
                onHoveredChanged: { containsMouse ? parent.color = "lightsalmon" : parent.color = "red" }
            }
        }
        Rectangle {
            color: "blue"
            height: 25
            width: 25
            radius:5
            x:25
            y:50

            MouseArea {
                anchors.fill: parent
                hoverEnabled: true;
                onHoveredChanged: { containsMouse ? parent.color = "cadetblue" : parent.color = "blue" }
            }
        }
        Rectangle {
            color: "green"
            height: 25
            width: 25
            radius:5
            x:25
            y:0

            MouseArea {
                anchors.fill: parent
                hoverEnabled: true;
                onHoveredChanged: { containsMouse ? parent.color = "darkseagreen" : parent.color = "green" }
            }
        }
        Rectangle {
            id : right
            color: "yellow"
            height: 25
            width: 25
            radius:5
            x:50
            y:25

            MouseArea {
                anchors.fill: right
                hoverEnabled: true;
                onHoveredChanged: { containsMouse ? focus="true" : parent.color = "yellow" }
                onClicked: {map.pan(100,0)}
            }
        }

        function loadSection(c, p) { // Ici il faudrait ajouter le type, comme ca on aura une variable globale qui fera correspondre le type de transport a une couleu
            var component = Qt.createComponent("section.qml")
            if (component.status === Component.Ready) {
                var section = component.createObject(map)
                section.line.color = c
                section.path = p
                map.addMapItem(section)
            }
        }

        function loadRoute(paths) {
            for (var i = 0; i < paths.length; i++) {
                loadSection("red", paths[i])
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

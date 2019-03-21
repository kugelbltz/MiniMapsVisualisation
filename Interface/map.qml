import QtQuick 2.0
import QtLocation 5.6
import QtPositioning 5.6
import QtQuick 2.12

Item {
    width: 512
    height: 512
    visible: true

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
        zoomLevel: 5 // plus le chiffre est grand plus c'est zoomé

        function loadSection(c, p) { // Ici il faudrait ajouter le type, comme ca on aura une variable globale qui fera correspondre le type de transport a une couleur
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
            clearMapItems(map.mapItems)
        }

        /*
        Component.onCompleted: {
            loadRoute([
                                             [
                                               { latitude: -27, longitude: 153.0 },
                                               { latitude: -27, longitude: 154.1 },
                                               { latitude: -28, longitude: 153.5 },
                                               { latitude: -29, longitude: 153.5 }
                                             ],
                                             [
                                                 {latitude : 48.86, longitude : 2.35},
                                                 {latitude : 44.83, longitude : -0.58}
                                             ]
                                         ])
            deleteRoute()
        }
      }
      */

    }
}

//Ajouter un bouton pour revenir a la vue d'origine
// et des boutons pour zoomer et tout

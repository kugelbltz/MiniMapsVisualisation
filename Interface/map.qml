import QtQuick 2.0
import QtQuick.Window 2.0
import QtLocation 5.6
import QtPositioning 5.6

Item {
    width: 512
    height: 512
    visible: true

    Plugin {
        id: mapPlugin
        name: "osm" // "mapboxgl", "esri", ...
        // specify plugin parameters if necessary
        // PluginParameter {
        //     name:
        //     value:
        // }
    }

    Map {
        anchors.fill: parent
        plugin: mapPlugin
        //center: QtPositioning.coordinate(48.86, 2.35) // Paris
        center: QtPositioning.coordinate(44.83, -0.58) // BDX
        zoomLevel: 5 // plus le chiffre est grand plus c'est zoome



        /*
        MapCircle {
            color:"cadetblue"
            //center: QtPositioning.coordinate(48.86, 2.35) // Paris
            center: QtPositioning.coordinate(44.83, -0.58) // BDX
            radius:50000 //en metre
            //border.width: 10;
            border.color: 'cadetblue'

        }
        */

    }
}

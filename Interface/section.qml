import QtQuick 2.12
import QtLocation 5.6
import QtPositioning 5.6

    MapPolyline {
            line.width: 3
            //line.color: "steelblue"
            /*
            path: [
                { latitude: -27, longitude: 153.0 },
                { latitude: -27, longitude: 154.1 },
                { latitude: -28, longitude: 153.5 },
                { latitude: -29, longitude: 153.5 }
            ]
            */

            MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true;
                    onHoveredChanged: { containsMouse ? parent.line.width = 10 : parent.line.width = 3 }
                }


        }

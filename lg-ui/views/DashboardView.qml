import QtQuick 2.9
import assets 1.0

Item {
    Rectangle {
      anchors.fill: parent
      color: Style.colourBackground
      Text {
        id: recText
        text: qsTr("Inicio")
      }
    }
}

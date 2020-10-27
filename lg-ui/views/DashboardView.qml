import QtQuick 2.9
import assets 1.0

Item {
    Rectangle {
      anchors.fill: parent
      // color: Style.colourBackground
      color: "#111111"
      Text {
        id: recText
        color: "#dddddd"
        text: qsTr("Inicio")
      }
    }
}

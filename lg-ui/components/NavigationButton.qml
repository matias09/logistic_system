import QtQuick 2.9
import assets 1.0

Item {
    property alias iconCharacter: textIcon.text
    property alias description: textDescription.text
    property color  hoverColour: Style.colourNavigationBarBackground

    signal navigationButtonClicked()

    width: parent.width
    height: Style.heightNavigationButton

  Rectangle {
    id: background
    anchors.fill: parent
    color: Style.colourNavigationBarBackground

    Row {
      Text {
        id: textIcon

        width: Style.widthNavigationButtonIcon
        height: Style.heightNavigationButtonIcon

        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter

        font {
          family: Style.fontAwesome
          pixelSize: 42
        }
        color: Style.colourNavigationBarFront
        text: "\uf11a"
      }

      Text {
        id: textDescription

        width: Style.widthNavigationButtonDescription
        height: Style.heightNavigationButtonDescription
        verticalAlignment: Text.AlignVCenter

        font.pixelSize: Style.pixelSizeNavigationBarText
        color:  Style.colourNavigationBarFront
        text: "SET ME !!"
      }
    }

    MouseArea {
      anchors.fill: parent
      cursorShape:  Qt.PointingHandCursor
      hoverEnabled: true
      onEntered: background.state = "hover"
      onExited: background.state = ""
      onClicked: navigationButtonClicked()
    }

    states: [
      State {
        name: "hover"
        PropertyChanges {
            target: background
            color: hoverColour
        }
      }
    ]
  }
}

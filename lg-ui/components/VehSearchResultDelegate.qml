import QtQuick 2.9
import assets  1.0
import LG      1.0

Item {
  property Vehicle vehicle

  implicitWidth:  parent.width
  implicitHeight: Math.max(
       vehicleColumn.implicitHeight, textModel.implicitHeight)
     + ( Style.heightDataControls / 2 )

  Rectangle {
    id: background
    width:  parent.width
    height: parent.height
    color: Style.colourPanelBackground

      Column {
        id: vehicleColumn
        width: parent / 2
        anchors {
          left:   parent.left
          top:    parent.top
          right:    parent.right

          margins: Style.heightDataControls / 4
        }
        spacing: Style.heightDataControls / 2

      Text {
        id: textId
        anchors.left: parent.left
        text:   vehicle.ui_reference.ui_label + ": "
              + vehicle.ui_reference.ui_value

        font.pixelSize: Style.pixelSizeDataControls
        color: Style.colourPanelFont
      }

      Text {
        id: textType
        anchors {
          top: textId.bottom
          left: parent.left
          topMargin: 10
        }
        text:   vehicle.ui_type.ui_label + ": "
              + vehicle.ui_type.ui_value

        font.pixelSize: Style.pixelSizeDataControls
        color: Style.colourPanelFont
      }

      Text {
        id: textModel
        anchors {
          top:   textId.top
          right: parent.right

          rightMargin: Style.heightDataControls / 4
        }
        text: vehicle.ui_model
        font.pixelSize: Style.pixelSizeDataControls
        color: Style.colourPanelFont
        horizontalAlignment: Text.AlignRight
      }
    }

    Rectangle {
      id: borderBottom
      anchors {
        bottom: parent.bottom
        left:   parent.left
        right:  parent.right
      }
      height: 1
      color: Style.colourPanelFont
    }

    MouseArea {
      anchors.fill: parent
      cursorShape: Qt.PointingHandCursor
      hoverEnabled: true
      onEntered: background.state = "hover"
      onExited:  background.state = ""
      onClicked: masterController.selectVehicle( vehicle )
    }

    states: [
      State {
        name: "hover"
        PropertyChanges {
          target: background
          color: Style.colourPanelBackgroundHover
        }
      }
    ]
  }
}

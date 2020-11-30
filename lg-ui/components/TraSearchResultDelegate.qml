import QtQuick 2.9
import assets  1.0
import LG      1.0

Item {
  property Travel travel

  implicitWidth:  parent.width
  implicitHeight: 90

  Rectangle {
    id: background
    width:  parent.width
    height: parent.height
    color: Style.colourPanelBackground

      Column {
        id: travelColumn
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
          anchors {
            top: travelColumn.bottom
            left: parent.left
          }
          text:   travel.ui_reference.ui_label + ": "
                + travel.ui_reference.ui_value

          font.pixelSize: Style.pixelSizeDataControls
          color: Style.colourPanelFont
        }

        Text {
          id: textClient
          anchors {
            top:   textId.bottom
            left:  parent.left

            rightMargin: Style.heightDataControls / 4
          }
          text:   travel.ui_id_cli.ui_label + ": "
                + travel.ui_cli.ui_value
          font.pixelSize: Style.pixelSizeDataControls
          color: Style.colourPanelFont
        }

        Text {
          id: textFullAddress
          anchors {
            top:   textClient.bottom
            left:  parent.left

            rightMargin: Style.heightDataControls / 4
          }
          text:  "Direccion Completa: " + travel.ui_destiny.ui_address.ui_fullAddress
          font.pixelSize: Style.pixelSizeDataControls
          color: Style.colourPanelFont
        }

        Text {
          id: textState
          anchors {
            top:   textFullAddress.bottom
            left:  parent.left

            rightMargin: Style.heightDataControls / 4
          }
          text:   travel.ui_destiny.ui_address.ui_state.ui_label + ": "
                + travel.ui_destiny.ui_address.ui_state.ui_value
          font.pixelSize: Style.pixelSizeDataControls
          color: Style.colourPanelFont
        }

        Text {
          id: textVehicle
          anchors {
            top:   textDriver.bottom
            left:  parent.left

            rightMargin: Style.heightDataControls / 4
          }
          text:   travel.ui_destiny.ui_id_veh.ui_label + ": "
                + travel.ui_destiny.ui_id_veh.ui_value
          font.pixelSize: Style.pixelSizeDataControls
          color: Style.colourPanelFont
        }


      Text {
        id: textAddress
        anchors {
          top:   textId.top
          right: parent.right

          rightMargin: Style.heightDataControls / 4
        }
        text: "Direccion completa: "
              + travel.ui_destiny.ui_address.ui_fullAddress
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
      onClicked: masterController.selectTravel( travel )
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

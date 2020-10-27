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
          anchors.left: parent.left
          text:   travel.ui_reference.ui_label + ": "
                + travel.ui_reference.ui_value

          font.pixelSize: Style.pixelSizeDataControls
          color: Style.colourPanelFont
        }

        Text {
          id: textBrand
          anchors {
            top:   textType.bottom
            left:  parent.left

            rightMargin: Style.heightDataControls / 4
          }
          text:   travel.ui_destiny.ui_address.ui_fullAddress.ui_label + ": "
                + travel.ui_destiny.ui_address.ui_fullAddress.ui_value
          font.pixelSize: Style.pixelSizeDataControls
          color: Style.colourPanelFont
          //horizontalAlignment: Text.AlignRight
        }

        Text {
          id: textType
          anchors {
            top: textId.bottom
            left: parent.left
          }
          text:   travel.ui_sta_date.ui_label + ": "
                + travel.ui_sta_date.ui_value

          font.pixelSize: Style.pixelSizeDataControls
          color: Style.colourPanelFont
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

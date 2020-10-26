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
        id: textType
        anchors {
          top: textId.bottom
          left: parent.left
        }
        text:   travel.ui_type.ui_label + ": "
              + travel.ui_type.ui_value

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
        text:   travel.ui_brand.ui_label + ": "
              + travel.ui_brand.ui_value
        font.pixelSize: Style.pixelSizeDataControls
        color: Style.colourPanelFont
        //horizontalAlignment: Text.AlignRight
      }

      Text {
        id: textModel
        anchors {
          top:   textBrand.bottom
          left:  parent.left

          rightMargin: Style.heightDataControls / 4
        }
        text:   travel.ui_model.ui_label + ": "
              + travel.ui_model.ui_value
        font.pixelSize: Style.pixelSizeDataControls
        color: Style.colourPanelFont
        //horizontalAlignment: Text.AlignRight
      }

      Text {
        id: textMaxWeight
        anchors {
          top:   parent.bottom
          right: parent.right

          rightMargin: Style.heightDataControls / 4
        }
        text:   travel.ui_max_w.ui_label + ": "
              + travel.ui_max_w.ui_value
        font.pixelSize: Style.pixelSizeDataControls
        color: Style.colourPanelFont
        horizontalAlignment: Text.AlignRight
      }

      Text {
        id: textVin
        anchors {
          top:   textMaxWeight.bottom
          right: parent.right

          rightMargin: Style.heightDataControls / 4
        }
        text:   travel.ui_vin.ui_label + ": "
              + travel.ui_vin.ui_value
        font.pixelSize: Style.pixelSizeDataControls
        color: Style.colourPanelFont
        horizontalAlignment: Text.AlignRight
      }

      Text {
        id: textVinCad
        anchors {
          top:   textVin.bottom
          right: parent.right

          rightMargin: Style.heightDataControls / 4
        }
        text:   travel.ui_vin_cad.ui_label + ": "
              + travel.ui_vin_cad.ui_value
        font.pixelSize: Style.pixelSizeDataControls
        color: Style.colourPanelFont
        horizontalAlignment: Text.AlignRight
      }

      Text {
        id: textYear
        anchors {
          top:   textVinCad.bottom
          right: parent.right

          rightMargin: Style.heightDataControls / 4
        }
        text:   travel.ui_year.ui_label + ": "
              + travel.ui_year.ui_value
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

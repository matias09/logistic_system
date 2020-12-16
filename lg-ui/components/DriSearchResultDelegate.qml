import QtQuick 2.9
import assets  1.0
import LG      1.0

Item {
  property Driver driver

  implicitWidth:  parent.width
  implicitHeight: Math.max(
       driverColumn.implicitHeight, textAddress.implicitHeight)
     + ( Style.heightDataControls )

  Rectangle {
    id: background
    width:  parent.width
    height: parent.height
    color: Style.colourPanelBackground

      Column {
        id: driverColumn
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
        text:   driver.ui_reference.ui_label + ": "
              + driver.ui_reference.ui_value

        font.pixelSize: Style.pixelSizeDataControls
        color: Style.colourPanelFont
      }

      Text {
        id: textName
        anchors {
          top: textId.bottom
          left: parent.left
        }
        text:   driver.ui_name.ui_label + ": "
              + driver.ui_name.ui_value

        font.pixelSize: Style.pixelSizeDataControls
        color: Style.colourPanelFont
      }

      Text {
        id: textNroTra
        anchors {
          top: textName.bottom
          left: parent.left
        }
        text:   driver.ui_nro_tra.ui_label + ": "
              + driver.ui_nro_tra.ui_value

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
        text: driver.ui_driverAddress.ui_fullAddress
        font.pixelSize: Style.pixelSizeDataControls
        color: Style.colourPanelFont
        horizontalAlignment: Text.AlignRight
      }

      Text {
        id: textLicNro
        anchors {
          top:   textAddress.bottom
          right: parent.right

          rightMargin: Style.heightDataControls / 4
        }
        text: driver.ui_lic_nro.ui_label + ": "
            + driver.ui_lic_nro.ui_value
        font.pixelSize: Style.pixelSizeDataControls
        color: Style.colourPanelFont
        horizontalAlignment: Text.AlignRight
      }

      Text {
        id: textLicCad
        anchors {
          top:   textLicNro.bottom
          right: parent.right

          rightMargin: Style.heightDataControls / 4
        }
        text:  driver.ui_lic_cad.ui_label + ": "
             + Qt.formatDate(driver.ui_lic_cad.ui_value, "yyyy-MM-dd")
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
      onClicked: masterController.selectDriver( driver )
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

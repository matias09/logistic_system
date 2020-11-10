import QtQuick 2.9
import QtQuick.Controls 2.2
import LG 1.0
import assets 1.0

Item {
  Flow {
    Rectangle {
      width: Style.widthDataControls
      height: Style.heightDataControls
      color: Style.colourBackground

      Text {
        id: textLabel
        anchors {
          fill: parent
          margins: Style.heightDataControls / 4
        }
        text: address.ui_id_state.ui_label
        color: Style.colourDataControlsFont
        font.pixelSize: Style.pixelSizeDataControls
        verticalAlignment: Qt.AlignVCenter
      }
    }

    Rectangle {
      id: background
      width: Style.widthDataControls
      height: Style.heightDataControls
      border {
        width: 1
        color: Style.colourDataControlsFont
      }

      ComboBox {
        id: state

        anchors { fill: parent }

        valueRole: "ui_value"
        textRole: "ui_desc"
        model: masterController.ui_states

        onActivated: {
          address.ui_id_state.ui_value = currentValue
        }

        Component.onCompleted: {
          currentIndex = ( address.ui_id_state.ui_value  )
          ?  address.ui_id_state.ui_value - 1
          :  indexOfValue(1)
          address.ui_id_state.ui_value = currentValue
        }
      }
    }
  }
}

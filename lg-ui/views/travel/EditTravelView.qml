import QtQuick 2.9
import QtQuick.Controls 2.2
import LG 1.0
import assets 1.0
import components 1.0

Item {
    property Travel selectedTravel
    Component.onCompleted:
      masterController.ui_traCommandController.setSelectedTravel(selectedTravel)

    Rectangle {
      anchors.fill: parent
      color: Style.colourBackground
    }

    ScrollView {
      id: scrollView
      anchors {
        left:      parent.left
        right:     parent.right
        top:       parent.top
        bottom:    commandBar.top

        margins:   Style.sizeScreenMargin
      }
      clip: true

      Column {
        spacing:  Style.sizeScreenMargin
        width: scrollView.width

        Panel {
        headerText: "Detalles del Viaje"
          contentComponent:
            Column {
              spacing: Style.sizeControlSpacing

              StringEditorSingleLine {
                stringDecorator: selectedTravel.ui_reference
                anchors {
                  left: parent.left
                  right: parent.right
                }
                enabled: false
              }

              StringEditorSingleLine {
                stringDecorator: selectedTravel.ui_id_cli
                anchors {
                  left: parent.left
                  right: parent.right
                }
              }

              StringEditorSingleLine {
                stringDecorator: selectedTravel.ui_sta_date
                anchors {
                  left: parent.left
                  right: parent.right
                }
              }

              StringEditorSingleLine {
                stringDecorator: selectedTravel.ui_destiny.ui_id_dri
                anchors {
                  left: parent.left
                  right: parent.right
                }
              }

              StringEditorSingleLine {
                stringDecorator: selectedTravel.ui_destiny.ui_id_veh
                anchors {
                  left: parent.left
                  right: parent.right
                }
              }

              StringEditorSingleLine {
                stringDecorator: selectedTravel.ui_destiny.ui_arr_date
                anchors {
                  left: parent.left
                  right: parent.right
                }
              }
            }
          }

        AddressEditor {
          address: selectedTravel.ui_destiny.ui_address
          headerText: "Direccion de Destino"
        }

        Rectangle {
          id: recErr
          visible: (selectedTravel.ui_destiny.ui_err.ui_value !== "")
                    ? true : false;

          anchors {
            left: parent.left
            right: parent.right
          }

          width: Style.widthDataControls
          height: Style.heightDataControls
          color: "#ca4949"

          Text {
              id: errMessages

              anchors.fill: parent
              verticalAlignment: Text.AlignVCenter

              text: selectedTravel.ui_destiny.ui_err.ui_value
              font.bold: true
              color: "#444444"
          }
        }

      }
  }

  CommandBar {
    id: commandList
    commandList:
      masterController.ui_traCommandController.ui_editTravelViewContextCommands
  }
}


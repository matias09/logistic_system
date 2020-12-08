import QtQuick 2.9
import QtQuick.Controls 1.4
import QtQuick.Controls 2.2
import LG 1.0
import assets 1.0
import components 1.0

Item {
  property Vehicle newVehicle: masterController.ui_newVehicle

  Column {
    spacing:  Style.sizeScreenMargin
    anchors {
      left:      parent.left
      right:     parent.right
      top:       parent.top
      margins:   Style.sizeScreenMargin
    }

    ScrollView {
      width:  900
      height: 600
      clip: true

      ScrollBar.vertical.policy: ScrollBar.AlwaysOn

    Panel {
      headerText: "Detalles del Vehiculo"
      contentComponent:
      Column {
        spacing: Style.sizeControlSpacing


        Flow {
          Rectangle {
            width: Style.widthDataControls
            height: Style.heightDataControls
            color: Style.colourBackground

            Text {
              id: types_textLabel
              anchors {
                fill: parent
                margins: Style.heightDataControls / 4
              }
              text: newVehicle.ui_id_type.ui_label
              color: Style.colourDataControlsFont
              font.pixelSize: Style.pixelSizeDataControls
              verticalAlignment: Qt.AlignVCenter
            }
          }

          Rectangle {
            id: types_background
            width: Style.widthDataControls
            height: Style.heightDataControls
            border {
              width: 1
              color: Style.colourDataControlsFont
            }

            ComboBox {
              id: types

              anchors { fill: parent }

              valueRole: "ui_value"
              textRole: "ui_desc"
              model: masterController.ui_vehCommandController.ui_types

              onActivated: {
                newVehicle.ui_id_type.ui_value = currentValue
              }

              Component.onCompleted: {
                currentIndex = ( newVehicle.ui_id_type.ui_value  )
                ?  newVehicle.ui_id_type.ui_value - 1
                :  indexOfValue(1)
                newVehicle.ui_id_type.ui_value = currentValue
              }
            }
          }
        }




        Flow {
          Rectangle {
            width: Style.widthDataControls
            height: Style.heightDataControls
            color: Style.colourBackground

            Text {
              id: brands_textLabel
              anchors {
                fill: parent
                margins: Style.heightDataControls / 4
              }
              text: newVehicle.ui_id_brand.ui_label
              color: Style.colourDataControlsFont
              font.pixelSize: Style.pixelSizeDataControls
              verticalAlignment: Qt.AlignVCenter
            }
          }

          Rectangle {
            id: brands_background
            width: Style.widthDataControls
            height: Style.heightDataControls
            border {
              width: 1
              color: Style.colourDataControlsFont
            }

            ComboBox {
              id: brands

              anchors { fill: parent }

              valueRole: "ui_value"
              textRole: "ui_desc"
              model: masterController.ui_vehCommandController.ui_brands

              onActivated: {
                newVehicle.ui_id_brand.ui_value = currentValue
                masterController.ui_vehCommandController.onBrandsChanged(currentValue)
                models.model = masterController.ui_vehCommandController.ui_models
              }

              Component.onCompleted: {
                currentIndex = ( newVehicle.ui_id_brand.ui_value  )
                ?  newVehicle.ui_id_brand.ui_value - 1
                :  indexOfValue(1)
                newVehicle.ui_id_brand.ui_value = currentValue

                masterController.ui_vehCommandController.onBrandsChanged(currentValue)
                models.model = masterController.ui_vehCommandController.ui_models
              }
            }
          }
        }


        Flow {
          Rectangle {
            width: Style.widthDataControls
            height: Style.heightDataControls
            color: Style.colourBackground

            Text {
              id: models_textLabel
              anchors {
                fill: parent
                margins: Style.heightDataControls / 4
              }
              text: newVehicle.ui_id_model.ui_label
              color: Style.colourDataControlsFont
              font.pixelSize: Style.pixelSizeDataControls
              verticalAlignment: Qt.AlignVCenter
            }
          }

          Rectangle {
            id: models_background
            width: Style.widthDataControls
            height: Style.heightDataControls
            border {
              width: 1
              color: Style.colourDataControlsFont
            }

            ComboBox {
              id: models

              anchors { fill: parent }

              valueRole: "ui_value"
              textRole: "ui_desc"

              onActivated: {
                newVehicle.ui_id_model.ui_value = currentValue
              }

              Component.onCompleted: {
                currentIndex = ( newVehicle.ui_id_model.ui_value  )
                ?  newVehicle.ui_id_model.ui_value - 1
                :  indexOfValue(1)
                newVehicle_ui_id_model.ui_value = currentValue
              }
            }
          }
        }

        StringEditorSingleLine {
          stringDecorator: newVehicle.ui_name
          anchors {
            left: parent.left
            right: parent.right
          }
        }

        Flow {
          id: vincadFlow

          Rectangle {
            id: vincadLabelBackground
            width: Style.widthDataControls
            height: Style.heightDataControls
            color: Style.colourBackground

            Text {
              id: vincadDateLabel
              anchors {
                fill: parent
                margins: Style.heightDataControls / 4
              }
              text: newVehicle.ui_vin_cad.ui_label
              color: Style.colourDataControlsFont
              font.pixelSize: Style.pixelSizeDataControls
              verticalAlignment: Qt.AlignVCenter
            }

            CheckBox {
              id: vincadCalEnable
              checked: false

              anchors {
                right: vincadLabelBackground.right
                margins: Style.heightDataControls / 4
              }
            }
          }

          Rectangle {
            id: vincadValueBackground
            width: Style.widthDataControls
            height: Style.heightDataControls
            color: Style.colourDataControlsBackground
            border {
              width: 1
              color: Style.colourDataControlsFont
            }

            TextInput {
              id: vincadtextValue
              enabled: false
              anchors {
                fill:parent
                margins: Style.heightDataControls / 4
              }
              text: Qt.formatDate(newVehicle.ui_vin_cad.ui_value
                                , "yyyy-MM-dd")
              color: Style.colourDataControlsFont
              font.pixelSize: Style.pixelSizeDataControls
              verticalAlignment: Qt.AlignVCenter
            }
          }
        }

        Calendar {
          visible: vincadCalEnable.checked
          minimumDate: new Date(2020, 0, 1)
          maximumDate: new Date(2025, 0, 1)

          anchors {
            horizontalCenter: vincadFlow.horizontalCenter
            margins: Style.heightDataControls / 4
          }

          onClicked: {
            newVehicle.ui_vin_cad.ui_value = selectedDate
            vincadCalEnable.checked = false
          }

          Component.onCompleted: {
            newVehicle.ui_vin_cad.ui_value = selectedDate
          }
        }

        Flow {
          id: yearFlow

          Rectangle {
            id: yearLabelBackground
            width: Style.widthDataControls
            height: Style.heightDataControls
            color: Style.colourBackground

            Text {
              id: yearDateLabel
              anchors {
                fill: parent
                margins: Style.heightDataControls / 4
              }
              text: newVehicle.ui_year.ui_label
              color: Style.colourDataControlsFont
              font.pixelSize: Style.pixelSizeDataControls
              verticalAlignment: Qt.AlignVCenter
            }

            CheckBox {
              id: yearCalEnable
              checked: false

              anchors {
                right: yearLabelBackground.right
                margins: Style.heightDataControls / 4
              }
            }
          }

          Rectangle {
            id: yearValueBackground
            width: Style.widthDataControls
            height: Style.heightDataControls
            color: Style.colourDataControlsBackground
            border {
              width: 1
              color: Style.colourDataControlsFont
            }

            TextInput {
              id: yeartextValue
              enabled: false
              anchors {
                fill:parent
                margins: Style.heightDataControls / 4
              }
              text: Qt.formatDate(newVehicle.ui_year.ui_value
                                , "yyyy-MM-dd")
              color: Style.colourDataControlsFont
              font.pixelSize: Style.pixelSizeDataControls
              verticalAlignment: Qt.AlignVCenter
            }
          }
        }

        Calendar {
          visible: yearCalEnable.checked
          minimumDate: new Date(1980, 0, 1)
          maximumDate: new Date(2025, 0, 1)

          anchors {
            horizontalCenter: yearFlow.horizontalCenter
            margins: Style.heightDataControls / 4
          }

          onClicked: {
            newVehicle.ui_year.ui_value = selectedDate
            yearCalEnable.checked = false
          }

          Component.onCompleted: {
            newVehicle.ui_year.ui_value = selectedDate
          }
        }

        StringEditorSingleLine {
          stringDecorator: newVehicle.ui_max_w
          anchors {
            left: parent.left
            right: parent.right
          }
        }

        StringEditorSingleLine {
          stringDecorator: newVehicle.ui_vin
          anchors {
            left: parent.left
            right: parent.right
          }
        }
      }

      }
    }
  }

  CommandBar {
    id: commandList
    commandList:
    masterController.ui_vehCommandController.ui_createVehicleViewContextCommands
  }
}

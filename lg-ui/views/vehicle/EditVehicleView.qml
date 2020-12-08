import QtQuick 2.9
import QtQuick.Controls 1.4
import QtQuick.Controls 2.2
import LG 1.0
import assets 1.0
import components 1.0

Item {
  property Vehicle selectedVehicle
  Component.onCompleted:
  masterController.ui_vehCommandController.setSelectedVehicle(selectedVehicle)

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
      height: 700
      clip: true

      ScrollBar.vertical.policy: ScrollBar.AlwaysOn

      Panel {
        headerText: "Detalles del Vehiculo"
        contentComponent:
        Column {
          spacing: Style.sizeControlSpacing


          StringEditorSingleLine {
            stringDecorator: selectedVehicle.ui_reference
            anchors {
              left: parent.left
              right: parent.right
            }
            enabled: false
          }


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
                text: selectedVehicle.ui_id_type.ui_label
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
                  selectedVehicle.ui_id_type.ui_value = currentValue
                }

                Component.onCompleted: {
                  currentIndex = ( selectedVehicle.ui_id_type.ui_value  )
                  ?  selectedVehicle.ui_id_type.ui_value - 1
                  :  indexOfValue(1)
                  selectedVehicle.ui_id_type.ui_value = currentValue
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
                text: selectedVehicle.ui_id_brand.ui_label
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
                  selectedVehicle.ui_id_brand.ui_value = currentValue
                  masterController.ui_vehCommandController.onBrandsChanged(currentValue)
                  models.model = masterController.ui_vehCommandController.ui_models
                }

                Component.onCompleted: {
                  currentIndex = ( selectedVehicle.ui_id_brand.ui_value  )
                  ?  indexOfValue(selectedVehicle.ui_id_brand.ui_value)
                  :  indexOfValue(1)
                  selectedVehicle.ui_id_brand.ui_value = currentValue

                  masterController.ui_vehCommandController.onBrandsChanged(currentValue)
                  models.model = masterController.ui_vehCommandController.ui_models

                  models.currentIndex = models.indexOfValue(selectedVehicle.ui_id_model.ui_value)
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
                text: selectedVehicle.ui_id_model.ui_label
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
                  selectedVehicle.ui_id_model.ui_value = currentValue
                }
              }
            }
          }


          StringEditorSingleLine {
            stringDecorator: selectedVehicle.ui_name
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
                text: selectedVehicle.ui_vin_cad.ui_label
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
                text: Qt.formatDate(selectedVehicle.ui_vin_cad.ui_value
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

            selectedDate: selectedVehicle.ui_vin_cad.ui_value

            onClicked: {
              selectedVehicle.ui_vin_cad.ui_value = selectedDate
              vincadCalEnable.checked = false
            }

            Component.onCompleted: {
              selectedVehicle.ui_vin_cad.ui_value = selectedDate
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
                text: selectedVehicle.ui_year.ui_label
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
                text: Qt.formatDate(selectedVehicle.ui_year.ui_value
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

            selectedDate: selectedVehicle.ui_year.ui_value

            onClicked: {
              selectedVehicle.ui_year.ui_value = selectedDate
              yearCalEnable.checked = false
            }

            Component.onCompleted: {
              selectedVehicle.ui_year.ui_value = selectedDate
            }
          }

          StringEditorSingleLine {
            stringDecorator: selectedVehicle.ui_max_w
            anchors {
              left: parent.left
              right: parent.right
            }
          }

          StringEditorSingleLine {
            stringDecorator: selectedVehicle.ui_vin
            anchors {
              left: parent.left
              right: parent.right
            }
          }
        }
      }
    }

    Rectangle {
      id: recErr
      visible: (selectedVehicle.ui_err.ui_value !== "")
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

        text: selectedVehicle.ui_err.ui_value
        font.bold: true
        color: "#444444"
      }
    }
  }

  CommandBar {
    id: commandList
    commandList:
    masterController.ui_vehCommandController.ui_editVehicleViewContextCommands
  }
}


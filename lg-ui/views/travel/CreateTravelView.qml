import QtQuick 2.9
import QtQuick.Controls 1.4
import QtQuick.Controls 2.8
import LG 1.0
import assets 1.0
import components 1.0

Item {
    property Travel newTravel: masterController.ui_newTravel

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
      height: 300
      clip: true

      ScrollBar.vertical.policy: ScrollBar.AlwaysOn

      Panel {
        headerText: "Travel Details"
        contentComponent:
          Column {
            spacing: Style.sizeControlSpacing


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
                    text: newTravel.ui_id_cli.ui_label
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
                    id: client

                    anchors { fill: parent }

                    valueRole: "ui_value"
                    textRole: "ui_desc"
                    model: masterController.ui_traCommandController.ui_clients

                    onActivated: {
                      newTravel.ui_id_cli.ui_value = currentValue
                    }

                    Component.onCompleted: {
                      currentIndex = 0
                      newTravel.ui_id_cli.ui_value = currentValue
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
                    id: dritextLabel
                    anchors {
                      fill: parent
                      margins: Style.heightDataControls / 4
                    }
                    text: newTravel.ui_destiny.ui_id_dri.ui_label
                    color: Style.colourDataControlsFont
                    font.pixelSize: Style.pixelSizeDataControls
                    verticalAlignment: Qt.AlignVCenter
                  }
                }

                Rectangle {
                  id: dribackground
                  width: Style.widthDataControls
                  height: Style.heightDataControls
                  border {
                    width: 1
                    color: Style.colourDataControlsFont
                  }

                  ComboBox {
                    id: driver

                    anchors { fill: parent }

                    valueRole: "ui_value"
                    textRole: "ui_desc"
                    model: masterController.ui_traCommandController.ui_drivers

                    onActivated: {
                      newTravel.ui_destiny.ui_id_dri.ui_value = currentValue
                    }

                    Component.onCompleted: {
                      currentIndex = 0
                      newTravel.ui_destiny.ui_id_dri.ui_value = currentValue
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
                    id: vehtextLabel
                    anchors {
                      fill: parent
                      margins: Style.heightDataControls / 4
                    }
                    text: newTravel.ui_destiny.ui_id_veh.ui_label
                    color: Style.colourDataControlsFont
                    font.pixelSize: Style.pixelSizeDataControls
                    verticalAlignment: Qt.AlignVCenter
                  }
                }

                Rectangle {
                  id: vehbackground
                  width: Style.widthDataControls
                  height: Style.heightDataControls
                  border {
                    width: 1
                    color: Style.colourDataControlsFont
                  }

                  ComboBox {
                    id: vehicle

                    anchors { fill: parent }

                    valueRole: "ui_value"
                    textRole: "ui_desc"
                    model: masterController.ui_traCommandController.ui_vehicles

                    onActivated: {
                      newTravel.ui_destiny.ui_id_veh.ui_value = currentValue
                    }

                    Component.onCompleted: {
                      currentIndex = 0
                      newTravel.ui_destiny.ui_id_veh.ui_value = currentValue
                    }
                  }
                }
              }

            Flow {
              id: staDateFlow

              Rectangle {
                id: staDateLabelBackground
                width: Style.widthDataControls
                height: Style.heightDataControls
                color: Style.colourBackground

                  Text {
                    id: staDateLabel
                    anchors {
                      fill: parent
                      margins: Style.heightDataControls / 4
                    }
                    text: newTravel.ui_sta_date.ui_label
                    color: Style.colourDataControlsFont
                    font.pixelSize: Style.pixelSizeDataControls
                    verticalAlignment: Qt.AlignVCenter
                  }

                  CheckBox {
                    id: staCalEnable
                    checked: false

                    anchors {
                      right: staDateLabelBackground.right
                      margins: Style.heightDataControls / 4
                    }
                  }
                }

                Rectangle {
                  id: licValueBackground
                  width: Style.widthDataControls
                  height: Style.heightDataControls
                  color: Style.colourDataControlsBackground
                  border {
                    width: 1
                    color: Style.colourDataControlsFont
                  }

                  TextInput {
                    id: statextValue
                    enabled: false
                    anchors {
                      fill:parent
                      margins: Style.heightDataControls / 4
                    }
                    text: Qt.formatDate(newTravel.ui_sta_date.ui_value
                                      , "yyyy-MM-dd")
                    color: Style.colourDataControlsFont
                    font.pixelSize: Style.pixelSizeDataControls
                    verticalAlignment: Qt.AlignVCenter
                  }
                }
              }

              Calendar {
                  visible: staCalEnable.checked
                  minimumDate: new Date(2020, 0, 1)
                  maximumDate: new Date(2025, 0, 1)

                  anchors {
                    horizontalCenter: staDateFlow.horizontalCenter
                    margins: Style.heightDataControls / 4
                  }

                  onClicked: {
                    newTravel.ui_sta_date.ui_value = selectedDate
                    staCalEnable.checked = false
                  }

                  Component.onCompleted: {
                    newTravel.ui_sta_date.ui_value = selectedDate
                  }
              }


            Flow {
              id: arrFlow

              Rectangle {
                id: arrLabelBackground
                width: Style.widthDataControls
                height: Style.heightDataControls
                color: Style.colourBackground

                  Text {
                    id: arrDateLabel
                    anchors {
                      fill: parent
                      margins: Style.heightDataControls / 4
                    }
                    text: newTravel.ui_destiny.ui_arr_date.ui_label
                    color: Style.colourDataControlsFont
                    font.pixelSize: Style.pixelSizeDataControls
                    verticalAlignment: Qt.AlignVCenter
                  }

                  CheckBox {
                    id: arrCalEnable
                    checked: false

                    anchors {
                      right: arrLabelBackground.right
                      margins: Style.heightDataControls / 4
                    }
                  }
                }

                Rectangle {
                  id: arrValueBackground
                  width: Style.widthDataControls
                  height: Style.heightDataControls
                  color: Style.colourDataControlsBackground
                  border {
                    width: 1
                    color: Style.colourDataControlsFont
                  }

                  TextInput {
                    id: arrtextValue
                    enabled: false
                    anchors {
                      fill:parent
                      margins: Style.heightDataControls / 4
                    }
                    text: Qt.formatDate(newTravel.ui_destiny.ui_arr_date.ui_value
                                      , "yyyy-MM-dd")
                    color: Style.colourDataControlsFont
                    font.pixelSize: Style.pixelSizeDataControls
                    verticalAlignment: Qt.AlignVCenter
                  }
                }
              }

              Calendar {
                  visible: arrCalEnable.checked

                  minimumDate: new Date(2020, 0, 1)
                  maximumDate: new Date(2025, 0, 1)

                  anchors {
                    horizontalCenter: arrFlow.horizontalCenter
                    margins: Style.heightDataControls / 4
                  }

                  onClicked: {
                    newTravel.ui_destiny.ui_arr_date.ui_value = selectedDate
                    arrCalEnable.checked = false
                  }

                  Component.onCompleted: {
                    newTravel.ui_destiny.ui_arr_date.ui_value = selectedDate
                  }
              }


            Binding {
              target: newTravel.ui_cli
              property: "ui_value"
              value: client.currentText
            }


          }
        }
      }

      AddressEditor {
        address: newTravel.ui_destiny.ui_address
        headerText: "Destination Address"
      }

      Rectangle {
        id: recErr
        visible: (newTravel.ui_destiny.ui_err.ui_value !== "")
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

            text: newTravel.ui_destiny.ui_err.ui_value
            font.bold: true
            color: "#444444"
        }
      }
    }

    CommandBar {
      id: commandList
      commandList:
        masterController.ui_traCommandController.ui_createTravelViewContextCommands
    }
}

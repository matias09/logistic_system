import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2

import assets 1.0
import components 1.0

Window {
    visible: true
    width: 1920
    height: 1080
    title: qsTr("Sistema de Logistica")

    Connections {
      target: masterController.ui_navigationController
      onGoDashboardView: contentFrame.replace("qrc:/views/DashboardView.qml")

      onGoCreateClientView: contentFrame.replace("qrc:/views/CreateClientView.qml")
      onGoEditClientView: contentFrame.replace("qrc:/views/EditClientView.qml",
              {selectedClient: client})
      onGoFindClientView: contentFrame.replace("qrc:/views/FindClientView.qml")

      onGoCreateDriverView: contentFrame.replace("qrc:/views/CreateDriverView.qml")
      onGoEditDriverView: contentFrame.replace("qrc:/views/EditDriverView.qml",
              {selectedDriver: driver})
      onGoFindDriverView: contentFrame.replace("qrc:/views/FindDriverView.qml")

      onGoCreateVehicleView: contentFrame.replace("qrc:/views/CreateVehicleView.qml")
      onGoEditVehicleView: contentFrame.replace("qrc:/views/EditVehicleView.qml",
              {selectedVehicle: vehicle})
      onGoFindVehicleView: contentFrame.replace("qrc:/views/FindVehicleView.qml")
    }

    NavigationBar {
      id: navigationBar
    }

    StackView {
        id: contentFrame
        clip: true
        anchors {
          top: parent.top
          bottom: parent.bottom
          right:  parent.right
          left:  navigationBar.right
        }
        initialItem: Qt.resolvedUrl("qrc:/views/SplashView.qml")
    }

    Component.onCompleted:
      contentFrame.replace("qrc:/views/DashboardView.qml")
}

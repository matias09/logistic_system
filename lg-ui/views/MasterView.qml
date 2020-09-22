import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2

import assets 1.0
import components 1.0

Window {
    visible: true
    width: 1920
    height: 1080
    title: qsTr("Client Management")

    Connections {
      target: masterController.ui_navigationController
      onGoCreateClientView: contentFrame.replace("qrc:/views/CreateClientView.qml")
      onGoDashboardView: contentFrame.replace("qrc:/views/DashboardView.qml")
      onGoEditClientView: contentFrame.replace("qrc:/views/EditClientView.qml",
              {selectedClient: client})
      onGoFindClientView: contentFrame.replace("qrc:/views/FindClientView.qml")
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
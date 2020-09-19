pragma Singleton
import QtQuick 2.9

Item {
  property alias  fontAwesome: fontAwesomeLoader.name
  readonly property color colourBackground: "#efefef"

// Navigation Button
//---------------------------------------------------------------------------
  readonly property color colourNavigationBarBackground: "#000000"
  readonly property color colourNavigationBarFront: "#ffffff"

  readonly property int pixelSizeNavigationBarIcon: 42
  readonly property int pixelSizeNavigationBarText: 22

  readonly property real  widthNavigationButtonIcon: 80
  readonly property real  heightNavigationButtonIcon: widthNavigationButtonIcon

  readonly property real  widthNavigationButtonDescription: 240
  readonly property real  heightNavigationButtonDescription: heightNavigationButtonIcon

  readonly property real  widthNavigationButton:
    widthNavigationButtonIcon + widthNavigationButtonDescription
  readonly property real  heightNavigationButton:
    Math.max(heightNavigationButtonIcon, heightNavigationButtonDescription)

  readonly property real widthNavigationBarCollapsed: widthNavigationButtonIcon
  readonly property real heightNavigationBarExpanded: widthNavigationButton
// --------------------------------------------------------------------------


// Command Bar
// --------------------------------------------------------------------------

    readonly property color  colourCommandBarBackground: "#cecece"
    readonly property color  colourCommandBarFont: "#131313"
    readonly property color  colourCommandBarFontDisabled: "#636363"

    readonly property real  heightCommandBar: heightCommandButton

    readonly property int  pixelSizeCommandBarIcon: 32
    readonly property int  pixelSizeCommandBarText: 12

    readonly property real widthCommandButton: 80
    readonly property real heightCommandButton: widthCommandButton
// --------------------------------------------------------------------------


// Text Input
// --------------------------------------------------------------------------
    readonly property real sizeScreenMargin: 20

    readonly property color  colourDataControlsBackground: "#FFFFFF"
    readonly property color  colourDataControlsFont: "#131313"

    readonly property int  pixelSizeDataControl: 18

    readonly property real widthDataControls: 400
    readonly property real heightDataControls: 40


// Panel Input
// --------------------------------------------------------------------------
    readonly property color colourPanelBackground: "#ffffff"
    readonly property color colourPanelBackgroundHover: "#ececec"
    readonly property color colourPanelHeaderBackground: "#131313"
    readonly property color colourPanelHeaderFont: "#ffffff"
    readonly property color colourPanelFont: "#131313"
    readonly property color colourShadow: "#dedede"

    readonly property int pixelSizePanelHeader: 18

    readonly property real heightPanelHeader: 40
    readonly property real sizeControlSpacing: 10
    readonly property real sizeShadowOffset: 5


  FontLoader {
    id: fontAwesomeLoader
    source: "qrc:/assets/fontawesome.ttf"
  }
}

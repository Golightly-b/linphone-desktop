import QtQuick 2.7
import QtQuick.Window 2.2

import Common.Styles 1.0

// ===================================================================

Item {
  id: wrapper

  property int popupX: 0
  property int popupY: 0

  property int edge: 0

  readonly property alias popupWidth: popup.width
  readonly property alias popupHeight: popup.height

  default property alias _content: content.data
  property bool _isOpen: false

  function show () {
    _isOpen = true
  }

  function hide () {
    _isOpen = false
  }

  function _applyXEdge (edge) {
    var screen = popup.Screen

    if (screen == null) {
      return popupX
    }

    if (edge & Qt.LeftEdge) {
      return 0
    }

    return screen.width - popup.width
  }

  function _applyYEdge (edge) {
    var screen = popup.Screen

    if (screen == null) {
      return popupY
    }

    if (edge & Qt.TopEdge) {
      return 0
    }

    return screen.height - popup.height
  }

  // -----------------------------------------------------------------

  // DO NOT TOUCH THIS PROPERTIES.

  // No visible.
  visible: false

  // No size, no position.
  height: 0
  width: 0
  x: 0
  y: 0

  Window {
    id: popup

    flags: Qt.SplashScreen
    opacity: 0
    height: _content[0] != null ? _content[0].height : 0
    width: _content[0] != null ? _content[0].width : 0

    x: edge ? _applyXEdge() : popupX
    y: edge ? _applyYEdge() : popupY

    Item {
      id: content

      // Fake parent.
      property var $parent: wrapper
    }
  }

  // -----------------------------------------------------------------

  states: State {
    name: 'opened'
    when: _isOpen

    PropertyChanges {
      opacity: 1.0
      target: popup
    }
  }

  transitions: [
    Transition {
      from: ''
      to: 'opened'

      ScriptAction {
        script: popup.show()
      }

      NumberAnimation {
        duration: PopupStyle.animation.openingDuration
        easing.type: Easing.InOutQuad
        property: 'opacity'
        target: popup
      }
    },

    Transition {
      from: 'opened'
      to: ''

      SequentialAnimation {
        NumberAnimation {
          duration: PopupStyle.animation.closingDuration
          easing.type: Easing.InOutQuad
          property: 'opacity'
          target: popup
        }

        ScriptAction {
          script: popup.hide()
        }
      }
    }
  ]
}

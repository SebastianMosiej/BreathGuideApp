import QtQuick 2.15
import QtQuick.Controls 2.15
import breathAppItems 1.0

ApplicationWindow {
    width: 800
    height: 600
    visible: true

    BreathingGraphItem {
        anchors.fill: parent
    }
}

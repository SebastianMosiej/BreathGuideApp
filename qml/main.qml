import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import breathAppItems 1.0

ApplicationWindow {
    width: 800
    height: 600
    visible: true

    ColumnLayout {
        anchors.fill: parent
        BreathingPhaseInfo {
            phase: breathingGraph.phase
            remainingTime: breathingGraph.remainingTime
            Layout.fillWidth: true
        }

        BreathingGraphItem {
            id: breathingGraph
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }
}

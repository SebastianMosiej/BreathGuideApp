import QtQuick 2.15
import breathAppItems 1.0

Item {
    property int phase: BreathPhase.NONE_SECTION
    property int remainingTime: 0

    id: root
    height: 100
    Text {
        id: phaseName
        height: parent.height
        width: parent.width
        text: ""
        font.pixelSize: 16
        verticalAlignment: Qt.AlignVCenter
        horizontalAlignment: Qt.AlignHCenter
    }

    states: [
        State {
            name: "inhale"
            when: root.phase === BreathPhase.INHALE_SECTION
            PropertyChanges {
                target: phaseName
                text: qsTr("Inhale %1").arg(root.remainingTime)
            }
        },
        State {
            name: "inhaleHold"
            when: root.phase === BreathPhase.INHALE_HOLD_SECTION
            PropertyChanges {
                target: phaseName
                text: qsTr("Hold Inhale %1").arg(root.remainingTime)
            }
        },
        State {
            name: "exhale"
            when: root.phase === BreathPhase.EXHALE_SECTION
            PropertyChanges {
                target: phaseName
                text: qsTr("Exhale %1").arg(root.remainingTime)
            }
        },
        State {
            name: "exhaleHold"
            when: root.phase === BreathPhase.EXHALE_HOLD_SECTION
            PropertyChanges {
                target: phaseName
                text: qsTr("Hold Exhale %1").arg(root.remainingTime)
            }
        }
    ]
}

import QtQuick 2.2

Item
{
    id: gaugeSpeedSource
    property real speed: 0

    SequentialAnimation
    {
        running: true
        loops: Animation.Infinite

        NumberAnimation
        {
            target: gaugeSpeedSource
            property: "speed"
            easing.type: Easing.InOutSine
            to: (Math.ceil(Math.random() * 2400 - 1800)) + 1800
            duration: (Math.random() * 4000 - 500) + 500
        }

        PauseAnimation {
            duration: (Math.random() * 10000 - 500) + 500
        }
        NumberAnimation
        {
            target: gaugeSpeedSource
            property: "speed"
            easing.type: Easing.InOutSine
            to: (Math.random() * 1400 + 600) + 600
            duration: (Math.random() * 4000 - 500) + 500
        }

        PauseAnimation {
            duration: (Math.random() * 10000 - 500) + 500
        }
    }
}

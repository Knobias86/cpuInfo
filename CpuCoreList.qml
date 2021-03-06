import QtQuick 2.7
import QtQuick.Extras 1.4
import QtQuick.Controls.Styles 1.4

Rectangle
{
    id: cpuList
    color: "black"

    Text
    {
        id: headerText
        width: parent.width
        horizontalAlignment: Text.AlignHCenter
        topPadding: 5

        font.bold: true
        font.pointSize: 10
        color: "white"
        text: "CPU Information"
    }

    Flickable
    {
        anchors.top:headerText.bottom
        anchors.bottom: parent.bottom
        width: parent.width;
        height: parent.height
        contentWidth: gridview.width;
        contentHeight: gridview.height

        clip: true
        flickableDirection: Flickable.VerticalFlick

        Column
        {
            id: gridview
            width: parent.width
            topPadding: 15
            spacing: 25

            Repeater
            {
                id: repeater
                model: cpuData["logical_units"]

                Row
                {
                    Text
                    {
                        id: cputext
                        leftPadding: 50

                        color: "white"
                        text: "Core " + index + ":"
                    }
                    Gauge
                    {
                        id: cpuBar
                        orientation: Qt.Horizontal

                        minimumValue: 0
                        maximumValue: 3100

                        tickmarkStepSize: 700
                        value: parseFloat(cpuData["cpu MHz"+index])

                        Behavior on value
                        {
                            NumberAnimation
                            {
                                duration: 1000
                            }
                        }

                        style: GaugeStyle
                        {
                            valueBar: Rectangle
                            {
                                implicitWidth: 16
                                color: Qt.rgba(cpuBar.value / cpuBar.maximumValue, 0, 1 - cpuBar.value / cpuBar.maximumValue, 1)
                            }
                        }
                    }
                    Text
                    {
                        rightPadding: 10

                        color: "white"
                        text: parseInt(cpuData["cpu MHz" + index]) + " MHz";
                    }
                }
            }
        }
    }
}


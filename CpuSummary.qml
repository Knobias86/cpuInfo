import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import QtQuick.Extras 1.4
import QtQuick.Controls.Styles 1.4

Rectangle
{
    id: cpuSummary
    color: "black"

    Text
    {
        id: headerText
        topPadding: 5
        horizontalAlignment: Text.AlignHCenter
        width: parent.width

        font.bold: true
        font.pointSize: 10
        color: "white"
        text: "CPU Summary"
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

        Grid
        {
            id: gridview
            columns: 2
            spacing: 10
            padding: 10

            Text
            {
                color: "white"
                text: "Model:"
            }
            Text
            {
                color: "white"
                text: String(cpuData["model name0"])
            }
            Text
            {
                color: "white"
                text: "No. logical cores: \n(per CPU)"
            }
            Text
            {
                color: "white"
                text: String(cpuData["logical_units"])
            }
            Text
            {
                color: "white"
                text: "BogoMIPS:"
            }
            Text
            {
                color: "white"
                text: String(cpuData["BogoMIPS0"])
            }
            Text
            {
                color: "white"
                text: "Flags:"
            }
            Text
            {
                width: 250
                wrapMode: Text.WordWrap
                color: "white"
                text: String(cpuData["Features0"])
            }
        }
    }
}

import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 2.0

Window
{
    id: window
    visible: true
    width: 480
    height: 320

    SwipeView
    {
        id: view

        currentIndex: 0
        anchors.fill: parent

        CpuSummary
        {
            id: cpuSummary
        }
        CpuCoreList
        {
            id: cpuCoreView
        }
    }

    PageIndicator
    {
        id: pageIndicator

        count: view.count
        currentIndex: view.currentIndex


        delegate: Rectangle
        {
            implicitWidth: 8
            implicitHeight: 8

            radius: width / 2
            color: "white"

            opacity: index === pageIndicator.currentIndex ? 0.95 : pressed ? 0.7 : 0.45

            Behavior on opacity
            {
                OpacityAnimator
                {
                    duration: 100
                }
            }
        }

        anchors.bottom: view.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }
}

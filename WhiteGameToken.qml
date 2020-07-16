import QtQuick 2.9

Rectangle {
        
        property var posIndex
        z: 1
        width: 45
        height: 45
        color: "#d5d4d4"
        radius: 100
        Rectangle {
            width: 30
            height: 30
            color: "#cbcaca"
            radius: 100
            Rectangle {
                width: 15
                height: 15
                color: "#d5d4d4"
                radius: 100
                anchors.centerIn: parent
            }
            anchors.centerIn: parent
        }
        MouseArea {
                anchors.fill: parent
                onClicked: window.tokenSelected(parent.parent.ringIndex, parent.posIndex, 1)
        }
}
import QtQuick 2.9
Rectangle {
        
        property var posIndex
        z: 2
        width: 45
        height: 45
        radius: 100
        color: "#222222"

        Rectangle{
            width: 30
            height: 30
            radius: 100
            anchors.centerIn: parent
            color: "#484848"

            Rectangle{
                width: 15
                height: 15
                radius: 100
                anchors.centerIn: parent
                color: "#222222"
            }
        }
        MouseArea {
                anchors.fill: parent
                onClicked: {window.tokenSelected(parent.parent.ringIndex, parent.posIndex, -1)}
        }
    }
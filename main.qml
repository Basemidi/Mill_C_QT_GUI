import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.13

import "GameLogic.js" as Logic


Window {
    id: window
    visible: true
    width: 640
    height:480

    property var tokens: ({00 : null})

    signal positionSignal(int ring, int position)
    signal startGame()
    signal tokenSelected(int ring, int position, int stone)
    signal makeAiMove()


    function setStone( Ring,  pos,  player){
        Logic.createStoneAtPos(Ring, pos, player)
    }
    function removeStone(Ring, pos){
        Logic.removeToken(Ring, pos)
    }
    function setCounter(num, token){
        Logic.setCounter(num, token)
    }
    function prepForAiMove(){
        makeAiMove()
    }


    Rectangle {
        id: outerRing
        objectName: "outerRing"
        property var ringIndex: 0
        x: 25
        y: 25
        width: 430
        height: 430
        border.color: "black"
        border.width: 3
        color: "#ffffff"
        radius: 10

        Rectangle{
            id: path011121
            x: (parent.height / 2) - 1
            y: 0
            width: 3
            height: parent.height *(1/3)
            color: "#000000"
        }
        Rectangle{
            id: path251505
            x: (parent.height / 2) - 1
            y: parent.height * (2/3)
            width: 3
            height: parent.height *(1/3)
            color: "#000000"
        }

        Rectangle{
            id: path071727
            x: 0
            y: (parent.height / 2) - 1
            width: parent.height *(1/3)
            height: 3
            color: "#000000"
        }

        Rectangle{
            id: path231303
            x: parent.height * (2/3)
            y: (parent.height / 2) - 1
            width: parent.height *(1/3)
            height: 3
            color: "#000000"
        }


        Rectangle {
            id: position00
            
            property var posIndex: 0
            x: -8
            y: -8
            width: 17
            height: 17
            color: "#000000"
            radius: 100

            MouseArea {
                anchors.fill: parent
                onClicked: Logic.selectedPosition(position00)
            }
        }

        Rectangle {
            id: position01
            property var posIndex: 1
            x: (parent.width/ 2) -8
            y: -8
            width: 17
            height: 17
            color: "#000000"
            radius: 100
            MouseArea {
                anchors.fill: parent
                onClicked: Logic.selectedPosition(position01)
            }
        }

        Rectangle {
            id: position02
            property var posIndex: 2
            x: parent.width - 8
            y: -8
            width: 17
            height: 17
            color: "#000000"
            radius: 100
            
            MouseArea {
                anchors.fill: parent
                onClicked: Logic.selectedPosition(position02)
            }
        }

        Rectangle {
            id: position03
            property var posIndex: 3
            x: parent.width - 8
            y: (parent.height / 2) - 8
            width: 17
            height: 17
            color: "#000000"
            radius: 100

            MouseArea {
                anchors.fill: parent
                onClicked: Logic.selectedPosition(position03)
            }
            
        }

        Rectangle {
            id: position04
            property var posIndex: 4
            x: parent.width - 8
            y: parent.height - 8
            width: 17
            height: 17
            color: "#000000"
            radius: 100

            MouseArea {
                anchors.fill: parent
                onClicked: Logic.selectedPosition(position04)
            }
            
        }
        Rectangle {
            id: position05
            property var posIndex: 5
            x: (parent.width/2) - 8
            y: parent.height - 8
            width: 17
            height: 17
            color: "#000000"
            radius: 100

            MouseArea {
                anchors.fill: parent
                onClicked: Logic.selectedPosition(position05)
            }
        }

        Rectangle {
            id: position06
            property var posIndex: 6
            x: -8
            y: parent.height - 8
            width: 17
            height: 17
            color: "#000000"
            radius: 100

            MouseArea {
                anchors.fill: parent
                onClicked: Logic.selectedPosition(position06)
            }
        }

        Rectangle {
            id: position07
            property var posIndex: 7
            x: -8
            y: (parent.height/2) - 8
            width: 17
            height: 17
            color: "#000000"
            radius: 100

            MouseArea {
                anchors.fill: parent
                onClicked: Logic.selectedPosition(position07)
            }
        }

        Rectangle{
            id: midRing
            property var ringIndex: 1
            width: parent.width * (2/3)
            height: parent.height * (2/3)
            border.color: "black"
            border.width: 3
            color: "transparent"
            radius: 10
            anchors.centerIn: parent

            Rectangle {
                id: position10
                property var posIndex: 0
                x: -8
                y: -8
                width: 17
                height: 17
                color: "#000000"
                radius: 100

                MouseArea {
                    anchors.fill: parent
                    onClicked: Logic.selectedPosition(position10)
                }
            }

            Rectangle {
                id: position11
                property var posIndex: 1
                x: (parent.width/ 2) -8
                y: -8
                width: 17
                height: 17
                color: "#000000"
                radius: 100

                MouseArea {
                    anchors.fill: parent
                    onClicked: Logic.selectedPosition(position11)
                }
            }

            Rectangle {
                id: position12
                property var posIndex: 2
                x: parent.width - 8
                y: -8
                width: 17
                height: 17
                color: "#000000"
                radius: 100

                MouseArea {
                    anchors.fill: parent
                    onClicked: Logic.selectedPosition(position12)
                }
            }

            Rectangle {
                id: position13
                property var posIndex: 3
                x: parent.width - 8
                y: (parent.height / 2) - 8
                width: 17
                height: 17
                color: "#000000"
                radius: 100

                MouseArea {
                    anchors.fill: parent
                    onClicked: Logic.selectedPosition(position13)
                }
            }

            Rectangle {
                id: position14
                property var posIndex: 4
                x: parent.width - 8
                y: parent.height - 8
                width: 17
                height: 17
                color: "#000000"
                radius: 100

                MouseArea {
                    anchors.fill: parent
                    onClicked: Logic.selectedPosition(position14)
                }
            }
            Rectangle {
                id: position15
                property var posIndex: 5
                x: (parent.width/2) - 8
                y: parent.height - 8
                width: 17
                height: 17
                color: "#000000"
                radius: 100

                MouseArea {
                    anchors.fill: parent
                    onClicked: Logic.selectedPosition(position15)
                }
            }

            Rectangle {
                id: position16
                property var posIndex: 6
                x: -8
                y: parent.height - 8
                width: 17
                height: 17
                color: "#000000"
                radius: 100

                MouseArea {
                    anchors.fill: parent
                    onClicked: Logic.selectedPosition(position16)
                }
            }

            Rectangle {
                id: position17
                property var posIndex: 7
                x: -8
                y: (parent.height/2) - 8
                width: 17
                height: 17
                color: "#000000"
                radius: 100

                MouseArea {
                    anchors.fill: parent
                    onClicked: Logic.selectedPosition(position17)
                }
            }

            Rectangle{
                id: innerRing
                property var ringIndex: 2
                width: parent.parent.width * (1/3)
                height: parent.parent.height * (1/3)
                border.color: "black"
                border.width: 3
                color: "transparent"
                radius: 10
                anchors.centerIn: parent

                Rectangle {
                    id: position20
                    property var posIndex: 0
                    x: -8
                    y: -8
                    width: 17
                    height: 17
                    color: "#000000"
                    radius: 100

                    MouseArea {
                        anchors.fill: parent
                        onClicked: Logic.selectedPosition(position20)
                    }
                }

                Rectangle {
                    id: position21
                    property var posIndex: 1
                    x: (parent.width/ 2) -8
                    y: -8
                    width: 17
                    height: 17
                    color: "#000000"
                    radius: 100

                    MouseArea {
                        anchors.fill: parent
                        onClicked: Logic.selectedPosition(position21)
                    }
                }

                Rectangle {
                    id: position22
                    property var posIndex: 2
                    x: parent.width - 8
                    y: -8
                    width: 17
                    height: 17
                    color: "#000000"
                    radius: 100

                    MouseArea {
                        anchors.fill: parent
                        onClicked: Logic.selectedPosition(position22)
                    }
                }

                Rectangle {
                    id: position23
                    property var posIndex: 3
                    x: parent.width - 8
                    y: (parent.height / 2) - 8
                    width: 17
                    height: 17
                    color: "#000000"
                    radius: 100

                    MouseArea {
                        anchors.fill: parent
                        onClicked: Logic.selectedPosition(position23)
                    }
                }

                Rectangle {
                    id: position24
                    property var posIndex: 4
                    x: parent.width - 8
                    y: parent.height - 8
                    width: 17
                    height: 17
                    color: "#000000"
                    radius: 100

                    MouseArea {
                        anchors.fill: parent
                        onClicked: Logic.selectedPosition(position24)
                    }
                }
                Rectangle {
                    id: position25
                    property var posIndex: 5
                    x: (parent.width/2) - 8
                    y: parent.height - 8
                    width: 17
                    height: 17
                    color: "#000000"
                    radius: 100

                    MouseArea {
                        anchors.fill: parent
                        onClicked: Logic.selectedPosition(position25)
                    }
                }

                Rectangle {
                    id: position26
                    property var posIndex: 6
                    x: -8
                    y: parent.height - 8
                    width: 17
                    height: 17
                    color: "#000000"
                    radius: 100

                    MouseArea {
                        anchors.fill: parent
                        onClicked: Logic.selectedPosition(position26)
                    }
                }

                Rectangle {
                    id: position27
                    property var posIndex: 7
                    x: -8
                    y: (parent.height/2) - 8
                    width: 17
                    height: 17
                    color: "#000000"
                    radius: 100

                    MouseArea {
                        anchors.fill: parent
                        onClicked: Logic.selectedPosition(position27)
                    }
                }
            }
        }
    }

    Button {
        id: buttonReset
        x: 503
        y: 415
        text: qsTr("Reset Game")
        visible: false
    }
    Button {
        id: buttonStart
        x: 503
        y: 380
        text: qsTr("Start Game")
        onClicked: {
            buttonReset.visible = true
            buttonStart.visible = false           
            window.startGame()
            }
        
    }

    Text {
        id: blackStoneCounter
        x: 590
        y: 144
        text: qsTr("0")
        font.pixelSize: 24
    }

    Text {
        id: whiteStoneCounter
        x: 590
        y: 263
        text: qsTr("0")
        font.pixelSize: 24
    }

    Rectangle {
        id: blackToken
        x: 531
        y: 136
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
    }

    Rectangle {
        id: whiteToken
        x: 531
        y: 255
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
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

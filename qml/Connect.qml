/*
 * This file is part of the Utilyze distribution (https://github.com/anishsheikh/Utilyze).
 * Copyright (c) 2022 Anish Sheikh.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

import QtQuick
import Shared

GamePage {

    errorMessage: deviceFinder.error
    infoMessage: deviceFinder.info
    Rectangle {
        id: viewContainer
        anchors.top: parent.top
        anchors.bottom:
            // only BlueZ platform has address type selection
            connectionHandler.requiresAddressType ? addressTypeButton.top : searchButton.top
        anchors.topMargin: GameSettings.fieldMargin + messageHeight
        anchors.bottomMargin: GameSettings.fieldMargin
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width - GameSettings.fieldMargin*2
        color: GameSettings.viewColor
        radius: GameSettings.buttonRadius


        Text {
            id: title
            width: parent.width
            height: GameSettings.fieldHeight
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            color: GameSettings.textColor
            font.pixelSize: GameSettings.mediumFontSize
            text: qsTr("FOUND DEVICES")

            BottomLine {
                height: 1;
                width: parent.width
                color: "#898989"
            }
        }


        ListView {
            id: devices
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.top: title.bottom
            model: deviceFinder.devices
            clip: true
            Text {
                id: title2
                height:GameSettings.fieldHeight * 1.2
                width: devices.width
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                anchors.top: parent.top
                anchors.topMargin: parent.height * 0.1
                anchors.leftMargin: parent.height * 0.1
                anchors.left: parent.left
                anchors.rightMargin: parent.height * 0.1
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: GamePage.Center
                anchors.right: parent.right
                color: GameSettings.textColor
                font.pixelSize: GameSettings.smallTinyFontSize
                text: qsTr("\nRoomNet Can Connect To One Device \n At a time \n Disconnect from other Devices Before Connecting \nClick Start Search Button, Tap On Devices With 'RoomNet' to Get Started.")
                visible: deviceFinder.ready
            }

            Text {
                id: title3
                height:GameSettings.fieldHeight * 1.2
                width: devices.width
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                anchors.top: parent.top
                anchors.topMargin: parent.height * 0.1
                anchors.leftMargin: parent.height * 0.1
                anchors.left: parent.left
                anchors.rightMargin: parent.height * 0.1
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: GamePage.Center
                anchors.right: parent.right
                color: GameSettings.textColor
                font.pixelSize: GameSettings.smallTinyFontSize
                text: qsTr("\n\nIf No Device With 'RoomNet' found, Check if The Appliance is Installed Properly and Turned on\n or \nYou Maybe Too Far From The Device \n or \n Maybe its Connected With Other Device")
                visible: deviceFinder.notfound
            }

            delegate: Rectangle {
                id: box
                height:GameSettings.fieldHeight * 1.2
                width: devices.width
                color: index % 2 === 0 ? GameSettings.delegate1Color : GameSettings.delegate2Color

                MouseArea {
                anchors.fill: parent
                    onClicked: {
                        deviceFinder.connectToService(modelData.deviceAddress);
                        app.showPage("SwitchView.qml")
                    }
                }

                Text {
                    id: device
                    font.pixelSize: GameSettings.smallFontSize
                    text: modelData.deviceName
                    anchors.top: parent.top
                    anchors.topMargin: parent.height * 0.1
                    anchors.leftMargin: parent.height * 0.1
                    anchors.left: parent.left
                    color: GameSettings.textColor
                }

            }
        }
    }

    GameButton {
        id: addressTypeButton
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: searchButton.top
        anchors.bottomMargin: GameSettings.fieldMargin*0.5
        width: viewContainer.width
        height: GameSettings.fieldHeight
        visible: connectionHandler.requiresAddressType // only required on BlueZ
        state: "public"
        onClicked: state === "public" ? state = "random" : state = "public"

        states: [
            State {
                name: "public"
                PropertyChanges { target: addressTypeText; text: qsTr("Public Address") }
                PropertyChanges { target: deviceHandler; addressType: AddressType.PublicAddress }
            },
            State {
                name: "random"
                PropertyChanges { target: addressTypeText; text: qsTr("Random Address") }
                PropertyChanges { target: deviceHandler; addressType: AddressType.RandomAddress }
            }
        ]

        Text {
            id: addressTypeText
            anchors.centerIn: parent
            font.pixelSize: GameSettings.tinyFontSize
            color: GameSettings.textColor
        }
    }

    GameButton {
        id: searchButton
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: GameSettings.fieldMargin * 2
        width: viewContainer.width
        height: GameSettings.fieldHeight
        enabled: !deviceFinder.scanning
        onClicked: deviceFinder.startSearch()
        visible: !connectionHandler.loc

        Text {
            anchors.centerIn: parent
            font.pixelSize: GameSettings.tinyFontSize
            text: qsTr("START SEARCH")
            color: searchButton.enabled ? GameSettings.textColor : GameSettings.disabledTextColor
        }
    }
}

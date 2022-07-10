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

Item {
    id: root
    anchors.fill: parent

    Rectangle {
        anchors.fill: parent
        color: "black"
        opacity: 0.9
    }

    MouseArea {
        id: eventEater
    }

    Rectangle {
        id: dialogFrame

        anchors.centerIn: parent
        width: parent.width * 0.8
        height: parent.height * 0.6
        border.color: "#454545"
        color: GameSettings.backgroundColor
        radius: width * 0.05

        Item {
            id: dialogContainer
            anchors.fill: parent
            anchors.margins: parent.width*0.05

            Image {
                id: offOnImage
                anchors.left: quitButton.left
                anchors.right: quitButton.right
                anchors.top: parent.top
                height: GameSettings.heightForWidth(width, sourceSize)
                source: "/images/location.png"
            }

            Text {
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: offOnImage.bottom
                anchors.bottom: quitButton.top
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                wrapMode: Text.WordWrap
                font.pixelSize: GameSettings.mediumFontSize
                color: GameSettings.textColor
                text: qsTr("Android Needs Location To Use Bluetooth. Please switch Location ON and reopen app.")
            }

            GameButton {
                id: quitButton
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                width: dialogContainer.width * 0.6
                height: GameSettings.buttonHeight
                onClicked: Qt.quit()

                Text {
                    anchors.centerIn: parent
                    color: GameSettings.textColor
                    font.pixelSize: GameSettings.bigFontSize
                    text: qsTr("Quit")
                }
            }
        }
    }
}


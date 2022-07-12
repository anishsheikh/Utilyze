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

Rectangle    {
    id: titleBar
    anchors.top: parent.top
    anchors.left: parent.left
    anchors.right: parent.right
    height: GameSettings.fieldHeight * 1.5
    color: GameSettings.viewColor

    property var __titles: ["CONNECT", "CONTROL"]
    property int currentIndex: 0

    signal titleClicked(int index)

    Repeater {
        model: 2
        Text {
            width: titleBar.width / 2
            height: titleBar.height * 1.35
            x: index * width
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            text: __titles[index]
            font.pixelSize: GameSettings.tinyFontSize
            color: titleBar.currentIndex === index ? GameSettings.textColor : GameSettings.disabledTextColor

            MouseArea {
                anchors.fill: parent
                onClicked: titleClicked(index)
            }
        }
    }


    Item {
        anchors.bottom: parent.bottom
        width: parent.width / 2
        height: parent.height
        x: currentIndex * width

        BottomLine{}

        Behavior on x { NumberAnimation { duration: 200 } }
    }

}

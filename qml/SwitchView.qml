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
import QtQuick.Controls
import QtQuick.Controls.Material

GamePage {
    id: measurePage

    errorMessage: deviceHandler.error
    infoMessage: deviceHandler.info

    function write(swr) {
        deviceHandler.write(swr)
    }
    function disconnect(){
        deviceHandler.disconnectService();
        app.prevPage();
    }
    Text {
        id: title3
        height:GameSettings.fieldHeight * 1.2
        width: devices.width
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        anchors.top: parent.top
        anchors.topMargin: parent.height * 0.15
        anchors.leftMargin: parent.height * 0.1
        anchors.left: parent.left
        anchors.rightMargin: parent.height * 0.1
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: GamePage.Center
        anchors.right: parent.right
        color: GameSettings.textColor
        font.pixelSize: GameSettings.smallTinyFontSize
        text: qsTr("\nCheck if The Appliance is Powered On \n if Its a Power Cut \nOr\n You Have Moved far Away \n From The Device  \n Click On Disconnect Button \n and \n Wait for Power To Come Back \n Or \n Come Nearby The Device \n Then Connect Again \n Or \n Its Connected With Another Device")
        visible: deviceHandler.disc
    }

    Column{
        anchors.centerIn: parent
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: parent.height*0.10
        spacing: GameSettings.fieldHeight * 0.1
        visible: deviceHandler.ready
        Row{
                spacing: GameSettings.fieldHeight * 0.55
        RoundButton {
            id: button1
            text: qsTr("Switch 1")
            onClicked: write(yourcommand)
            width: GameSettings.fieldHeight*2
            height: GameSettings.fieldHeight*2
            Material.background: GameSettings.viewColor
            Material.foreground: GameSettings.textColor
            font.bold: true
            font.pixelSize: 18
        }
        RoundButton {
            id: button2
            text: qsTr("Switch 2")
            onClicked: write(yourcommand)
            width: GameSettings.fieldHeight*2
            height: GameSettings.fieldHeight*2
            Material.background: GameSettings.viewColor
            Material.foreground: GameSettings.textColor
            font.bold: true
            font.pixelSize: 18
        }
        }
        Row {
                spacing: GameSettings.fieldHeight * 0.55
        RoundButton {
            id: button3
            text: qsTr("Switch 3")
            onClicked: write(yourcommand)
            width: GameSettings.fieldHeight*2
            height: GameSettings.fieldHeight*2
            Material.background: GameSettings.viewColor
            Material.foreground: GameSettings.textColor
            font.bold: true
            font.pixelSize: 18
        }
        RoundButton {
            id: button4
            text: qsTr("Switch 4")
            onClicked: write(yourcommand)
            width: GameSettings.fieldHeight*2
            height: GameSettings.fieldHeight*2
            Material.background: GameSettings.viewColor
            Material.foreground: GameSettings.textColor
            font.bold: true
            font.pixelSize: 18

        }
        }
        Row{
                spacing: GameSettings.fieldHeight * 0.55
        RoundButton {
            id: button5
            text: qsTr("Switch 5")
            onClicked: write(yourcommand)
            width: GameSettings.fieldHeight*2
            height: GameSettings.fieldHeight*2
            Material.background: GameSettings.viewColor
            Material.foreground: GameSettings.textColor
            font.bold: true
            font.pixelSize: 18
        }
        RoundButton {
            id: button6
            text: qsTr("Switch 6")
            onClicked: write(yourcommand)
            width: GameSettings.fieldHeight*2
            height: GameSettings.fieldHeight*2
            Material.background: GameSettings.viewColor
            Material.foreground: GameSettings.textColor
            font.bold: true
            font.pixelSize: 18
        }
        }
        Row{
                spacing: GameSettings.fieldHeight * 0.55
        RoundButton {
            id: button7
            text: qsTr("Switch 7")
            onClicked: write(yourcommand)
            width: GameSettings.fieldHeight*2
            height: GameSettings.fieldHeight*2
            Material.background: GameSettings.viewColor
            Material.foreground: GameSettings.textColor
            font.bold: true
            font.pixelSize: 18
        }
        RoundButton {
            id: button8
            text: qsTr("Switch 8")
            onClicked: write(yourcommand)
            width: GameSettings.fieldHeight*2
            height: GameSettings.fieldHeight*2
            Material.background: GameSettings.viewColor
            Material.foreground: GameSettings.textColor
            font.bold: true
            font.pixelSize: 18
        }
        }
    }



    RoundButton {
        id: startButton
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: GameSettings.fieldMargin
        width: GameSettings.fieldHeight*2.2
        height: GameSettings.fieldHeight*0.9
        Material.background: GameSettings.viewColor
        Material.foreground: GameSettings.textColor
        font.bold: true
        font.pixelSize: 16
        font.family: "Ariel"
        text: qsTr("Disconnect")
        onClicked: disconnect()
    }
}

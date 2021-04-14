import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Window 2.0

import Qt.labs.settings 1.1

import Process 1.0
import ConfigFile 1.0

ApplicationWindow {
    id: window

    visible: true
    width: Screen.width
    height: Screen.height
    title: qsTr("Pluto Tool - 1.0.0")

    ConfigFile {
        id: myFile
        onError: console.log(msg)
    }

    ProcessStarter {
        id: process
        onReadyRead: {
            console.info("Process executed!")
            lTableParser.parse(readAll())
        }

        onStarted: {
            console.info("Process started")
        }

        onErrorOccurred: {
            console.error("Fail start process: " + error)
        }

    }

    Rectangle {
        id: commands
        anchors.left: parent.left
        anchors.top: parent.top
        height: parent.height
        width: 100
        color: "#990033"

        ColumnLayout {
            width: parent.width
            spacing: 1

            MenuButton {
                id: buttonStatus

                text: "Status"

                onClicked: {
                    process.start(myFile.cliToolPath, [ "-z", "status", myFile.databasePath])
//                    statusView.visible = true
                    categoryView.visible = false
                    payeeView.visible = false
                }
            }

            MenuButton {
                id: buttonPayee

                text: "Payees"

                onClicked: {
//                    process.start(myFile.cliToolPath, [ "-z", "get-payees", myFile.databasePath])
                    payeeView.visible = true
                    categoryView.visible = false
                }
            }

            MenuButton {
                id: buttonCategory

                text: "Category"

                onClicked: {
//                    process.start(myFile.cliToolPath, [ "-z", "get-categories", myFile.databasePath])
                    payeeView.visible = false
                    categoryView.visible = true
                }
            }
        }
    }

    Payee {
        id: payeeView
        width: parent.width - commands.width
        anchors.left: commands.right
        anchors.top: commands.top

        title: "Payees"
    }

    Category {
        id: categoryView
        width: parent.width - commands.width
        anchors.left: commands.right
        anchors.top: commands.top

        title: "Categories"
    }

    Component.onCompleted: {
        console.log("main.qml > onCompleted: Read INI file");
        myFile.read()
        console.log("main.qml > onCompleted: Complete read INI file");
        console.log("main.qml > onCompleted: Read all database...");
        process.start(myFile.cliToolPath, [ "-z", "get-payees", myFile.databasePath])
        process.start(myFile.cliToolPath, [ "-z", "get-categories", myFile.databasePath])
    }

    Component.onDestruction: {

    }
}

import QtQuick 2.12
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import PlutoTool 1.0

Rectangle {
    id: payeePage

    height: parent.height

    property var title: "TITLE"
    property var mLeft: 10
    property var mRight: 10

    anchors.topMargin: 10
    anchors.rightMargin: mRight
    anchors.leftMargin: mLeft

    ColumnLayout {

        id: payeePageInt

        width: parent.width - mRight - mLeft
        height: parent.height

        RowLayout {
            id: payeeHeader

            anchors.top: parent.top
            anchors.right: parent.right
            anchors.left: parent.left

            width: parent.width

            height: 50
            spacing: 3

            Text {
                id: payeeTitle
                height: 40
                Layout.fillWidth: true
                verticalAlignment: Text.AlignBottom
                font.pointSize: 20
                text: title
            }

            Rectangle {
                id: payeeNewButton
                height: 40
                width: 40
                color: "#999999"
                radius: 5

                Image {
                    anchors.centerIn: parent
                    source: "images/add.svg"
                    sourceSize.width: 25
                    sourceSize.height: 25
                }
            }
        }

        TableView {
            columnSpacing: 1
            rowSpacing: 1

            height: parent.height

            anchors.top: payeeHeader.bottom
            anchors.right: payeeHeader.right
            anchors.left: payeeHeader.left

            anchors.topMargin: 10
            clip: true

            property var columnWidths: [50, (parent.width - 200), 150]
            columnWidthProvider: function (column) { return columnWidths[column] }

            model: PayeeModel {
                list: lPayeeList
            }

            delegate: Rectangle {
                implicitWidth: 200
                implicitHeight: 30
                border.color: "black"
                border.width: 0
                color: (tableheading == true) ? "#990033":"#EEEEEE"
                Text {
                    text: tabledata
                    color: (tableheading == true) ? "#FFFFFF":"#000000"
                    font.bold: (tableheading == true) ? true : false
                    anchors.centerIn: parent
                }
                Component.onCompleted: {
                    console.log(tabledata);
                }
            }
        }

    }
    Component.onCompleted: {
        console.log("Width");
        console.log("PAGE: " + payeePage.width);
        console.log("PAGEINT: " + payeePageInt.width);
        console.log("HEADER: " + payeeHeader.width);
        console.log("TITLE: " + payeeTitle.width);
        console.log("BUT: " + payeeNewButton.width);
        console.log("Height");
        console.log("PAGE: " + payeePage.height);
        console.log("PAGEINT: " + payeePageInt.height);
        console.log("HEADER: " + payeeHeader.height);
        console.log("X-Y");
        console.log("PAGE: " + payeePage.x + " - " + payeePage.y);
        console.log("PAGEINT: " + payeePageInt.x + " - " + payeePageInt.y);
        console.log("HEADER: " + payeeHeader.x + " - " + payeeHeader.y);
    }
}

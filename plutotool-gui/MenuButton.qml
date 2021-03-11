import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3


Button {
    id: mybutton
    text: "-"
    width: parent.width
    height: 40

    background: Rectangle {
        implicitWidth: parent.width
        implicitHeight: parent.height
//        border.width: buttonPayee.activeFocus ? 2 : 1
        border.width: 0
        border.color: "#750127"
        color: mybutton.down ? "#750127" : "#990033"
    }

    contentItem: Text {
        text: parent.text
        font: parent.font
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
        //color: buttonPayee.down ? "#ffffff" : "#666666"
        color: "#ffffff"
    }
}

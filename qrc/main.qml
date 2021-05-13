import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Window 2.12

ApplicationWindow{
    id: root
    visible: true
    title: qsTr("TKOM")

    minimumWidth: 650
    minimumHeight: 450

    background: Rectangle{ color: "white" }

    ColumnLayout {
        width: root.width

        TextArea{
            id: code
            placeholderText: "Let the code begin..."

        }
        Button {

            id: run
            text: qsTr("run")
        }
    }
}
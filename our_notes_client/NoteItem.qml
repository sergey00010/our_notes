import QtQuick
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15
import Custom 1.0

Rectangle {
    property string _mainColor: "#DDB892"
    property string _secondColor: "#EDE0D4"

    color:_secondColor
    radius: 10
    
    ColumnLayout {
        width: parent.width
        height: parent.height
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.left: parent.left
        anchors.leftMargin: 10
        spacing: 1
        
        Text {
            text: "ID: " + model.id
            font.pixelSize: 14
            anchors.horizontalCenter: parent.horizontalCenter
        }
        
        Text {
            text: "name: " + model.nameNote
            font.pixelSize: 16
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
        }
        
        Text {
            text: "content: " + model.contentNote
            font.pixelSize: 14
            anchors.horizontalCenter: parent.horizontalCenter
        }
        RowLayout{
            Layout.fillWidth: true
            Layout.fillHeight: true
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 2
            CustomButton {
                Layout.maximumWidth: parent.width * 0.3
                text:"remove note"
                _mainColor:_mainColor
                onClicked: {
                    noteManager.removeNote(model.id);
                }
            }
            CustomButton {
                text:"edit note"
                _mainColor:_mainColor
                onClicked: {
                    idActiveNote = model.id
                    nameActiveNote = model.nameNote
                    contentActiveNote = model.contentNote
                    
                    stackView.push(editNotePage)
                    
                }
            }
        }
    }
}

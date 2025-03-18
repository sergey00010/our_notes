import QtQuick
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15
import Custom 1.0

ColumnLayout{
    TextField{
        id:noteNameEditArea
        Layout.fillWidth: true
        placeholderText: "enter name note ..."
        background: Rectangle{
            color:secondColor
            radius: 10
        }
    }
    
    ScrollView {
        id: viewnote
        Layout.fillWidth: true
        Layout.fillHeight: true
        TextArea {
            id:noteTextEditArea
            width: parent.width * 0.95
            height: parent.height * 0.95
            placeholderText: "enter note ..."
            textFormat: TextEdit.AutoText
            wrapMode: TextArea.Wrap
            
            background: Rectangle{
                color:secondColor
                radius: 10
            }
        }
    }
    RowLayout{
        Layout.preferredHeight: parent.height * 0.1
        Layout.fillWidth: true
        
        CustomButton {
            text:"<-"
            _mainColor:secondColor
            font.pixelSize: 14
            onClicked: {
                stackView.pop()
            }
        }
        CustomButton {
            text:"save"
            _mainColor:secondColor
            font.pixelSize: 14
            onClicked: {
                noteManager.manageNote(idActiveNote,noteNameEditArea.text,noteTextEditArea.text, user)
                stackView.pop()
            }
        }
    }
    Component.onCompleted: {
        noteNameEditArea.text = nameActiveNote
        noteTextEditArea.text = contentActiveNote
    }
}

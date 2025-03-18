import QtQuick
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15
import Custom 1.0

ColumnLayout{
    ListView {
        id:notesListV
        anchors.horizontalCenter: parent.horizontalCenter
        Layout.preferredWidth: parent.width * 0.9
        Layout.fillHeight: true
        model: noteModel
        spacing: 6
        delegate: NoteItem {
            width: notesListV.width
            height: notesListV.height * 0.3
            _secondColor: secondColor
        }
    }
    RowLayout{
        anchors.horizontalCenter: parent.horizontalCenter
        Layout.preferredWidth: parent.width * 0.99
        Layout.preferredHeight: parent.height * 0.1
        Rectangle{
            anchors.fill: parent
            color:mainColor
            CustomButton {
                anchors.centerIn: parent
                width: parent.width * 0.9
                height: parent.height * 0.7
                _mainColor:secondColor
                text:"add new note"
                onClicked: {
                    idActiveNote = -1
                    nameActiveNote = ""
                    contentActiveNote = ""
                    stackView.push(editNotePage)
                }
            }
        }
    }
}

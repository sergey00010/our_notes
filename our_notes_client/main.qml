import QtQuick
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15
import Custom 1.0

ApplicationWindow  {
    width: 640
    height: 480
    visible: true
    title: qsTr("our notes")

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: loginPage
    }

    property string user: ""

    property int idActiveNote: 0
    property string nameActiveNote: ""
    property string contentActiveNote: ""

    property color mainColor: "#DDB892"
    property color secondColor: "#EDE0D4"


    Component {
        id: listNotesPage
        Page{
            background: Rectangle{
                color:mainColor
            }
            ColumnLayout{
                anchors.fill: parent
                spacing: 2
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
        }
    }


    Component{
        id:editNotePage
            Page{
            background: Rectangle{
                color:mainColor
            }
            ColumnLayout{
                anchors.centerIn: parent
                width: parent.width * 0.9
                height: parent.height * 0.9

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
        }
    }

    Component{
        id:loginPage
        Page{
            background: Rectangle{
                color:mainColor
            }
            ColumnLayout{
                anchors.centerIn: parent
                width: parent.width * 0.7
                height: parent.height * 0.8

                Text{
                    text:"Login: "
                    font.pixelSize: 22
                }

                TextField{
                    id:loginField
                    Layout.fillWidth: true
                    placeholderText: "enter login ..."
                    font.pixelSize: 14
                    background: Rectangle{
                        color:secondColor
                        radius: 10
                    }
                }
                TextField{
                    id:passwordField
                    Layout.fillWidth: true
                    placeholderText: "enter password ..."
                    font.pixelSize: 14
                    echoMode: TextInput.Password
                    background: Rectangle{
                        color:secondColor
                        radius: 10
                    }
                }
                RowLayout{
                    Item {
                        Layout.fillWidth: true
                    }
                    CustomButton {
                        Layout.maximumWidth: parent.width * 0.5
                        text:"login"
                        _mainColor:secondColor
                        font.pixelSize: 14
                        onClicked: {
                            login.logIn(loginField.text,passwordField.text)
                        }
                    }
                }
                Text{
                    id:noticeText
                    text:""
                    font.pixelSize: 15
                }
                Item{
                    Layout.fillHeight: true
                }
                Connections{
                    target: login
                    function onError(errorcontent){
                        noticeText.text = errorcontent
                    }
                    function onLoginSuccess(username){
                        user = username
                        noteManager.loadDataFromDb(username)
                        stackView.push(listNotesPage)
                    }
                }
            }

        }
    }


}

import QtQuick
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15
import Custom 1.0

ColumnLayout{
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

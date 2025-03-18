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
            ListNotesForm {
                anchors.fill: parent
                spacing: 2
            }
        }
    }


    Component{
        id:editNotePage
            Page{
            background: Rectangle{
                color:mainColor
            }
            ManageNote {
                anchors.centerIn: parent
                width: parent.width * 0.9
                height: parent.height * 0.9
            }
        }
    }

    Component{
        id:loginPage
        Page{
            background: Rectangle{
                color:mainColor
            }
            LoginForm {
                anchors.centerIn: parent
                width: parent.width * 0.7
                height: parent.height * 0.8
            }

        }
    }


}

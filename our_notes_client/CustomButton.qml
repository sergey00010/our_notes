import QtQuick
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15
import Custom 1.0

Button{
    property string _mainColor: "#DDB892"

    Layout.fillWidth: true
    font.pixelSize: 14
    background: Rectangle{
        color:_mainColor
        radius: 10
    }
}

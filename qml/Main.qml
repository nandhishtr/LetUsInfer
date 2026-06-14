import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("Let US Infer")
    palette.window: '#c5e5d6'
    palette.windowText:'#254332'
    palette.base:'#c5e5d6'
    palette.text:'#254332'
    palette.button:'#385d4b'
    palette.buttonText:'#254332'
    palette.placeholderText: '#254332'
    RowLayout {
        anchors.fill: parent
        InputView {
            id: inputView
            // anchors.left: parent.left
        }
        OutputView {
            id: outputView
            // anchors.right: parent.right
        }
    }



}

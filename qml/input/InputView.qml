import QtQuick
import QtQuick.Dialogs 
import QtQuick.Controls
import QtQuick.Layouts

Item {
    ColumnLayout {
        anchors.fill: parent
        spacing: 10
        uniformCellSizes: false
        Label {
            id: inputheader
            text: "INPUT"
            font.bold: true
        }
        DropArea {
            Layout.preferredWidth: 200
            Layout.preferredHeight: 200
            Rectangle {
                anchors.fill: parent
                color: '#333837'
                visible: !selectedImage.visible
            }
            Image {
                id: selectedImage
                anchors.fill: parent
                visible: false
            }
            onDropped: {
                selectedImage.source = drop.urls[0]
                selectedImage.visible = true
            }
        }
        Label {
            text: "INPUT DATA DIRECTORY"
            font.bold: true
        }
        TextField {
            id: dataPathPicker
            Layout.preferredWidth: 300
            Layout.preferredHeight: 30
            placeholderText: qsTr("Please choose the data directory")
            onPressed: directoryPicker.open()
        }
        FolderDialog {
            id: directoryPicker
            title: "Please choose a directory"
            visible: false
            onAccepted: {
                console.log("You chose: " + directoryPicker.selectedFolder)
                dataPathPicker.text = directoryPicker.selectedFolder
            }
            onRejected: {
                console.log("Cancelled")
            }
        }
        Label {
            text: "MODEL FILE"
            font.bold: true
        }
        TextField {
            id: modelPicker
            Layout.preferredWidth: 300
            Layout.preferredHeight: 30
            placeholderText: qsTr("Please choose the model")
            onPressed: filePicker.open()
        }
        FileDialog {
            id: filePicker
            title: "Please choose a file"
            visible: false
            onAccepted: {
                console.log("You chose: " + filePicker.selectedFile)
                modelPicker.text = filePicker.selectedFile
            }
            onRejected: {
                console.log("Cancelled")
            }
        }
        Label {
            id: topK
            text: "TopK"
            font.bold: true
        }
        SpinBox {
            id: topkSpin
            from: 1
            to: 10
            value: 5
        }
        Button {
            id: runInference
            text: "RUN INFERENCE"
            font.bold: true
            font.pixelSize: 16
            Layout.preferredWidth: 200
            Layout.preferredHeight: 55
        }
    }
}

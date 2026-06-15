import QtQuick 2.15
import QtQuick.Layouts
import QtQuick.Controls
import Qt.labs.qmlmodels

Item {
    ColumnLayout {
        anchors.fill: parent
        spacing: 10
        uniformCellSizes: false
        Label {
            id: resultHeader
            text: "RESULT"
            font.bold: true
        }
        HorizontalHeaderView {
            id: horizontalHeader
            property var headerLabels: ["Rank", "Label", "Confidence"]
            implicitWidth: 300
            implicitHeight: 20
            syncView: tableView
            clip: true
            delegate: Rectangle {
                color: '#4d996e'
                radius: 2
                implicitWidth: 300
                implicitHeight: 20
                border.width: 0.5
                border.color: '#324c32'
                Label {
                    text: horizontalHeader.headerLabels[column]
                    font.bold: true
                    anchors.centerIn: parent
                }
            }
        }

        TableView {
            id: tableView
            Layout.preferredWidth: 300
            Layout.preferredHeight: 100
            // columnSpacing: 1
            // rowSpacing: 1
            clip: true
            model: dataModel
            delegate: Rectangle {
                border.width: 0.5
                border.color: '#324c32'
                implicitWidth: 150
                implicitHeight: 30
                color: '#b6e1cd'
                Label {
                    anchors.centerIn: parent
                    text: model.display
                    font.bold:true
                }
            }
            TableModel {
                id: dataModel
                TableModelColumn { 
                    display: "Rank"
                }
                TableModelColumn { 
                    display: "Label"
                }
                TableModelColumn { 
                    display: "Confidence"
                }
                // rows: InferenceViewModel.tableModel
            }

        }
        Connections {
                target: InferenceViewModel
                    function onTableModelChanged() {
                        dataModel.rows = JSON.parse(JSON.stringify(InferenceViewModel.tableModel))
                    }
                }
    }
}

import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.1

ApplicationWindow {
    title: qsTr("Task scheduling demonstration")

    width: 640
    height: 480

    ListModel {
        id: jobModel
        property int currentIndex: 0

    }

    Component {
        id: jobDelegate
        Item {
            width: 110
            height: 45

            MouseArea {
                anchors.fill: parent
                onClicked: jobs.currentIndex = index
            }

            Column {
                Text { text: '<b>Job #</b>' + name }
                TextField {
                    text: duration
                    validator: IntValidator {bottom: 1; top: 100;}
                    onFocusChanged: {
                        if (focus == false) {
                            jobModel.setProperty(index, "duration", parseInt(text, 10))
                        }
                    }
                }
            }
        }
    }

    GridLayout {
        anchors.fill: parent
        anchors.margins: 10
        columns: 2

        Label {
            text: qsTr("Number of machines:")

            Layout.column: 0
            Layout.row: 0
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
        }

        TextField {
            id: machineCount
            validator: IntValidator {bottom: 1; top: 100;}
            focus: true
            text: "1"

            Layout.column: 0
            Layout.row: 1
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
        }

        Button {
            text: qsTr("Add job")
            onClicked: {
                ++jobModel.currentIndex
                jobModel.append({"name": jobModel.currentIndex, "duration": 1})
            }

            Layout.column: 0
            Layout.row: 2
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
        }

        Button {
            text: qsTr("Remove job")
            onClicked: {
                if (jobs.currentIndex > -1) jobModel.remove(jobs.currentIndex)
            }

            Layout.column: 0
            Layout.row: 3
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
        }

        Button {
            text: qsTr("Schedule")
            enabled: jobModel.count > 0 && machineCount.text != ""
            onClicked: {
                var parameters = []
                for(var i = 0; i < jobs.model.count; ++i)
                    parameters[i] = parseInt(jobs.model.get(i).duration, 10)

                taskScheduler.schedule(parseInt(machineCount.text, 10), parameters)
            }

            Layout.column: 0
            Layout.row: 4
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
        }

        ScrollView {
            ListView {
                id: jobs

                model: jobModel
                delegate: jobDelegate
                highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
            }

            Layout.minimumWidth: 110
            Layout.minimumHeight: 200
            Layout.preferredWidth: 150
            Layout.maximumWidth: 150
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.column: 0
            Layout.row: 5
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
        }

        Canvas {
            id: canvas
            antialiasing: true

            Layout.minimumWidth: 300
            Layout.minimumHeight: 300
            Layout.preferredWidth: 500
            Layout.preferredHeight: 500
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.column: 1
            Layout.row: 0
            Layout.rowSpan: 6
        }

        Keys.onPressed: {
            if (event.key === Qt.Key_Down) {
                if (jobs.currentIndex < jobs.count - 1) ++jobs.currentIndex
                event.accepted = true;
            } else if (event.key === Qt.Key_Up) {
                if (jobs.currentIndex > 0) --jobs.currentIndex
                event.accepted = true;
            }
        }
    }
}

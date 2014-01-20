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
                    onTextChanged: {
                        if (acceptableInput == true) {
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

                canvas.enabled = true
                taskScheduler.schedule(parseInt(machineCount.text, 10), parameters)
                canvas.drawChart()
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
            enabled: false

            property int verticalBlockCount: 30
            property int horizontalBlockCount: 30
            property real verticalBlockSize: (canvas.height - 2 * graphMargin) / verticalBlockCount
            property real horizontalBlockSize: (canvas.width - 2 * graphMargin) / horizontalBlockCount
            property int graphMargin: 40
            property var context

            property var colors: ['blueviolet', 'limegreen', 'crimson', 'orange', 'hotpink', 'tomato', 'darkturquoise', 'olive', 'burlywood', 'aquamarine', 'lightseagreen', 'brown', 'burlywood']

            Layout.minimumWidth: 300
            Layout.minimumHeight: 300
            Layout.preferredWidth: 500
            Layout.preferredHeight: 500
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.column: 1
            Layout.row: 0
            Layout.rowSpan: 6

            onPaint: drawChart()

            function drawChart() {
                console.log("Drawing chart\t", width - 2 * graphMargin, "x", height - 2 * graphMargin, "usable space.")
                context = canvas.getContext("2d")
                context.clearRect(0, 0, canvas.width, canvas.height)

                drawAxes()
                drawGrid()
                drawData()
                drawLegend()
                canvas.requestPaint()
            }

            function drawAxes() {
                console.log("Drawing axes")
                context.lineWidth = 5
                context.beginPath();
                context.moveTo(graphMargin, graphMargin)
                context.lineTo(graphMargin, canvas.height - graphMargin)
                context.lineTo(canvas.width - graphMargin, canvas.height - graphMargin)
                context.strokeStyle = "#EE000000"
                context.stroke()
            }

            function drawGrid() {
                console.log("Drawing grid \t", horizontalBlockCount, "vertical lines and", verticalBlockCount, "horizontal lines.")
                context.lineWidth = 2
                context.beginPath();
                drawGridVerticalLines()
                drawGridHorizontalLines()
                context.strokeStyle = "#44000000"
                context.stroke()
            }

            function drawGridVerticalLines() {
                var y0 = canvas.height - graphMargin
                var yn = graphMargin
                for (var i = 1; i < horizontalBlockCount; ++i) {
                    var x = graphMargin + i * horizontalBlockSize
                    context.moveTo(x, y0)
                    context.lineTo(x, yn)
                }
            }

            function drawGridHorizontalLines() {
                var x0 = graphMargin
                var xn = canvas.width - graphMargin
                for (var j = 1; j < verticalBlockCount; ++j) {
                    var y = canvas.height - graphMargin - j * verticalBlockSize
                    context.moveTo(x0, y)
                    context.lineTo(xn, y)
                }
            }

            function drawData() {
                console.log("Drawing data")
                context.lineWidth = 5
                var results = taskScheduler.getResults()
                for (var machine = 0; machine < results.length; ++machine) {
                    console.log("Drawing series\t", "#" + machine)
                    drawId(machine)
                    drawSeries(results[machine], graphMargin, canvas.height - graphMargin - verticalBlockSize * (machine + 2))
                }
            }

            function drawId(machine) {
                var textWidth = context.measureText(machine).width
                var textHeight = 20
                context.beginPath()
                context.font = textHeight + "px sans-serif"
                context.fillStyle = "black"
                var x = graphMargin - textWidth - 5
                var y = height - graphMargin - (machine + 1) * verticalBlockSize - 0.5 * textHeight
                context.fillText(machine + 1, x, y)
            }

            function drawSeries(machine, x, y) {
                for (var job = 0; job < machine.length; ++job) {
                    drawJob(machine[job][0], machine[job][1], x, y)
                    x += horizontalBlockSize * machine[job][1]
                }
            }

            function drawJob(id, duration, x, y) {
                context.beginPath();
                console.log("Drawing job  \t", "#" + id, colors[id], duration, "time units")
                context.rect(x, y, duration * horizontalBlockSize, verticalBlockSize)
                context.fillStyle = colors[id]
                context.fill()
                context.lineWidth = 2
                context.strokeStyle = "#AA000000"
                context.stroke();
            }

            function drawLegend() {
                context.beginPath();
                context.fill()
            }
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

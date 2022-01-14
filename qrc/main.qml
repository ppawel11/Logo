import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Window 2.12

import TKOM 1.0 as TKOM

ApplicationWindow{
    id: root
    visible: true
    title: qsTr("TKOM")

    minimumWidth: 800
    minimumHeight: 600

    background: Rectangle{ color: "white" }

    TKOM.DrawingController {
        id: drawing_controller

        marker_pos_x: canvas.marker_x
        marker_pos_y: canvas.marker_y

        onDrawLine_: canvas.draw_line( length )
        onReset_: canvas.reset()
        onClear_: canvas.clear()
        onDrawCircle: canvas.draw_circle( radius )

    }

    ColumnLayout {
        anchors.fill: parent

        Canvas {
            id: canvas
            Layout.fillWidth: true
            Layout.fillHeight: true

            property real marker_x: width / 2
            property real marker_y: height / 2

            property bool first_draw: true

            visible: true

            onPaint: {
                if( first_draw )
                {
                    var ctx = getContext('2d');
                    ctx.reset();
                    first_draw = false;
                }
            }

            function draw_line( length ) {
                var delta_x = length * Math.cos( drawing_controller.marker_rotation * Math.PI / 180 );
                var delta_y = length * Math.sin( drawing_controller.marker_rotation * Math.PI / 180 );

                if( drawing_controller.is_drawing ) {
                    var ctx = getContext('2d');

                    ctx.strokeStyle = 'black';
                    ctx.lineWidth = 2;

                    ctx.beginPath();
                    ctx.moveTo(marker_x, marker_y);
                    ctx.lineTo(marker_x + delta_x, marker_y + delta_y );
                    ctx.stroke();

                    requestPaint();
                }

                marker_x = marker_x + delta_x;
                marker_y = marker_y + delta_y;
            }

            function reset() {
                marker_x = width / 2;
                marker_y = height / 2;
            }

            function clear() {
                first_draw = true;
                requestPaint();
            }

            function draw_circle( radius ) {
                if( drawing_controller.is_drawing ) {
                    var ctx = getContext('2d');

                    ctx.strokeStyle = 'black';
                    ctx.lineWidth = 2;
                    ctx.beginPath();
                    //ctx.moveTo(marker_x, marker_y);
                    ctx.arc(marker_x, marker_y, radius, 0 , 360);
                    ctx.stroke();
                    requestPaint();
                }
            }
        }



        ScrollView {
            id: scrollView
            Layout.fillWidth: true
            Layout.maximumHeight: 200
            Layout.minimumHeight: 200

            TextArea{
                id: code
                implicitHeight: 200
                placeholderText: "Let the code begin..."

            }
        }


        Button {
            height: 100
            Layout.fillWidth: true
            id: run
            text: qsTr("run")

            onClicked: {

            }
        }

        Button {
            height: 100
            Layout.fillWidth: true
            id: line
            text: qsTr("line")

            onClicked: {
                drawing_controller.draw_line(100);
            }
        }

        Button {
            height: 100
            Layout.fillWidth: true
            id: reset_
            text: qsTr("reset")

            onClicked: {
                drawing_controller.reset();
            }
        }

        Button {
            height: 100
            Layout.fillWidth: true
            id: switch_
            text: qsTr("switch")

            onClicked: {
                drawing_controller.switch_mode();
            }
        }

        Button {
            height: 100
            Layout.fillWidth: true
            id: clear_
            text: qsTr("clear")

            onClicked: {
                drawing_controller.clear();
            }
        }

        Button {
            height: 100
            Layout.fillWidth: true
            id: circle_
            text: qsTr("circle")

            onClicked: {
                drawing_controller.draw_circle( 100 );
            }
        }

        Button {
            height: 100
            Layout.fillWidth: true
            id: aa_
            text: qsTr("print kod")

            onClicked: {
                console.log(code.text);
            }
        }
    }

}
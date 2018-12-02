import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Layouts 1.11
import RCProject 1.0

RCWindow {
	visible: true
	width: 700
	height: 500
	title: qsTr("Root Classification")
	RowLayout {
		anchors.fill: parent
		Rectangle {
			id: panel
			color: 'gray'
			width: 200
			Layout.fillHeight: true
		}
		CCViewer {
			Layout.fillWidth: true
			Layout.fillHeight: true
			MouseArea {
				property real old_x: 0
				property real old_y: 0
				anchors.fill: parent
				acceptedButtons: Qt.AllButtons
				onWheel: {
					wheel.accepted = true
					if (wheel.angleDelta.y > 0)
						parent.d *= 1.1
					else
						parent.d /= 1.1
				}
				onPositionChanged: {
					mouse.accepted = true
					switch (mouse.buttons) {
					case Qt.LeftButton:
						var a1 = parent.a1 + (mouse.y - old_y) / 2
						if (a1 > 89)
							parent.a1 = 89
						else if (a1 < -89)
							parent.a1 = -89
						else
							parent.a1 = a1
						parent.a2 = (parent.a2 + (mouse.x - old_x) / 2) % 360
						break
					case Qt.RightButton:
						break
					}
					old_x = mouse.x
					old_y = mouse.y
				}
				onPressed: {
					old_x = mouse.x
					old_y = mouse.y
				}
			}
		}
	}
}

import QtQuick 2.11

Column {
	property var listmodel
	property int current
	width: panel.width - panel.d * 2
	height: panel.h + panel.d * 2 + 1
	Rectangle {
		color: (current == index) ? "white" : "gray"
		width: panel.width - panel.d * 2
		height: panel.h + panel.d * 2
		Row {
			anchors.centerIn: parent
			spacing: panel.d
			padding: panel.d
			Rectangle {
				width: panel.h
				height: panel.h
				color: Qt.rgba(c.x, c.y, c.z)
				radius: panel.h / 2
			}
			LabelValue {
				value: xyz.x
			}
			LabelValue {
				value: xyz.y
			}
			LabelValue {
				value: xyz.z
			}
			LabelValue {
				value: r
			}
			IconButton {
				src: "qrc:/img/delete.png"
				onClicked: {
					listmodel.remove(index)
				}
			}
		}
	}
	Item {
		width: panel.width - panel.d * 2
		height: 1
	}
}

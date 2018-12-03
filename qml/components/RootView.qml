import QtQuick 2.11

Column {
	width: panel.width - panel.d * 2
	height: panel.h + panel.d * 2 + 1
	Rectangle {
		color: "white"
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
			}
		}
	}
	Item {
		width: panel.width - panel.d * 2
		height: 1
	}
}

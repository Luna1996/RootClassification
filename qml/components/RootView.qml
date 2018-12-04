import QtQuick 2.11

Column {
	property int current
	property var onSelect
	property var onDelete
	width: panel.width - panel.d * 2
	height: panel.h + panel.d * 2 + 1
	Rectangle {
		color: (current === index) ? Qt.rgba(.9, .9, .9) : "white"
		width: panel.width - panel.d * 2
		height: panel.h + panel.d * 2
		MouseArea {
			anchors.fill: parent
			onClicked: {
				onSelect(index, [r, g, b, mx, my, mz, d])
			}
		}
		Row {
			anchors.centerIn: parent
			spacing: panel.d
			padding: panel.d
			Rectangle {
				width: panel.h
				height: panel.h
				color: Qt.rgba(r, g, b)
				radius: panel.h / 2
			}
			LabelValue {
				text: mx.toFixed(0)
				onTextEdited: {
					if (text === '')
						mx = 0
					else
						mx = parseFloat(text)
					onSelect(index, [r, g, b, mx, my, mz, d])
				}
			}
			LabelValue {
				text: my.toFixed(0)
				onTextEdited: {
					if (text === '')
						my = 0
					else
						my = parseFloat(text)
					onSelect(index, [r, g, b, mx, my, mz, d])
				}
			}
			LabelValue {
				text: mz.toFixed(0)
				onTextEdited: {
					if (text === '')
						mz = 0
					else
						mz = parseFloat(text)
					onSelect(index, [r, g, b, mx, my, mz, d])
				}
			}
			LabelValue {
				text: d.toFixed(0)
				onTextEdited: {
					if (text === '')
						d = 0
					else
						d = parseFloat(text)
					onSelect(index, [r, g, b, mx, my, mz, d])
				}
			}
			IconButton {
				background: Rectangle {
					color: Qt.rgba(.8, .1, .1)
				}
				src: "qrc:/img/delete.png"
				onClicked: {
					onDelete(index)
				}
			}
		}
	}
	Item {
		width: panel.width - panel.d * 2
		height: 1
	}
}

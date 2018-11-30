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
			objectName: "ccviewer"
			Layout.fillWidth: true
			Layout.fillHeight: true
		}
	}
}

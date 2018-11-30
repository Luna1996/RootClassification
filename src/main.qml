import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Layouts 1.11
import RCProject 1.0

Window {
	visible: true
	visibility: "FullScreen"
	title: qsTr("Root Classification")
	RowLayout {
		anchors.fill: parent
		Rectangle {
			color: 'gray'
			Layout.preferredWidth: 200
			Layout.fillHeight: true
		}
		CCViewer {
			Layout.fillWidth: true
			Layout.fillHeight: true
		}
	}
}

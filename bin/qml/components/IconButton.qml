import QtQuick 2.9
import QtQuick.Controls 2.4

Button {
	property real size: 25
	property string src
	width: size
	height: size
	Image {
		anchors.centerIn: parent
		source: parent.src
	}
}

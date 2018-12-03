import QtQuick 2.11
import QtQuick.Controls 2.4

TextField {
	property real value
	width: 40
	height: 25
	padding: 0
	text: value.toFixed(0)
}

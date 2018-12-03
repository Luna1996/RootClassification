import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQml.Models 2.3
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.2
import QtQuick.Layouts 1.11
import RCProject 1.0
import "./components"

RCWindow {
	id: window
	visible: true
	visibility: "Maximized"
	title: "Root Classification"
	RowLayout {
		spacing: 0
		anchors.fill: parent
		Item {
			id: panel
			property int w: 250
			property int d: 5
			property int h: 25
			width: panel.w
			Layout.fillHeight: true
			Rectangle {
				anchors.fill: parent
				color: "gray"
			}
			MouseArea {
				anchors.fill: parent
				onPressed: {
					viewer.forceActiveFocus()
				}
			}
			Column {
				spacing: panel.d
				padding: panel.d
				anchors.fill: parent
				Title {
					text: "File"
				}
				Row {
					spacing: panel.d
					TextField {
						enabled: false
						width: panel.w - 3 * panel.d - panel.h
						height: panel.h
						text: filepicker.fileUrl
					}
					IconButton {
						src: "qrc:/img/folder-open.png"
						onClicked: {
							filepicker.open()
						}
					}
					FileDialog {
						id: filepicker
						nameFilters: ["Root Data(*.ply)"]
						selectMultiple: false
						onAccepted: {
							window.setData(fileUrl)
						}
					}
				}
				Rectangle {
					color: "white"
					width: panel.w - 2 * panel.d
					height: 1
				}
				Title {
					text: "Roots"
				}
				Row {
					spacing: 5
					IconButton {
						src: "qrc:/img/refresh.png"
						onClicked: window.refresh()
					}
					IconButton {
						src: "qrc:/img/plus.png"
						onClicked: {
							root_model.append({
																	"c": Qt.vector3d(1, 0, 0),
																	"xyz": Qt.vector3d(0, 0, 0),
																	"r": 10
																})
						}
					}
				}
				Rectangle {
					objectName: "root_list"
					color: Qt.rgba(.8, .8, .8)
					width: panel.width - panel.d * 2
					height: 500
					function append(root) {
						root_model.append(root)
					}
					ListView {
						model: ListModel {
							id: root_model
						}
						anchors.fill: parent
						delegate: RootView {
						}
					}
				}
			}
		}
		CCViewer {
			id: viewer
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
						parent.a1 = (parent.a1 - (mouse.x - old_x) / 2) % 360

						var a2 = parent.a2 + (mouse.y - old_y) / 2
						if (a2 > 89)
							parent.a2 = 89
						else if (a2 < -89)
							parent.a2 = -89
						else
							parent.a2 = a2
						break
					case Qt.RightButton:
						break
					}
					old_x = mouse.x
					old_y = mouse.y
				}
				onPressed: {
					parent.forceActiveFocus()
					parent.show_center = true
					old_x = mouse.x
					old_y = mouse.y
				}
				onReleased: {
					parent.show_center = false
				}
			}
		}
	}
}

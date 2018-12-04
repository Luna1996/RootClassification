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
							root_list.currentIndex = root_model.append({
																													 "r": Math.random(),
																													 "g": Math.random(),
																													 "b": Math.random(),
																													 "mx": 0,
																													 "my": 0,
																													 "mz": 0,
																													 "d": 20
																												 })
						}
					}
					IconButton {
						src: "qrc:/img/check.png"
						onClicked: {
							var r1 = root_model.get(0)
							var r2 = root_model.get(1)
							window.runAlgorithm(r1.mx, r1.my, r1.mz, r2.mx, r2.my, r2.mz,
																	r1.r, r1.g, r1.b, r2.r, r2.g, r2.b,
																	r1.d, r2.d)
						}
					}
				}
				Rectangle {
					color: Qt.rgba(.8, .8, .8)
					width: panel.width - panel.d * 2
					height: 500
					ListView {
						id: root_list
						objectName: "root_list"
						currentIndex: -1
						function append(root) {
							root_model.append(root)
						}
						function clearRoot() {
							root_model.clear()
						}
						model: ListModel {
							id: root_model
						}
						anchors.fill: parent
						delegate: RootView {
							m_window: window
							current: root_list.currentIndex
							onSelect: function (i, o) {
								if (root_list.currentIndex === i) {
									root_list.currentIndex = -1
									window.clearSphere()
								} else {
									root_list.currentIndex = i
									window.setSphere(o[0], o[1], o[2], o[3], o[4], o[5], o[6])
								}
							}
							onDelete: function (i) {
								root_model.remove(i)
								window.clearSphere()
							}
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

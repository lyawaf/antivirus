// Components/CollapseFrame.qml
import QtQuick 2.9
import QtQuick.Controls 2.2

// A frame with a button that collapses/opens it
// The item resizes to fit the button and frame content

Frame {
	id: collapseFrame

	property bool   collapsed:         false
	property string showText:          qsTr("Show")
	property string collapseText:      qsTr("Collapse")
	property alias  animationDuration: animation.duration

	// text to show on buttons toggling this frame
	readonly property string currentText: collapsed ? showText : collapseText

	clip: true
	visible: height > 0

	Behavior on height {
		NumberAnimation {id: animation}
	}

	states: State {
		name: "collapsed"
		when: collapseFrame.collapsed
		PropertyChanges { target: collapseFrame; height: 0 }
	}
}

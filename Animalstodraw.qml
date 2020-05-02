import QtQuick 2.12
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3

import myNature2 1.0


Item{
    property int valueimage3: -1
    property int valueimage2: -1
    property int valueimage1: -1
    property bool arewelapin : true
    property bool areweladies : true
    property var territoryIndex

    Animaltodraw {
        id: animal1
        height:
            if(valueimage3!==-1){
                Math.min(parent.height, parent.width) / 3
            } else if(valueimage2!==-1) {
                Math.min(parent.height, parent.width) / 2
            } else {
                Math.min(parent.height, parent.width)
            }

        width: height
        anchors.left: parent.left
        anchors.top: parent.top
        valueImage: valueimage1
        amialady:areweladies
        amialapin:arewelapin
        orderInAnimals:0
    }
    Animaltodraw {
        id: animal2
        height: animal1.height
        width: height
        visible: valueimage2!==-1
        anchors.left: animal1.right
        anchors.top: parent.top
        valueImage: valueimage2
        amialady:areweladies
        amialapin:arewelapin
        orderInAnimals:1
    }
    Animaltodraw {
        id: animal3
        height: animal1.height
        width: height
        visible: valueimage3!==-1
        anchors.left: animal2.right
        anchors.top: parent.top
        valueImage: valueimage3
        amialady:areweladies
        amialapin:arewelapin
        orderInAnimals:2
    }

}

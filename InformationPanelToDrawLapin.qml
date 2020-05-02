import QtQuick 2.0
import QtQuick.Controls 2.4


Popup{

    property int cellIndex:0
    property string imageSource: "bug.png"
    property int currentAnimalId: -1
    property int pixelsize: 12
    height: myModel.nbPixelPerTerritory * 2
    width: myModel.nbPixelPerTerritory * 3
    visible: false



    Column {
        anchors.left: parent.left
        anchors.top: parent.top
        height: parent.height
        width: Math.round(parent.width * 2 / 3)

        Text {
            width:parent.width
            text : "ID, age, woman : "
            font.bold: true
            font.pixelSize: pixelsize
            horizontalAlignment: Text.AlignRight
        }

        Text {
            width:parent.width
            text : "Life level : "
            font.bold: true
            font.pixelSize: pixelsize
            horizontalAlignment: Text.AlignRight
        }

        Text {
            width:parent.width
            text : "hourglass (max) : "
            font.bold: true
            font.pixelSize: pixelsize
            horizontalAlignment: Text.AlignRight
        }
    }

    Column {
        anchors.right: parent.right
        anchors.top: parent.top
        height: parent.height
        width: Math.round(parent.width * 1 / 3)

        Text {
            width:parent.width
            font.pixelSize: pixelsize
            horizontalAlignment: Text.Alignleft
            text:
                if(myModel.lapinToBeEdited !== null)
                {myModel.lapinToBeEdited.rabbitId + ", " + myModel.lapinToBeEdited.age + ", " + myModel.lapinToBeEdited.woman}
                else
                {""}
        }

        Text {
            width:parent.width
            font.pixelSize: pixelsize
            horizontalAlignment: Text.Alignleft
            text: if(myModel.lapinToBeEdited !== null) {myModel.lapinToBeEdited.lifeLevel} else {""}
        }

        Text {
            width:parent.width
            font.pixelSize: pixelsize
            horizontalAlignment: Text.Alignleft
            text: if(myModel.lapinToBeEdited !== null)
                  { Math.round(myModel.lapinToBeEdited.lifehourglassdependingonage)  + " ("+ Math.round(myModel.lapinToBeEdited.lifehourglass) + ")"}
                  else {""}
        }
    }
    Image {
        height: parent.height
        width: parent.width
        fillMode: Image.PreserveAspectFit
        source: imageSource
        opacity: 0.3
    }


}

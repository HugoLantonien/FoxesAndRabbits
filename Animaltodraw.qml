import QtQuick 2.0
import QtQuick.Layouts 1.3


Item {
    property bool amialapin : true
    property bool amialady : true
    property int valueImage: -1
    property var territoryIndex
    property int orderInAnimals

    territoryIndex : parent.territoryIndex
    visible: valueImage!==-1

    Image {
        id : animalImage
        height: parent.height
        width: height
        anchors.left: parent.left
        anchors.top: parent.top
        fillMode: Image.PreserveAspectFit
        source:
            if(valueImage !== -1 ) {
                if(amialapin) {
                    if(amialady) {
                        "rabbit1" + valueImage + ".png";
                    } else {
                        "rabbit2" + valueImage + ".png";
                    }
                } else {
                    if(amialady) {
                        "fox1" + valueImage + ".png";
                    } else {
                        "fox2" + valueImage + ".png";
                    }
                }
            }else {
                "bug.png";
            }
    }

    MouseArea {
        enabled: valueImage!==-1
        height: parent.height
        width: height
        anchors.left: parent.left
        anchors.top: parent.top
        onClicked:  {

            if(amialapin)
            {
                informationPanelRenard.currentAnimalId = -1;
                informationPanelRenard.visible = false;
                myModel.renardToBeEdited = null;

                if(
                   (informationPanelLapin.visible === true) &&
                   (informationPanelLapin.currentAnimalId === myModel.getLapinInATerritory(index, amialady, orderInAnimals).rabbitid))
                {
                    informationPanelLapin.currentAnimalId = -1;
                    informationPanelLapin.visible = false;
                    myModel.lapinToBeEdited = null;
                }
                else
                {
                    informationPanelLapin.parent = animalImage
                    informationPanelLapin.x = Math.round(animalImage.width)
                    informationPanelLapin.y = Math.round(-informationPanelLapin.height)
                    informationPanelLapin.imageSource = animalImage.source

                    myModel.lapinToBeEdited = myModel.getLapinInATerritory(index, amialady, orderInAnimals);
                    informationPanelLapin.currentAnimalId = myModel.lapinToBeEdited.rabbitId

                    informationPanelLapin.visible = true
                }

            }
            else
            {

                informationPanelLapin.currentAnimalId = -1;
                informationPanelLapin.visible = false;
                myModel.lapinToBeEdited = null;

                if(
                   (informationPanelRenard.visible === true) &&
                   (informationPanelRenard.currentAnimalId === myModel.getRenardInATerritory(index, amialady, orderInAnimals).foxid))
                {

                    informationPanelRenard.currentAnimalId = -1;
                    informationPanelRenard.visible = false;
                    myModel.renardToBeEdited = null;

                }
                else
                {
                    informationPanelRenard.parent = animalImage
                    informationPanelRenard.x = Math.round(animalImage.width)
                    informationPanelRenard.y = Math.round(-informationPanelRenard.height)
                    informationPanelRenard.imageSource = animalImage.source

                    myModel.renardToBeEdited = myModel.getRenardInATerritory(index, amialady, orderInAnimals);
                    informationPanelRenard.currentAnimalId = myModel.renardToBeEdited.foxid

                    informationPanelRenard.visible = true
                }

            }

        }
    }

}


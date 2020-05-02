import QtQuick 2.12
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import myNature2 1.0


ColumnLayout {
    anchors.centerIn:  parent
    visible: true
    property var territoriesSize : myModel.nbPixelPerTerritory * myModel.nbTerritoriesDisplayedInFrame
    property var animalIconSize: myModel.nbPixelPerTerritory/2

    Frame {
        Layout.preferredHeight:  territoriesSize
        Layout.preferredWidth:   territoriesSize
        clip:true

        TerritoriesToDraw{
            id : myModel
            territorriesList : territoriesQml
        }

        TableView {
            id:myGrid

            height: territoriesQml.nbRowsOfTerritories * (myModel.nbPixelPerTerritory + 0.5)
            width: territoriesQml.nbColumnsOfTerritories * (myModel.nbPixelPerTerritory + 0.5)

            anchors.fill: parent
            clip: true
            model: myModel

            delegate: cellDelegate

            Component  {
                id : cellDelegate

                Item {

                implicitHeight: myModel.nbPixelPerTerritory
                implicitWidth:  myModel.nbPixelPerTerritory

                Rectangle{
                    id:rectangle1
                    height: parent.height
                    width : parent.width
                    color: if(model.grasslevel===6){
                               "darkgreen"
                           } else if(model.grasslevel===5){
                               "forestgreen"
                           } else if(model.grasslevel===4){
                               "green"
                           } else if(model.grasslevel===3){
                               "aquamarine"
                           } else if(model.grasslevel===3){
                               "darkolivegreen"
                           } else if(model.grasslevel===2){
                               "darkkhaki"
                           } else if(model.grasslevel===1){
                               "goldenrod"
                           } else if(model.grasslevel===0){
                               "gold"
                           }
                    border.width: 0

                    Animalstodraw{
                        id:ladiesfoxes
                        height: parent.height/2
                        width: parent.width/2
                        anchors.left: parent.left
                        anchors.top: parent.top
                        valueimage3: model.ladyfox3
                        valueimage2: model.ladyfox2
                        valueimage1: model.ladyfox1
                        territoryIndex:myModel.index(index,0)
                        arewelapin : false
                        areweladies : true
                    }

                    Animalstodraw{
                        id:gentlemenfoxes
                        height: parent.height/2
                        width: parent.width/2
                        anchors.left: ladiesfoxes.right
                        anchors.top: parent.top
                        valueimage3: model.gentlemanfox3
                        valueimage2: model.gentlemanfox2
                        valueimage1: model.gentlemanfox1
                        territoryIndex:myModel.index(index,0)
                        arewelapin : false
                        areweladies : false
                    }

                    Animalstodraw{
                        id:ladiesrabbit
                        height: parent.height/ 2
                        width: parent.width/2
                        anchors.left: ladiesfoxes.left
                        anchors.top: ladiesfoxes.bottom
                        valueimage3: model.ladyrabbit3
                        valueimage2: model.ladyrabbit2
                        valueimage1: model.ladyrabbit1
                        territoryIndex:myModel.index(index,0)
                        arewelapin : true
                        areweladies : true
                    }

                    Animalstodraw{
                        id:gentlemenrabbit
                        height: parent.height/ 2
                        width: parent.width/2
                        anchors.left: ladiesrabbit.right
                        anchors.top: ladiesrabbit.top
                        valueimage3: model.gentlemanrabbit3
                        valueimage2: model.gentlemanrabbit2
                        valueimage1: model.gentlemanrabbit1
                        territoryIndex:myModel.index(index,0)
                        arewelapin : true
                        areweladies : false
                    }
                }
            }
            }
            ScrollBar.horizontal: ScrollBar {
                parent: myGrid.parent
                anchors.left: myGrid.left
                anchors.right: myGrid.right
                anchors.top: myGrid.top
            }
            ScrollBar.vertical: ScrollBar {
                parent: myGrid.parent
                anchors.bottom: myGrid.bottom
                anchors.right: myGrid.right
                anchors.top: myGrid.top
            }

        }
    }


    property int mycounter: 1
    property int nbyearstoplay: yearCounterQml.nbOfYearToPlay
    property int nbyearstoplayiterator: 10

    RowLayout {
        id:lowrowlayout

        function eraseBeforeYearsToGo() {

            informationPanelRenard.currentAnimalId = -1;
            informationPanelRenard.visible = false;
            myModel.renardToBeEdited = null;

            informationPanelLapin.currentAnimalId = -1;
            informationPanelLapin.visible = false;
            myModel.lapinToBeEdited = null;
        }

        Timer {
            id: timer
            interval : 300
            repeat : true
            running : false

            onTriggered: {
                yearCounterQml.playYears(1);
                myModel.reDraw();
                myGrid.forceLayout();
                if(mycounter>=nbyearstoplay)  {
                    timer.running = false;
                    mycounter=1;
                } else {
                    mycounter=mycounter + 1;
                }

            }
        }

        Button{
            autoRepeatDelay:100
            autoRepeat: true
            text: qsTr("--")
            Layout.fillWidth: true
            onClicked: {
                if(yearCounterQml.nbOfYearToPlay < nbyearstoplayiterator)
                    yearCounterQml.nbOfYearToPlay = 0;
                else
                    yearCounterQml.nbOfYearToPlay -= nbyearstoplayiterator
            }
        }

        Button{
            text: qsTr("add ") + yearCounterQml.nbOfYearToPlay
            Layout.fillWidth: true
            onClicked: {

                lowrowlayout.eraseBeforeYearsToGo();

                yearCounterQml.playYears(nbyearstoplay);
                myModel.reDraw();
                myGrid.forceLayout();

            }
        }

        Button{
            text: qsTr("add Show ") + yearCounterQml.nbOfYearToPlay
            Layout.fillWidth: true
            onClicked: {
                lowrowlayout.eraseBeforeYearsToGo();
                timer.running = true;
            }
        }

        Button{
            autoRepeatDelay:100
            autoRepeat: true
            text: qsTr("++")
            Layout.fillWidth: true
            onClicked: {
                yearCounterQml.nbOfYearToPlay += nbyearstoplayiterator
            }
        }

        Button{
            text: qsTr(">>")
            Layout.fillWidth: true
            onClicked: {
                territoriesColumn.visible = false;
                chartColumn.visible = true;
            }
        }
    }
    InformationPanelToDrawRenard {
        id:informationPanelRenard
    }
    InformationPanelToDrawLapin {
        id:informationPanelLapin
    }

}



import QtQuick.Layouts 1.3
import QtQuick.Controls 2.4
import QtQuick 2.12
import QtCharts 2.3
import myNature2 1.0

ColumnLayout {
    visible: false
    anchors.centerIn:  parent
    property var chartWidth
    property var iconSize
    property var graphicCounter: 0

    onVisibleChanged: {
        if(visible)
            myChartView.changeChartView();
    }

    Text {
        Layout.preferredWidth:chartWidth
        Layout.alignment: Qt.AlignHCenter
        font.pixelSize: 20
        horizontalAlignment: Text.AlignVCenter
        text: chartDatasQml.graphDescription
        wrapMode: Text.Wrap
    }

    Frame {
        Layout.preferredHeight:   chartWidth
        Layout.preferredWidth:   chartWidth
        Layout.alignment: Qt.AlignHCenter

        ChartView {
            id : myChartView
            title: chartDatasQml.graphTitle
            titleFont.pixelSize: 24
            anchors.fill: parent
            legend.font.pixelSize: 20

            ValueAxis {
                id: axisX
                max: chartDatasQml.xMax
                min:0
            }

            ValueAxis {
                id: axisY
                max: chartDatasQml.valueMax
                min:chartDatasQml.valueMin

            }

            function changeChartView() {

                chartDatasQml.prepareGraphics(graphicCounter);
                myChartView.removeAllSeries();
                for(var i=0 ; i < chartDatasQml.numberOfSeries ; i++)
                {
                    var mySeries = myChartView.createSeries(ChartView.SeriesTypeLine, "shall not be displayed", axisX, axisY);
                    console.log("changeChartView : " + i + "/" + chartDatasQml.numberOfSeries + " animal : " + chartDatasQml.animal )
                    chartDatasQml.prepareSerie(mySeries, i);
                    switch(i) {
                    case 0 : mySeries.color= "darkblue"; break;
                    case 1 : mySeries.color="darkred"; break;
                    case 2 : mySeries.color="darkviolet"; break;
                    default : mySeries.color="hotpink"; break;
                    }
                 }
            }
        }
    }


    RowLayout{


        Button{
            text: qsTr("<<")
            Layout.fillWidth: true
            onClicked: {
                territoriesColumn.visible = true;
                chartColumn.visible = false;
            }
        }

        Rectangle
        {
            Layout.preferredHeight: iconSize
            Layout.preferredWidth: iconSize

            Button{
                id:buttonAnimal
                anchors.fill: parent
                onClicked: {
                    if(chartDatasQml.animal === ChartDatas.Animal_fox)
                        chartDatasQml.animal = ChartDatas.Animal_rabbit;
                    else
                        chartDatasQml.animal = ChartDatas.Animal_fox;

                    myChartView.changeChartView();
                }
            }
            Image {
                anchors.fill: parent
                fillMode: Image.PreserveAspectFit
                source: {
                    if(chartDatasQml.animal === ChartDatas.Animal_fox)
                        "fox10.png";
                    else
                        "rabbit10.png";
                }
            }
        }

        Button{
            text: "Next " + chartDatasQml.currentChartNumber
            Layout.fillWidth: true
            onClicked: {
                graphicCounter++;
                myChartView.changeChartView();
            }
        }
    }
}

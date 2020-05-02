import QtQuick 2.12
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2
import QtCharts 2.3

import myNature2 1.0

ApplicationWindow {
    visible: true
    width: 1280
    height: 960
    title: qsTr("Tabs")

    Territoriesgridtodraw {
        id:territoriesColumn
    }
    Chartstodraw {
        id:chartColumn
        chartWidth : territoriesColumn.territoriesSize
        iconSize: territoriesColumn.animalIconSize
    }



}

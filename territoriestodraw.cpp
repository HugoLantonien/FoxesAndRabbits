#include "territoriestodraw.h"
#include "territory.h"
#include <QDebug>




unsigned int TerritoriesToDraw::getNbIconToDrawFoxes()
{
    return nbIconToDrawFoxes;
}

unsigned int TerritoriesToDraw::getNbIconToDrawRabbits()
{
    return nbIconToDrawRabbits;
}

unsigned int TerritoriesToDraw::getNbPixelPerTerritory()
{
    return nbPixelPerTerritory;
}

TerritoriesToDraw::TerritoriesToDraw(QObject *parent)
    : QAbstractListModel(parent),
      m_territorries(nullptr),
      m_lapinToBeEdited(nullptr),
      m_renardToBeEdited(nullptr)
{
    qDebug() << "TerritoriesToDraw created here";

}

int TerritoriesToDraw::rowCount(const QModelIndex &parent) const
{
    bool log = false;
    if (parent.isValid() || m_territorries == nullptr)
        return 0;
    if(log)
        qDebug() << "Nb of Rows = "  << Territories::nbRowsOfTerritories * Territories::nbColumnsOfTerritories;

    return Territories::nbRowsOfTerritories; //* Territories::nbColumnsOfTerritories;
}

#ifdef TABLE_VIEW_ON
int TerritoriesToDraw::columnCount(const QModelIndex &parent) const
{
    bool log = false;
    if (parent.isValid() || m_territorries == nullptr)
        return 0;

    if(log)
        qDebug() << "Nb of Columns = "  << Territories::nbColumnsOfTerritories;

    return Territories::nbColumnsOfTerritories;

}
#endif



QVariant TerritoriesToDraw::data(const QModelIndex &index, int role) const
{


    if (!index.isValid() || m_territorries == nullptr)
        return QVariant();

    int myRow = index.row();

#ifdef TABLE_VIEW_ON
    int myColumn = index.column();

#else
    //if gridview or listview
    myRow = myRow / Territories::nbRowsOfTerritories;
    int myColumn = index.row() - myRow * Territories::nbRowsOfTerritories;
#endif

    Territory *myTerritory = m_territorries->m_territories[myRow][myColumn];

    bool log = false;

    switch (role) {

    case LadyFox1:
    case LadyFox2:
    case LadyFox3:
    {
        if (log)
            qDebug() << "requesting LadyFox(" << index.row() << "=" << myRow << ", " << myColumn << ")" ;

        Renard *myFox = myTerritory->getASpecificFox(true, 0 + role - LadyFox1);
        if(myFox == nullptr) {
            return -1;
        }
        else {
            return QVariant(myFox->getIcon());
        }
    }
    case GentlemanFox1:
    case GentlemanFox2:
    case GentlemanFox3:
    {
        Renard *myFox = myTerritory->getASpecificFox(false, 0 + role - GentlemanFox1);
        if(myFox == nullptr) {
            return -1;
        }
        else {
            if (log)
                qDebug() << "requesting GentlemanFox(" << myRow << ", " << myColumn << ") = " << myFox->getIcon() ;
            return QVariant(myFox->getIcon());
        }
    }
    case LadyRabbit1:
    case LadyRabbit2:
    case LadyRabbit3:
    {
        Lapin *myRabbit = myTerritory->getASpecificRabbit(true, 0 + role - LadyRabbit1);
        if(myRabbit == nullptr) {
            return -1;
        }
        else {
            if (log)
                qDebug() << "requesting LadyRabbit(" << myRow << ", " << myColumn << ") = " << myRabbit->getIcon() ;
            return QVariant(myRabbit->getIcon());
        }
    }
    case GentlemanRabbit1:
    case GentlemanRabbit2:
    case GentlemanRabbit3:
    {
        if (log)
            qDebug() << "requesting GentlemanRabbit(" << index.row() << "=" << myRow << ", " << myColumn << ")" ;

        Lapin *myRabbit = myTerritory->getASpecificRabbit(false, 0 + role - GentlemanRabbit1);
        if(myRabbit == nullptr) {
            return -1;
        }
        else {
            return QVariant(myRabbit->getIcon());
        }
    }
    case GrassLevelRole:
    {
        if (log)
            qDebug() << "requesting grass level(" << index.row() << "=" << myRow << ", " << myColumn << ")" ;
        return QVariant(myTerritory->getGrassLevel());
    }
    }
    return QVariant();
}


/*
bool TerritoriesToDraw::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || m_territorries == nullptr)
        return false;

    int myRow = index.row();
    myRow = myRow / Territories::nbRowsOfTerritories;
    int myColumn = index.row() - myRow * Territories::nbRowsOfTerritories;

    Territory *myTerritory = m_territorries->m_territories[myRow][myColumn];

    bool log = false;

    qDebug() << role << " Got it " << value;

    switch (role) {
    case LadyFox1:
        qDebug() << role << " LadyFox1 ready to be updated" << value;
        return true;
    case LadyFox2:
    case LadyFox3:
    case GentlemanFox1:
    case GentlemanFox2:
    case GentlemanFox3:
    case LadyRabbit1:
    case LadyRabbit2:
    case LadyRabbit3:
    case GentlemanRabbit1:
    case GentlemanRabbit2:
    case GentlemanRabbit3:
    case GrassLevelRole:
        qDebug() << role << " role shall not be updated";
        return false;
    case LapinToBeDisplayed:
    case RenardToBeDisplayed:
        qDebug() << role << " Got it " << value;
        return  false;
   }

   return false;

}

Qt::ItemFlags TerritoriesToDraw::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}
*/

QHash<int, QByteArray> TerritoriesToDraw::roleNames() const
{

    QHash<int, QByteArray> names;
    names[LadyFox1] = "ladyfox1";
    names[LadyFox2] = "ladyfox2";
    names[LadyFox3] = "ladyfox3";
    names[GrassLevelRole] = "grasslevel";
    names[GentlemanFox1] = "gentlemanfox1";
    names[GentlemanFox2] = "gentlemanfox2";
    names[GentlemanFox3] = "gentlemanfox3";
    names[LadyRabbit1] = "ladyrabbit1";
    names[LadyRabbit2] = "ladyrabbit2";
    names[LadyRabbit3] = "ladyrabbit3";
    names[GentlemanRabbit1] = "gentlemanrabbit1";
    names[GentlemanRabbit2] = "gentlemanrabbit2";
    names[GentlemanRabbit3] = "gentlemanrabbit3";

    return  names;

}


Territories *TerritoriesToDraw::territorriesList() const
{
    return m_territorries;
}

void TerritoriesToDraw::setTerritorriesList(Territories *territorriesList)
{
    beginResetModel();

    if(m_territorries)
        m_territorries->disconnect(this);


    m_territorries = territorriesList;

    qDebug() << "setTerritorriesList = "  << territorriesList << "(" << Territories::getInstance() << ")";

    endResetModel();


}

Lapin *TerritoriesToDraw::lapinToBeEdited() const
{
    return m_lapinToBeEdited;
}

void TerritoriesToDraw::setLapinToBeEdited(Lapin *lapinToBeEdited)
{
    if(lapinToBeEdited != m_lapinToBeEdited) {
    m_lapinToBeEdited = lapinToBeEdited;
    emit lapinToBeEditedChanged();
    }

}

Lapin *TerritoriesToDraw::getLapinInATerritory(int index, bool woman, int numberInTerritory)
{
    bool log=true;

    int myColumn = index / Territories::nbRowsOfTerritories;
    int myRow = index - myColumn * Territories::nbRowsOfTerritories;

    Territory *myTerritory = m_territorries->m_territories[myRow][myColumn];

    Lapin *myRabbit = myTerritory->getASpecificRabbit(woman, numberInTerritory);

    if(log)
        qDebug() << "Territory (" << myRow << ", "  << myColumn << "), lapin woman(" << woman << "), nb (" << numberInTerritory << "), adress " << myRabbit;

    return myRabbit;
}

Renard *TerritoriesToDraw::renardToBeEdited() const
{
    return m_renardToBeEdited;
}

void TerritoriesToDraw::setRenardToBeEdited(Renard *renardToBeEdited)
{
    if(renardToBeEdited != m_renardToBeEdited) {
        m_renardToBeEdited = renardToBeEdited;
        emit renardToBeEditedChanged();
    }


}

Renard *TerritoriesToDraw::getRenardInATerritory(int index, bool woman, int numberInTerritory)
{
    bool log=true;

    int myColumn = index / Territories::nbRowsOfTerritories;
    int myRow = index - myColumn * Territories::nbRowsOfTerritories;

    Territory *myTerritory = m_territorries->m_territories[myRow][myColumn];

    Renard *myRenard = myTerritory->getASpecificFox(woman, numberInTerritory);

    if(log)
        qDebug() << "Territory (" << myRow << ", "  << myColumn << "), renard woman(" << woman << "), nb (" << numberInTerritory << "), adress " << myRenard;

    return myRenard;
}

unsigned int TerritoriesToDraw::getNbTerritoriesDisplayedInFrame()
{
    return nbTerritoriesDisplayedInFrame;
}

void TerritoriesToDraw::reDraw()
{

    emit dataChanged(index(0, 0), index(Territories::nbRowsOfTerritories - 1, Territories::nbColumnsOfTerritories - 1), {LadyFox1});
    emit dataChanged(index(0, 0), index(Territories::nbRowsOfTerritories - 1, Territories::nbColumnsOfTerritories - 1), {LadyFox2});
    emit dataChanged(index(0, 0), index(Territories::nbRowsOfTerritories - 1, Territories::nbColumnsOfTerritories - 1), {LadyFox3});
    emit dataChanged(index(0, 0), index(Territories::nbRowsOfTerritories - 1, Territories::nbColumnsOfTerritories - 1), {GentlemanFox1});
    emit dataChanged(index(0, 0), index(Territories::nbRowsOfTerritories - 1, Territories::nbColumnsOfTerritories - 1), {GentlemanFox2});
    emit dataChanged(index(0, 0), index(Territories::nbRowsOfTerritories - 1, Territories::nbColumnsOfTerritories - 1), {GentlemanFox3});
    emit dataChanged(index(0, 0), index(Territories::nbRowsOfTerritories - 1, Territories::nbColumnsOfTerritories - 1), {GentlemanRabbit1});
    emit dataChanged(index(0, 0), index(Territories::nbRowsOfTerritories - 1, Territories::nbColumnsOfTerritories - 1), {GentlemanRabbit2});
    emit dataChanged(index(0, 0), index(Territories::nbRowsOfTerritories - 1, Territories::nbColumnsOfTerritories - 1), {GentlemanRabbit3});
    emit dataChanged(index(0, 0), index(Territories::nbRowsOfTerritories - 1, Territories::nbColumnsOfTerritories - 1), {LadyRabbit1});
    emit dataChanged(index(0, 0), index(Territories::nbRowsOfTerritories - 1, Territories::nbColumnsOfTerritories - 1), {LadyRabbit2});
    emit dataChanged(index(0, 0), index(Territories::nbRowsOfTerritories - 1, Territories::nbColumnsOfTerritories - 1), {LadyRabbit3});
    emit dataChanged(index(0, 0), index(Territories::nbRowsOfTerritories - 1, Territories::nbColumnsOfTerritories - 1), {GrassLevelRole});

}


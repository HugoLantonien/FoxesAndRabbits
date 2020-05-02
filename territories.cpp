#include "territories.h"
#include "territory.h"
#include "animals.h"
#include "animal.h"
#include <QDebug>



Territories *Territories::instance = nullptr;


Territories::Territories(QObject *parent):
    QObject (parent)
{
    // Création des territories
    unsigned int i, j;

    for(i=0 ; i < Territories::nbRowsOfTerritories ; i++  )
    {
        for(j=0 ; j < Territories::nbColumnsOfTerritories ; j++  )
        {
            m_territories[i][j] = new Territory(j, i);
        }
    }

    // Affectation des pointeurs eastTerritory, westTerritory, northTerritory, southTerritory
    for(i=0 ; i < Territories::nbRowsOfTerritories ; i++  )
    {
        for(j=0 ; j < Territories::nbColumnsOfTerritories ; j++  )
        {
            if(j != 0)
            {
                m_territories[i][j]->eastTerritory = m_territories[i][j-1] ;
            }
            else
            {
                m_territories[i][j]->eastTerritory = m_territories[i][Territories::nbColumnsOfTerritories - 1] ;
            }

            if(j != Territories::nbColumnsOfTerritories - 1)
            {
                m_territories[i][j]->westTerritory = m_territories[i][j+1] ;
            }
            else
            {
                m_territories[i][j]->westTerritory = m_territories[i][0] ;
            }

            if(i != 0)
            {
                m_territories[i][j]->northTerritory = m_territories[i-1][j] ;
            }
            else
            {
                m_territories[i][j]->northTerritory = m_territories[Territories::nbRowsOfTerritories -1][j] ;
            }

            if(i != Territories::nbRowsOfTerritories - 1)
            {
                m_territories[i][j]->southTerritory = m_territories[i+1][j] ;
            }
            else
            {
                m_territories[i][j]->southTerritory = m_territories[0][j] ;
            }
        }
    }

}
void Territories::dropAnimalInARandomTerritory(Animal *animalToDrop)
{
    int i = Animals::randomInt(50, 100) * Territories::nbRowsOfTerritories / 100;
    if(i >= Territories::nbRowsOfTerritories)
    {
        i = Territories::nbRowsOfTerritories -1;
    }

    int j = Animals::randomInt(50, 100) * Territories::nbColumnsOfTerritories / 100;
    if(i >= Territories::nbRowsOfTerritories)
    {
        i = Territories::nbRowsOfTerritories -1;
    }

    animalToDrop->setAnimalTerritory(m_territories[i][j]);

}


Territories *Territories::getInstance()
{
    if(Territories::instance == nullptr)
    {
        Territories::instance = new Territories;
    }
    return Territories::instance;
}


void Territories::aYearOfHappeningInsideTerritories(void)
{
    for(int eastWest = 0 ; eastWest < Territories::nbColumnsOfTerritories ; eastWest++)
    {
        for(int northSouth = 0 ; northSouth < Territories::nbRowsOfTerritories ; northSouth++)
        {
            Territories::m_territories[northSouth][eastWest]->eatingTerritoryGrass();
            Territories::m_territories[northSouth][eastWest]->animalsConfrontationInsideTerritory();
        }
    }
}


double Territories::getValueOfNextTerroriesInAnimalsOdor()
{
    return valueOfNextTerroriesInAnimalsOdor;
}


int Territories::getTerritoriesNumber()
{
    return Territories::nbRowsOfTerritories * Territories::nbColumnsOfTerritories;
}

int Territories::getNbColumnsOfTerritories()
{
    return nbColumnsOfTerritories;
}

unsigned int Territories::getTotalAnimalsInTerritoriesByListCounter() const
{
    unsigned int counter = 0;
    for(int eastWest = 0 ; eastWest < Territories::nbColumnsOfTerritories ; eastWest++)
    {
        for(int northSouth = 0 ; northSouth < Territories::nbRowsOfTerritories ; northSouth++)
        {
            counter = counter + Territories::m_territories[northSouth][eastWest]->getListOfTerritoryAnimals()->getTotalAnimalsInList();
        }
    }
    return counter;
}

unsigned int Territories::getTotalAnimalsInTerritoriesByRecounting()
{
    unsigned int counter = 0;
    for(int eastWest = 0 ; eastWest < Territories::nbColumnsOfTerritories ; eastWest++)
    {
        for(int northSouth = 0 ; northSouth < Territories::nbRowsOfTerritories ; northSouth++)
        {
            counter = counter + Territories::m_territories[northSouth][eastWest]->getListOfTerritoryAnimals()->getTotalAnimalsInListByRecounting();
        }
    }
    return counter;
}

int Territories::getNbRowsOfTerritories()
{
    return nbRowsOfTerritories;
}

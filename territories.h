#pragma once

#ifndef TERRITORIES_H
#define TERRITORIES_H

#include <QObject>

class Territory;
class Animal;

class Territories : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int nbRowsOfTerritories READ getNbRowsOfTerritories CONSTANT)
    Q_PROPERTY(int nbColumnsOfTerritories READ getNbColumnsOfTerritories CONSTANT)

public:
    static Territories *getInstance();

    void dropAnimalInARandomTerritory(Animal *animalToDrop) ;
    void aYearOfHappeningInsideTerritories(void);

    static double getValueOfNextTerroriesInAnimalsOdor();

    static int getTerritoriesNumber();
    static int getNbRowsOfTerritories() ;
    static int getNbColumnsOfTerritories() ;

    unsigned int getTotalAnimalsInTerritoriesByListCounter() const;
    unsigned int getTotalAnimalsInTerritoriesByRecounting();

    static const int nbRowsOfTerritories  = 20;
    static const int nbColumnsOfTerritories = 20;
    Territory *m_territories[nbRowsOfTerritories] [nbColumnsOfTerritories];


private:
    Territories(QObject *parent = nullptr);
    static Territories *instance;

    static constexpr double valueOfNextTerroriesInAnimalsOdor = 0.25;


};


#endif // TERRITORIES_H

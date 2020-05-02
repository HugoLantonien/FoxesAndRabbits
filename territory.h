#pragma once

#ifndef TERRITORY_H
#define TERRITORY_H

#include <QObject>
#include "animalslist.h"
#include "territories.h"
#include "renard.h"
#include "lapin.h"


class Territory
{
   friend class Territories;

public:
    Territory(unsigned int positionEastWest, unsigned int positionSouthNorth);

    unsigned int positionEastWest() const;
    unsigned int positionSouthNorth() const;

    void animalsConfrontationInsideTerritory(void);
    void eatingTerritoryGrass(void);

    void addAnimalToTerritoryList(Animal *animalToAdd);
    bool removeAnimalFromTerritoryList(Animal *animalToRemove);
    AnimalsList *getListOfTerritoryAnimals() const;

    int getGrassLevel(void);

    double getSmellOfAnimalsReadyToMateWithMe(Animal *smellingAnimal);
    double getSmellOfAnimalReadyToFightWithMe(Animal *smellingAnimal);
    double getSmellOfAnimalsToHunt();
    double getSmellOfAnimalsHunters();
    double getSmellOfGrassOpportunity(Animal *smellingAnimal);

    Territory *getEastTerritory() const;
    Territory *getWestTerritory() const;
    Territory *getNorthTerritory() const;
    Territory *getSouthTerritory() const;

    Renard *getASpecificFox (bool lady, int number) const;
    Lapin *getASpecificRabbit (bool lady, int number) const;

private:

    typedef enum {
        E_closeTerritoriesMe,
        E_closeTerritoriesEast,
        E_closeTerritoriesWest,
        E_closeTerritoriesNorth,
        E_closeTerritoriesSouth,
        E_closeTerritoriesMax
    } E_closeTerritories;


    static double getSmellOfSomeAnimals(unsigned int *nbOf) ;
    double getSmellOfGrassEaters(Animal *animalSmelling, bool majGrassLevel);

    AnimalsList *m_listOfTerritoryAnimals;
    Territory *eastTerritory;
    Territory *westTerritory;
    Territory *northTerritory;
    Territory *southTerritory;
    unsigned int m_positionEastWest;
    unsigned int m_positionSouthNorth;

    int m_grassLevel;

    static int constexpr grownGrassEachYear = 2;
    static int constexpr maxGrassOnATerritory = 6;
};





#endif // TERRITORY_H

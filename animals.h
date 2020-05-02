
#ifndef ANIMALS_H
#define ANIMALS_H

#include "animal.h"
#include "animalslist.h"
#include "lapin.h"
#include "renard.h"
#include <QGlobal.h>
#include <QString>

class Animals
{
public:
    static Animals *getInstance();

    static int randomInt(int val1, int variationAcceptee);
    static double randomDouble(double val1, double variationAcceptee);
    static bool randomBool(void);
    static double getLifeHourglassDependingOnAge (
                                          int  age,
                                          double lifeHourglass_maximumValue,
                                          double lifeHourglass_ageMaximumValue,
                                          double lifeHourglass_birthDivisorFactor,
                                          double lifeHourglass_oldAge,
                                          double lifeHourglass_oldAgeDivisorFactor
            );


    void debugFunction(QString nomFonction);


    void deathWindOnAnimals();
    void moveToABetterPlace();

    unsigned int anAnimalIsBorn(Animal *bornAnimal);
    void anAnimalIsDead(Animal* deadAnimal);

    unsigned int getLivingAnimalsNb() const;
    unsigned int getTotalAnimalsNb() const;

    unsigned int getTotalAnimalsInAnimalsListByListCounter() const;          //for debug
    unsigned int getTotalAnimalsInAnimalsListByRecounting() ;   //for debug


    void addAnimalToDeleteList(Animal * theAnimalToAdd);

private:
    Animals();
    static Animals *instance;

    QVector <Animal *> m_animalsToDelete;

    AnimalsList listOfAllAnimals;

    unsigned int m_livingAnimalsNb = 0;
    unsigned int m_totalAnimalsNb = 0;
    static constexpr double initialNumberOfFoxesPerTerritory = 0.25;
    static constexpr double initialNumberOfRabbitsPerTerritory = 1;

};

#endif // ANIMALS_H



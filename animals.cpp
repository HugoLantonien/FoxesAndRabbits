#include "animals.h"
#include "renard.h"
#include "lapin.h"
#include <QDebug>
#include <QRandomGenerator>
#include "territories.h"
#include "territory.h"



Animals *Animals::instance = nullptr;


Animals::Animals():  listOfAllAnimals(AnimalsList())
{
    qDebug() << "Here is created the Animals" ;
    qDebug() ;

}



unsigned int Animals::getTotalAnimalsNb() const
{
    return m_totalAnimalsNb;
}

unsigned int Animals::getTotalAnimalsInAnimalsListByListCounter() const
{
    return this->listOfAllAnimals.getTotalAnimalsInList();
}

unsigned int Animals::getTotalAnimalsInAnimalsListByRecounting()
{
    return this->listOfAllAnimals.getTotalAnimalsInListByRecounting();
}

void Animals::addAnimalToDeleteList(Animal *theAnimalToAdd)
{
    bool log = false;

    m_animalsToDelete.append(theAnimalToAdd);

    if(log)
        qDebug() << "addAnimalToDeleteList : " << m_animalsToDelete.count() << " m_animalsToDelete";
}


unsigned int Animals::getLivingAnimalsNb() const
{
    return m_livingAnimalsNb;
}

Animals *Animals::getInstance()
{
    if(Animals::instance == nullptr)
    {
        Animals::instance = new Animals;

        int numberOfFoxes = static_cast <int>(Animals::initialNumberOfFoxesPerTerritory * Territories::getInstance()->getTerritoriesNumber());

        for(int f = 0 ; f < numberOfFoxes ; f++)
        {
            new Renard();
        }

        int numberOfRabbits = static_cast <int>(Animals::initialNumberOfRabbitsPerTerritory * Territories::getInstance()->getTerritoriesNumber());

        for(int f = 0 ; f < numberOfRabbits ; f++)
        {
            new Lapin();
        }
    }

    return Animals::instance;
}

void Animals::deathWindOnAnimals()
{
    bool log=false;
    Animal *currentAnimal;
    currentAnimal = listOfAllAnimals.getLastAnimalAddedAndMove();

    while(currentAnimal != nullptr)
    {
       if(currentAnimal->Getalive())
        {
           double initialLifeLevel = currentAnimal->lifeLevel() ;

           currentAnimal->faceToDeath();
           currentAnimal->annualDecreaseOfLifeLevel();

           if(log)
           {
               if(currentAnimal->Getalive())
               {

                   qDebug() << currentAnimal->coutLight() << " (" << initialLifeLevel << ")"
                            << " ===> " << " (" << currentAnimal->lifeLevel() << ")" ;
               }
           }

       }

       currentAnimal = listOfAllAnimals.getNextAnimalAddedAndMove();
    }

    // Suppression des animaux morts
    log=false;
    if(log)
        qDebug() << "deathWindOnAnimals : from " << m_animalsToDelete.count() << "animals to delete";
    for(int i = 0 ; i < m_animalsToDelete.count() ; i++)
    {
        m_animalsToDelete[i]->deletionOfTheAnimal();
    }
    m_animalsToDelete.remove(0, m_animalsToDelete.count());
    if(log)
        qDebug() << "deathWindOnAnimals : to " << m_animalsToDelete.count() << "animals to delete";

}

void Animals::moveToABetterPlace()
{
    Animal *currentAnimal = listOfAllAnimals.getLastAnimalAddedAndMove();

    while(currentAnimal != nullptr)
    {
        if(currentAnimal->Getalive()==true)
        {
            currentAnimal->moveToABetterPlace();
        }
        currentAnimal = listOfAllAnimals.getNextAnimalAddedAndMove();
    }
}

unsigned int Animals::anAnimalIsBorn(Animal *bornAnimal)
{
    m_livingAnimalsNb++;
    m_totalAnimalsNb++;
    listOfAllAnimals.addAnimalToList(bornAnimal);
    return m_totalAnimalsNb;
}



void Animals::anAnimalIsDead(Animal* deadAnimal)
{
    this->listOfAllAnimals.removeAnimalFromList(deadAnimal);
    m_livingAnimalsNb--;
}



// Static functions

int Animals::randomInt(int val1, int variationAcceptee)
{

    int high = val1 * (100 + variationAcceptee) / 100;
    int low = val1 * (100 - variationAcceptee) / 100;
    int v1 =  QRandomGenerator::global()->bounded(65536);

    v1 =  v1 % ((high + 1) - low) + low;

    return v1;
}

double Animals::randomDouble(double val1, double variationAcceptee)
{

    double high = val1 * (100.0 + variationAcceptee) / 100.0;
    double low = val1 * (100.0 - variationAcceptee) / 100.0;

    double v1 =  QRandomGenerator::global()->generateDouble();

    v1 =  low + v1 * (high - low);

    return v1;
}


bool Animals::randomBool(void)
{
    quint64 value  = QRandomGenerator::global()->generate() % 2;
    if(value == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Animals::debugFunction(QString nomFonction)
{

    qDebug() << "********************************"  ;
    qDebug() << nomFonction ;

    Animal *currentAnimal;
    Animal *nextAnimal;
    currentAnimal = listOfAllAnimals.getLastAnimalAddedAndMove();

    while(currentAnimal != nullptr)
    {
        //unsigned int essai2 = currentAnimal->GetanimalId() ;
        unsigned int essai2=1;
        nextAnimal = listOfAllAnimals.getAnimalAddedAPositionFurther(1);
        if(nextAnimal != nullptr)
        {
            qDebug() << nomFonction << " dealing with (" << essai2 <<")(" << currentAnimal  <<") => (" << nextAnimal << ")" ;
        }
        else
        {
            qDebug() << nomFonction << " dealing with (" << essai2 <<")(" << currentAnimal  <<") => (end of list)";
        }

       currentAnimal = listOfAllAnimals.getNextAnimalAddedAndMove();
    }
    qDebug() << "********************************" ;

}

double Animals::getLifeHourglassDependingOnAge (
                                      int  age,
                                      double lifeHourglass_maximumValue,
                                      double lifeHourglass_ageMaximumValue,
                                      double lifeHourglass_birthDivisorFactor,
                                      double lifeHourglass_oldAge,
                                      double lifeHourglass_oldAgeDivisorFactor
        )
{
    if(age > lifeHourglass_ageMaximumValue)
    {
        // if age = lifeHourglass_ageMaximumValue, lifeLevelHourglassValueConsideringAge = lifeHourglass_ageMaximumValue
        // if age = lifeHourglass_oldAge, lifeLevelHourglassValueConsideringAge = m_lifeHourglass / lifeHourglass_oldAgeDivisorFactor

        return (age - lifeHourglass_ageMaximumValue)
               * ( lifeHourglass_maximumValue - (lifeHourglass_maximumValue / lifeHourglass_oldAgeDivisorFactor))
               / (lifeHourglass_ageMaximumValue - lifeHourglass_oldAge)
               +  lifeHourglass_maximumValue ;
    }
    else
    {
        // if age = lifeHourglass_ageMaximumValue, lifeLevelHourglassValueConsideringAge = m_lifeHourglass
        // if age = 0, lifeLevelHourglassValueConsideringAge = m_lifeHourglass / lifeHourglass_birthDivisorFactor

        return (age - lifeHourglass_ageMaximumValue)
               * (lifeHourglass_maximumValue - lifeHourglass_maximumValue / lifeHourglass_birthDivisorFactor)
               / (lifeHourglass_ageMaximumValue)
               + lifeHourglass_maximumValue ;
    }

}

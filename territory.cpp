#include "territory.h"
#include "territoriestodraw.h"
#include <QDebug>



Territory::Territory(unsigned int positionEastWest, unsigned int positionSouthNorth):
    m_listOfTerritoryAnimals(new AnimalsList()),
    m_positionEastWest(positionEastWest),
    m_positionSouthNorth(positionSouthNorth),
    m_grassLevel(0)
{


}
AnimalsList * Territory::getListOfTerritoryAnimals() const
{
    return m_listOfTerritoryAnimals;
}
void Territory::addAnimalToTerritoryList(Animal *animalToAdd)
{
    this->m_listOfTerritoryAnimals->addAnimalToList(animalToAdd);
}

bool Territory::removeAnimalFromTerritoryList(Animal *animalToRemove)
{
    return m_listOfTerritoryAnimals->removeAnimalFromList(animalToRemove);
}


unsigned int Territory::positionEastWest() const
{
    return m_positionEastWest;
}

unsigned int Territory::positionSouthNorth() const
{
    return m_positionSouthNorth;
}

void Territory::animalsConfrontationInsideTerritory()
{

    bool log = false;

    if(log == true)
    {
        qDebug() << this->m_listOfTerritoryAnimals->getTotalAnimalsInList() << " animals meeting (" << this->m_positionEastWest << ", " << this->m_positionSouthNorth << ")" ;
    }

    Animal *currentAnimal1 = this->getListOfTerritoryAnimals()->getLastAnimalAddedAndMove();
    unsigned int positionCurrentAnimal1 = 0;

    while(currentAnimal1 != nullptr)
    {
        if((currentAnimal1->lifeLevel() > 0.0 ) && (currentAnimal1->Getalive())) // On vérifie que l'animal n'est pas un cadavre
        {
            unsigned int positionCurrentAnimal2 = positionCurrentAnimal1 + 1;
            Animal *currentAnimal2 = this->getListOfTerritoryAnimals()->getAnimalAddedAPositionFurther(positionCurrentAnimal2);

            while(currentAnimal2 != nullptr)
            {
                if((currentAnimal2->lifeLevel() > 0.0 )&& (currentAnimal2->Getalive())) // On vérifie que l'animal n'est pas un cadavre
                {
                    currentAnimal1->confrontationWithAnotherAnimal(currentAnimal2);
                }
                positionCurrentAnimal2++;
                currentAnimal2 = this->getListOfTerritoryAnimals()->getAnimalAddedAPositionFurther(positionCurrentAnimal2);
            }
        }

        // Pointer is repositionned to positionCurrentAnimal1
        positionCurrentAnimal1++;
        currentAnimal1 = this->getListOfTerritoryAnimals()->getAnimalAddedAPositionFurther(positionCurrentAnimal1);
    }

}

void Territory::eatingTerritoryGrass()
{
    bool log = false;
    QString myLog;

    if(log == true)
    {
        myLog =  "eatingTerritoryGrass ("
                + QString::number(this->m_positionEastWest)
                + ", "
                + QString::number(this->m_positionSouthNorth)
                + ") " ;
    }

    // Grass is growing
    this->m_grassLevel = this->m_grassLevel + Territory::grownGrassEachYear ;
    if(this->m_grassLevel > Territory::maxGrassOnATerritory)
    {
        this->m_grassLevel = Territory::maxGrassOnATerritory;
    }

    if(log == true)
    {
        myLog = myLog
                + "grass ("
                + QString::number(this->m_grassLevel)
                + "), " ;
    }


    // Some grass is being eaten
    // Eating grass for each rabbit before hunting
    double portionOfGrassPerRabbit = this->getSmellOfGrassEaters(nullptr, true);

    // Eating grass for each rabbit before hunting
    Animal *currentAnimal = this->getListOfTerritoryAnimals()->getLastAnimalAddedAndMove();
    while(currentAnimal != nullptr)
    {
        currentAnimal->IEatSomeGrass(portionOfGrassPerRabbit);
        currentAnimal = this->getListOfTerritoryAnimals()->getNextAnimalAddedAndMove();
    }


}

double Territory::getSmellOfSomeAnimals(unsigned int *nbOf)
{
    // initialization
    double value = 0;

    //Contribution of the 3 close territories
     value =    nbOf[Territory::E_closeTerritoriesEast]
             +  nbOf[Territory::E_closeTerritoriesWest]
             +  nbOf[Territory::E_closeTerritoriesNorth]
             +  nbOf[Territory::E_closeTerritoriesSouth];

    value = nbOf[Territory::E_closeTerritoriesMe] + value * Territories::getValueOfNextTerroriesInAnimalsOdor() ;

    return  value / (1 + Territories::getValueOfNextTerroriesInAnimalsOdor() * 4);
}

double Territory::getSmellOfGrassEaters(Animal *animalSmelling, bool majGrassLevel)
{
    int nbOfGrassEater = 0;
    double portionOfGrassPerRabbit;

    Animal *currentAnimal = this->getListOfTerritoryAnimals()->getLastAnimalAddedAndMove();
    while(currentAnimal != nullptr)
    {
        if(currentAnimal->IEatSomeGrass(0.0) && currentAnimal != animalSmelling)
            nbOfGrassEater++;
        currentAnimal = this->getListOfTerritoryAnimals()->getNextAnimalAddedAndMove();
    }

    if(this->m_grassLevel >= nbOfGrassEater )
    {
        // grass portion per rabbit
        portionOfGrassPerRabbit = 1.0;
        if(majGrassLevel)
        {    this->m_grassLevel = this->m_grassLevel - nbOfGrassEater;}
    }
    else
    {
        portionOfGrassPerRabbit = this->m_grassLevel / nbOfGrassEater;
        if(majGrassLevel)
        {    this->m_grassLevel = 0;}
    }

    return portionOfGrassPerRabbit;
}


double Territory::getSmellOfAnimalReadyToFightWithMe(Animal *smellingAnimal)
{
    unsigned int valueOfEachTerritory[E_closeTerritoriesMax];
    Territory *t = nullptr;
    Animal *currentAnimal;

    for(unsigned int i=0 ; i < E_closeTerritoriesMax ; i++)
    {
        switch (i) {
        case E_closeTerritoriesMe:      t=this;                 break;
        case E_closeTerritoriesEast:    t=this->eastTerritory;  break;
        case E_closeTerritoriesWest:    t=this->westTerritory;  break;
        case E_closeTerritoriesSouth:   t=this->southTerritory;  break;
        case E_closeTerritoriesNorth:   t=this->northTerritory;  break;
        }

        valueOfEachTerritory[i] = 0;
        currentAnimal = t->getListOfTerritoryAnimals()->getLastAnimalAddedAndMove();
        while(currentAnimal != nullptr)
        {
            if(currentAnimal->amIReadyToFightWith(smellingAnimal))
            {
                valueOfEachTerritory[i] ++;
            }
            currentAnimal = t->getListOfTerritoryAnimals()->getNextAnimalAddedAndMove();
        }
    }

    return (this->getSmellOfSomeAnimals(valueOfEachTerritory));
}


double Territory::getSmellOfAnimalsReadyToMateWithMe(Animal *smellingAnimal)
{
    unsigned int valueOfEachTerritory[E_closeTerritoriesMax];
    Territory *t = nullptr;
    Animal *currentAnimal;

    for(unsigned int i=0 ; i < E_closeTerritoriesMax ; i++)
    {
        switch (i) {
        case E_closeTerritoriesMe:      t=this;                 break;
        case E_closeTerritoriesEast:    t=this->eastTerritory;  break;
        case E_closeTerritoriesWest:    t=this->westTerritory;  break;
        case E_closeTerritoriesSouth:   t=this->southTerritory;  break;
        case E_closeTerritoriesNorth:   t=this->northTerritory;  break;
        }

        valueOfEachTerritory[i] = 0;
        currentAnimal = t->getListOfTerritoryAnimals()->getLastAnimalAddedAndMove();
        while(currentAnimal != nullptr)
        {
            if(currentAnimal->amIReadyToMateWith(smellingAnimal))
            {
                valueOfEachTerritory[i] ++;
            }
            currentAnimal = t->getListOfTerritoryAnimals()->getNextAnimalAddedAndMove();
        }
    }

    return (this->getSmellOfSomeAnimals(valueOfEachTerritory));
}

double Territory::getSmellOfAnimalsToHunt()
{
    unsigned int valueOfEachTerritory[E_closeTerritoriesMax];
    Territory *t = nullptr;
    Animal *currentAnimal;

    for(unsigned int i=0 ; i < E_closeTerritoriesMax ; i++)
    {
        switch (i) {
        case E_closeTerritoriesMe:      t=this;                 break;
        case E_closeTerritoriesEast:    t=this->eastTerritory;  break;
        case E_closeTerritoriesWest:    t=this->westTerritory;  break;
        case E_closeTerritoriesSouth:   t=this->southTerritory;  break;
        case E_closeTerritoriesNorth:   t=this->northTerritory;  break;
        }

        valueOfEachTerritory[i] = 0;
        currentAnimal = t->getListOfTerritoryAnimals()->getLastAnimalAddedAndMove();
        while(currentAnimal != nullptr)
        {
            valueOfEachTerritory[i] += currentAnimal->canIBeHunted();
            currentAnimal = t->getListOfTerritoryAnimals()->getNextAnimalAddedAndMove();
        }
    }

    return (this->getSmellOfSomeAnimals(valueOfEachTerritory));
}

double Territory::getSmellOfAnimalsHunters()
{
    unsigned int valueOfEachTerritory[E_closeTerritoriesMax];
    Territory *t = nullptr;
    Animal *currentAnimal;

    for(unsigned int i = 0; i < E_closeTerritoriesMax ; i++)
    {
        switch (i) {
        case E_closeTerritoriesMe:      t=this;                 break;
        case E_closeTerritoriesEast:    t=this->eastTerritory;  break;
        case E_closeTerritoriesWest:    t=this->westTerritory;  break;
        case E_closeTerritoriesSouth:   t=this->southTerritory;  break;
        case E_closeTerritoriesNorth:   t=this->northTerritory;  break;
        }

        valueOfEachTerritory[i] = 0;
        currentAnimal = t->getListOfTerritoryAnimals()->getLastAnimalAddedAndMove();
        while(currentAnimal != nullptr)
        {
            valueOfEachTerritory[i] += currentAnimal->canIHunt();
            currentAnimal = t->getListOfTerritoryAnimals()->getNextAnimalAddedAndMove();
        }
    }

    return (this->getSmellOfSomeAnimals(valueOfEachTerritory));
}

double Territory::getSmellOfGrassOpportunity(Animal *smellingAnimal)
{
    unsigned int valueOfEachTerritory[E_closeTerritoriesMax];
    Territory *t = nullptr;

    for(unsigned int i=0 ; i < E_closeTerritoriesMax ; i++)
    {
        switch (i) {
        case E_closeTerritoriesMe:      t=this;                 break;
        case E_closeTerritoriesEast:    t=this->eastTerritory;  break;
        case E_closeTerritoriesWest:    t=this->westTerritory;  break;
        case E_closeTerritoriesSouth:   t=this->southTerritory;  break;
        case E_closeTerritoriesNorth:   t=this->northTerritory;  break;
        }

        valueOfEachTerritory[i] = static_cast <unsigned int>(t->getSmellOfGrassEaters(smellingAnimal, false));
    }

    return (this->getSmellOfSomeAnimals(valueOfEachTerritory));
}



int Territory::getGrassLevel()
{
    return m_grassLevel;
}

Territory *Territory::getEastTerritory() const
{
    return eastTerritory;
}

Territory *Territory::getWestTerritory() const
{
    return westTerritory;
}

Territory *Territory::getNorthTerritory() const
{
    return northTerritory;
}

Territory *Territory::getSouthTerritory() const
{
    return southTerritory;
}

Renard *Territory::getASpecificFox(bool lady, int number) const
{
    Animal *currentAnimal = this->getListOfTerritoryAnimals()->getLastAnimalAddedAndMove();
    int counter = 0;

    while(currentAnimal != nullptr)
    {
        if(lady == currentAnimal->woman()){

            if(Renard *currentFox = dynamic_cast<Renard*>(currentAnimal))
            {
                if(counter == number) {
                    return currentFox;
                } else {
                    counter++;
                }
            }
        }
        currentAnimal = this->getListOfTerritoryAnimals()->getNextAnimalAddedAndMove();
    }
    return nullptr;
}

Lapin *Territory::getASpecificRabbit(bool lady, int number) const
{
    Animal *currentAnimal = this->getListOfTerritoryAnimals()->getLastAnimalAddedAndMove();
    int counter = 0;

    while(currentAnimal != nullptr)
    {
        if(lady == currentAnimal->woman()){

            if(Lapin *currentRabbit = dynamic_cast<Lapin*>(currentAnimal))
            {
                if(counter == number) {
                    return currentRabbit;
                } else {
                    counter++;
                }
            }
        }
        currentAnimal = this->getListOfTerritoryAnimals()->getNextAnimalAddedAndMove();
    }
    return nullptr;

}




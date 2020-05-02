#include "animal.h"
#include "territories.h"
#include "territory.h"
#include "animals.h"
#include "yearscounter.h"
#include <QDebug>



Animal::Animal(QObject *parent):
    QObject (parent),
    m_generationFatherWay(0),
    m_generationMotherWay(0),
    m_alive(true),
    m_woman(Animals::randomBool()),
    m_birthDate(yearsCounter::getInstance()->getDate())
{
    m_animalId = Animals::getInstance()->anAnimalIsBorn(this);
    Territories::getInstance()->dropAnimalInARandomTerritory(this);

}

Animal::Animal(Animal &mere, Animal &pere, QObject *parent) :
    QObject (parent),
    m_generationFatherWay(pere.m_generationFatherWay + 1),
    m_generationMotherWay(mere.m_generationMotherWay + 1),
    m_alive(true),
    m_woman(Animals::randomBool()),
    m_birthDate(yearsCounter::getInstance()->getDate())
{
    m_animalId = Animals::getInstance()->anAnimalIsBorn(this);
    this->setAnimalTerritory(mere.getAnimalTerritory()) ;


}

Animal::~Animal()
{
    //dtor
}


void Animal::deletionOfTheAnimal()
{
    Animals::getInstance()->anAnimalIsDead(this);
    this->getAnimalTerritory()->removeAnimalFromTerritoryList(this);
    this->deleteLater();
}

void Animal::coutComplete() const
{
    qDebug() << "life Level (" << m_lifeLevel << ")" ;
    qDebug() << "life Hourglass (" << m_lifeHourglass  << ")";
    qDebug() << "woman (" << m_woman <<") m_birthDate (" << m_birthDate << ")";
    qDebug() << "generation, from father (" << m_generationFatherWay << "), from mother (" << m_generationMotherWay << ")";
}


void Animal::birthSetlifeHourglass(Animal &mere, Animal &pere, double variationNaissance)
{
    double fromFather;
    double fromMother;

    fromFather = Animals::randomDouble(mere.m_lifeHourglass, variationNaissance);
    fromMother = Animals::randomDouble(pere.m_lifeHourglass, variationNaissance);
    m_lifeHourglass = (fromFather + fromMother)/2;
    if(m_lifeHourglass > m_lifeHourglass_Max)
    {
       m_lifeHourglass =  m_lifeHourglass_Max;
    }

}

void Animal::birthSetFightingSkills(Animal &mere, Animal &pere, double variationNaissance)
{
    double fromFather;
    double fromMother;

    fromFather = Animals::randomDouble(mere.m_fighting_attackingDamagesToLiveLevel, variationNaissance);
    fromMother = Animals::randomDouble(pere.m_fighting_attackingDamagesToLiveLevel, variationNaissance);
    m_fighting_attackingDamagesToLiveLevel = (fromFather + fromMother)/2;

    fromFather = Animals::randomDouble(mere.m_fighting_defencingPreservingLiveLevel, variationNaissance);
    fromMother = Animals::randomDouble(pere.m_fighting_defencingPreservingLiveLevel, variationNaissance);
    m_fighting_defencingPreservingLiveLevel = (fromFather + fromMother)/2;

}

void Animal::birthSetSeducingSkills(Animal &mere, Animal &pere, double variationNaissance)
{
    double fromFather;
    double fromMother;

    fromFather = Animals::randomDouble(mere.m_mating_Seducing_Skills, variationNaissance);
    fromMother = Animals::randomDouble(pere.m_mating_Seducing_Skills, variationNaissance);
    m_mating_Seducing_Skills = (fromFather + fromMother)/2;

}

int Animal::GetAge(void) const
{
    return yearsCounter::getInstance()->getDate() - m_birthDate;
}

double Animal::getLifeHourglass() const
{
    return m_lifeHourglass;
}

unsigned int Animal::getIcon() const
{
    return m_icon;
}

double Animal::getMating_Seducing_Skills() const
{
    return m_mating_Seducing_Skills;
}

void Animal::setMating_Seducing_Skills(double mating_Seducing_Skills)
{
    m_mating_Seducing_Skills = mating_Seducing_Skills;
}

void Animal::death(void)
{

    m_alive = false;
    m_lifeLevel = -1;
    Animals::getInstance()->addAnimalToDeleteList(this);

}

double Animal::getFighting_attackingDamagesToLiveLevel() const
{
    return m_fighting_attackingDamagesToLiveLevel;
}

double Animal::getFighting_defencingPreservingLiveLevel() const
{
    return m_fighting_defencingPreservingLiveLevel;
}

int Animal::getBirthDate() const
{
    return m_birthDate;
}

double Animal::lifeLevel() const
{
    return m_lifeLevel;
}

void Animal::setLifeLevel(double lifeLevel)
{
    m_lifeLevel = lifeLevel;
}


void Animal::setFighting_defencingPreservingLiveLevel(double fighting_defencingPreservingLiveLeve)
{
    m_fighting_defencingPreservingLiveLevel = fighting_defencingPreservingLiveLeve;
}


void Animal::setFighting_attackingDamagesToLiveLevel(double fighting_attackingDamagesToLiveLevel)
{
    m_fighting_attackingDamagesToLiveLevel = fighting_attackingDamagesToLiveLevel;
}

void Animal::beingAttacked(Animal *otherAnimal)
{
    double lifeLevelAfterAttack =
                    (this->m_fighting_defencingPreservingLiveLevel - otherAnimal->m_fighting_attackingDamagesToLiveLevel)
                    * Animals::randomDouble(1.0, 50);

    if(lifeLevelAfterAttack <0.0)
    {
        this->m_lifeLevel = this->lifeLevel() + lifeLevelAfterAttack;
    }
}

void Animal::attacking(Animal *otherAnimal)
{
    otherAnimal->beingAttacked(this);
}


Territory *Animal::getAnimalTerritory() const
{
    return m_animalTerritory;
}

void Animal::setLifeHourglass(double lifeHourglass)
{
    m_lifeHourglass = lifeHourglass;
}


bool Animal::woman() const
{
    return m_woman;
}

double Animal::getGeneration() const
{
    return (m_generationFatherWay + m_generationMotherWay) / 2 ;
}


void Animal::setAnimalTerritory(Territory *animalTerritory)
{
    m_animalTerritory = animalTerritory;
   m_animalTerritory->addAnimalToTerritoryList(this);

}

double Animal::getLifeHourglassDependingOnAge(double lifeHourglass_ageMaximumValue,
                                      double lifeHourglass_birthDivisorFactor,
                                      double lifeHourglass_oldAge,
                                      double lifeHourglass_oldAgeDivisorFactor) const
{
    return Animals::getLifeHourglassDependingOnAge (
                                          this->GetAge(),
                                          m_lifeHourglass,
                                          lifeHourglass_ageMaximumValue,
                                          lifeHourglass_birthDivisorFactor,
                                          lifeHourglass_oldAge,
                                          lifeHourglass_oldAgeDivisorFactor
            );


}

bool Animal::GetFaceToDeath(double lifeHourglass_dependingOnAge, double deathMaximuLevel)
{

    bool log = false ;
    double deathValue;
    double lifeValue;


    deathValue = ((Animals::randomDouble(50.0, 100.0)) * deathMaximuLevel) / 100.0;
    lifeValue= m_lifeLevel * lifeHourglass_dependingOnAge / 100;

    if(log ==true)
    {
        /*
        qDebug() << " m_lifeHourglass (" << m_lifeHourglass << ") age (" << this->GetAge() << ")" ;
        qDebug() << "m_lifeLevel (" << m_lifeLevel << ") => lifeValue (" << lifeValue << ")"  ;
        qDebug() << "deathMaximuLevel (" << deathMaximuLevel << ") => deathValue (" << deathValue << ")";
        */

        qDebug() << this->coutLight() << "(" << lifeValue << ")" << "(" << deathValue << ")" ;
    }

    if(deathValue >= lifeValue)
    {
        return true;
    }
    else
    {
        return false;
    }
}

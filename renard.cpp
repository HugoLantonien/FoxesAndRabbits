#include "renard.h"
#include "animals.h"
#include "territories.h"
#include "territory.h"
#include "yearscounter.h"
#include "territoriestodraw.h"
#include "chartdatas.h"
#include <QRandomGenerator>
#include <QDebug>

using  namespace std;

unsigned int Renard::m_livingFoxesNb = 0;
unsigned int Renard::m_totalFoxesNb = 0;
unsigned int Renard::m_nbOfBirthThisYear = 0;
unsigned int Renard::m_nbOfUnsuccessfullDateThisYear = 0;
unsigned int Renard::m_nbOfFightThisYear = 0;
unsigned int Renard::m_nbOfDeathDueToFightThisYear = 0;
unsigned int Renard::m_nbOfdeathThisYear = 0;
unsigned int Renard::m_nbOfSuccessufHuntThisYear = 0;
unsigned int Renard::m_nbOfHuntThisYear = 0;


Renard::Renard():Animal ()
{
    bool log = false;
    bool logLight = false;

    this->setLifeLevel(lifeLevelFoxes_valeurInitiale);
    double lifeHourglass = Animals::randomDouble(Renard::lifeHourglassFoxes_initialValue, Renard::lifeHourglassFoxes_birthVariationRange);
    this->setLifeHourglass(lifeHourglass);
    this->setFighting_defencingPreservingLiveLevel(Renard::fightingFoxes_defencingPreservingLiveLevel_initialValue);
    this->setFighting_attackingDamagesToLiveLevel(Renard::fightingFoxes_attackingLiveLevel_initialValue);
    this->setMating_Seducing_Skills(Renard::m_matingFoxes_Seducing_Skills);
    this->setIcon();
    m_livingFoxesNb++;
    m_totalFoxesNb++;
    m_foxId = m_totalFoxesNb;

    if (logLight) {
        qDebug()<< "A new Fox(" << this << ")" ;
    }

    if(log)
    {
        this->coutComplete();
    }

}

Renard::~Renard()
{
    bool log = false;

    if(log)
        qDebug() << "deletion of the fox " << this->foxId();

}


Renard::Renard(Renard &mere, Renard &pere): Animal(mere,pere)

{

    bool log = false;

   this->birthSetlifeHourglass(mere, pere, this->lifeHourglassFoxes_birthVariationRange);
   this->setLifeLevel(lifeLevelFoxes_valeurInitiale);
   this->birthSetFightingSkills(mere, pere, Renard::fightingFoxes_birthVariationRange);
   this->birthSetSeducingSkills(mere, pere, Renard::matingFoxes_birthVariationRange);
   this->setIcon();

   m_livingFoxesNb++;
   m_totalFoxesNb++;
   m_foxId = m_totalFoxesNb;


   double fromFather = Animals::randomDouble(mere.m_lifeHourglassFoxes_ageMaximumValue, Renard::lifeHourglassFoxes_birthVariationRange);
   double fromMother = Animals::randomDouble(pere.m_lifeHourglassFoxes_ageMaximumValue, Renard::lifeHourglassFoxes_birthVariationRange);
   m_lifeHourglassFoxes_ageMaximumValue = (fromFather + fromMother)/2;
   if(m_lifeHourglassFoxes_ageMaximumValue < m_lifeHourglassFoxes_ageMaximumValue_Min)
   {    m_lifeHourglassFoxes_ageMaximumValue =  m_lifeHourglassFoxes_ageMaximumValue_Min;}

   fromFather = Animals::randomDouble(mere.m_lifeHourglassFoxes_birthDivisorFactor, Renard::lifeHourglassFoxes_birthVariationRange);
   fromMother = Animals::randomDouble(pere.m_lifeHourglassFoxes_birthDivisorFactor, Renard::lifeHourglassFoxes_birthVariationRange);
   m_lifeHourglassFoxes_birthDivisorFactor = (fromFather + fromMother)/2;
   if(m_lifeHourglassFoxes_birthDivisorFactor < m_lifeHourglassFoxes_birthDivisorFactor_Min)
   {    m_lifeHourglassFoxes_birthDivisorFactor =  m_lifeHourglassFoxes_birthDivisorFactor_Min;}

   fromFather = Animals::randomDouble(mere.m_lifeHourglassFoxes_oldAge, Renard::lifeHourglassFoxes_birthVariationRange);
   fromMother = Animals::randomDouble(pere.m_lifeHourglassFoxes_oldAge, Renard::lifeHourglassFoxes_birthVariationRange);
   m_lifeHourglassFoxes_oldAge = (fromFather + fromMother)/2;

   fromFather = Animals::randomDouble(mere.m_lifeHourglassFoxes_oldAgeDivisorFactor, Renard::lifeHourglassFoxes_birthVariationRange);
   fromMother = Animals::randomDouble(pere.m_lifeHourglassFoxes_oldAgeDivisorFactor, Renard::lifeHourglassFoxes_birthVariationRange);
   m_lifeHourglassFoxes_oldAgeDivisorFactor = (fromFather + fromMother)/2;
   if(m_lifeHourglassFoxes_oldAgeDivisorFactor < m_lifeHourglassFoxes_oldAgeDivisorFactor_Min)
   {    m_lifeHourglassFoxes_oldAgeDivisorFactor =  m_lifeHourglassFoxes_oldAgeDivisorFactor_Min;}

   fromFather = Animals::randomDouble(mere.m_matingFoxes_factorDeathMaximuValueToMate, Renard::matingFoxes_birthVariationRange);
   fromMother = Animals::randomDouble(pere.m_matingFoxes_factorDeathMaximuValueToMate, Renard::matingFoxes_birthVariationRange);
   m_matingFoxes_factorDeathMaximuValueToMate = (fromFather + fromMother)/2;

   fromFather = Animals::randomDouble(mere.m_changingTerritoryFoxes_flirtValueAgainstRabbitsNumber, Renard::changingTerritoryFoxes_birthVariationRange);
   fromMother = Animals::randomDouble(pere.m_changingTerritoryFoxes_flirtValueAgainstRabbitsNumber, Renard::changingTerritoryFoxes_birthVariationRange);
   m_changingTerritoryFoxes_flirtValueAgainstRabbitsNumber = (fromFather + fromMother)/2;

   fromFather = Animals::randomDouble(mere.m_changingTerritoryFoxes_rabbitsNumberAgainstFlirtValue, Renard::changingTerritoryFoxes_birthVariationRange);
   fromMother = Animals::randomDouble(pere.m_changingTerritoryFoxes_rabbitsNumberAgainstFlirtValue, Renard::changingTerritoryFoxes_birthVariationRange);
   m_changingTerritoryFoxes_rabbitsNumberAgainstFlirtValue = (fromFather + fromMother)/2;

   fromFather = Animals::randomDouble(mere.m_changingTerritoryFoxes_avoidingFightAgainstRabbitsNumber, Renard::changingTerritoryFoxes_birthVariationRange);
   fromMother = Animals::randomDouble(pere.m_changingTerritoryFoxes_avoidingFightAgainstRabbitsNumber, Renard::changingTerritoryFoxes_birthVariationRange);
   m_changingTerritoryFoxes_avoidingFightAgainstRabbitsNumber = (fromFather + fromMother)/2;

   fromFather = Animals::randomDouble(mere.m_eatingFoxes_lifeLevelAddedPerRabbit, Renard::eatingFoxes_birthVariationRange);
   fromMother = Animals::randomDouble(pere.m_eatingFoxes_lifeLevelAddedPerRabbit, Renard::eatingFoxes_birthVariationRange);
   m_eatingFoxes_lifeLevelAddedPerRabbit = (fromFather + fromMother)/2;
   if(m_eatingFoxes_lifeLevelAddedPerRabbit > m_eatingFoxes_lifeLevelAddedPerRabbit_Max )
   {m_eatingFoxes_lifeLevelAddedPerRabbit = m_eatingFoxes_lifeLevelAddedPerRabbit_Max;}

   fromFather = Animals::randomDouble(mere.m_numberOfBabyPerPregnancy, Renard::matingFoxes_birthVariationRange);
   fromMother = Animals::randomDouble(pere.m_numberOfBabyPerPregnancy, Renard::matingFoxes_birthVariationRange);
   m_numberOfBabyPerPregnancy = (fromFather + fromMother)/2;
   if(m_numberOfBabyPerPregnancy > m_numberOfBabyPerPregnancy_Max)
   {m_numberOfBabyPerPregnancy =  m_numberOfBabyPerPregnancy_Max;}
   if(m_numberOfBabyPerPregnancy < m_numberOfBabyPerPregnancy_Min)
   {m_numberOfBabyPerPregnancy =  m_numberOfBabyPerPregnancy_Min;}


   fromFather = Animals::randomDouble(mere.m_eatingFoxes_lifeLevelNeedPerYear, Renard::eatingFoxes_birthVariationRange);
   fromMother = Animals::randomDouble(pere.m_eatingFoxes_lifeLevelNeedPerYear, Renard::eatingFoxes_birthVariationRange);
   m_eatingFoxes_lifeLevelNeedPerYear = (fromFather + fromMother)/2;
   if(m_eatingFoxes_lifeLevelNeedPerYear < m_eatingFoxes_lifeLevelNeedPerYear_Min)
   {    m_eatingFoxes_lifeLevelNeedPerYear = m_eatingFoxes_lifeLevelNeedPerYear_Min;}

   if(log)
   {
       qDebug() << "A new Fox(" << this << ") : " << this->coutLight();
   }

}

void Renard::faceToDeath()
{
    bool log =false;

    double lifeHourglassDependingOnAge =  this->getLifeHourglassDependingOnAgeFox();

    bool dead = this->GetFaceToDeath(lifeHourglassDependingOnAge, this->deathMaximumValueFoxes);
    if(dead)
    {
        this->death();

        m_livingFoxesNb--;
        m_nbOfdeathThisYear++;

        ChartDatas::getInstance()->addAFox(*this);

        if(log)
            qDebug() << "a fox is dead " << this->coutLight();


    }
}

void Renard::coutComplete() const
{
    qDebug() << this->coutLight()
             << "lifeHourglass (ageMaxVal="<< m_lifeHourglassFoxes_ageMaximumValue << ") "
             << "(birthDiv="<< m_lifeHourglassFoxes_birthDivisorFactor << ") "
             << "(oldAge="<< m_lifeHourglassFoxes_oldAge << ") "
             << "(oldDiv="<< m_lifeHourglassFoxes_oldAgeDivisorFactor << ") " ;
    Animal::coutComplete();
}

QString Renard::coutLight() const
{

    QString value = "Fox (" + QString::number(m_foxId) + ", " + QString::number(this->woman()) + ")" ; //, position (" << this->getAnimalTerritory()->positionEastWest() << ", " << this->getAnimalTerritory()->positionSouthNorth() << ")" ;
    return value;
}

unsigned int Renard::canIBeHunted() const
{
    return 0;
}

unsigned int Renard::canIHunt() const
{
    return 1;
}

unsigned int Renard::getTotalFoxesNb()
{
    return m_totalFoxesNb;
}

unsigned int Renard::getLivingFoxesNb()
{
    return m_livingFoxesNb;
}

Animal::E_readyToMate Renard::readyToMate(void) const
{

    // age to flirt reached
    if(this->GetAge() < this->m_matingFoxes_flirtingBeginningAge)
    {
        return Animal::E_readyToMateNoBecauseOfAge;
    }

    // Time between two pregnancies
    if(
        (this->woman() == true) &&
        (yearsCounter::getInstance()->getDate() - m_lastPregnancyDate <= this->m_matingFoxes_timeBetweenPregnancies )
    )

    {
         return Animal::E_readyToMateNoBecauseLastPregnancy;
    }

    // enough life level

    double lifeHourglassDependingOnAge =  this->getLifeHourglassDependingOnAgeFox();


    double lifeLevelAgainstDeath = lifeHourglassDependingOnAge * this->lifeLevel() / 100.0;

    if(lifeLevelAgainstDeath > Renard::deathMaximumValueFoxes * this->m_matingFoxes_factorDeathMaximuValueToMate) {
        return Animal::E_readyToMateYes;
    }
    else {
        return Animal::E_readyToMateNoBecauseOfLiveLevel;
    }



}

bool Renard::amIReadyToMateWith(Animal *theOneProposingAMate)
{

    // Have we the same sex
    // and also are we the same animal
    if(this->woman() == theOneProposingAMate->woman())
        return false;

    // What about you are ready to mate with a fox ?
    if(theOneProposingAMate->readyToMateWithAFox() == false)
        return false;

    // am I ready to mate
    if(this->readyToMate() != Animal::E_readyToMateYes)
        return false;

    // why not
    return true;

}

bool Renard::amIReadyToFightWith(Animal *theOneProposingAFight)
{

    // I fight only against fox
    if(Renard *otherFox = dynamic_cast  <Renard*> (theOneProposingAFight))
    {
        // Have we an opposite sex
        // If yes no fight
        if(this->woman() != theOneProposingAFight->woman())
            return false;

        // am I myself ready to mate so to fight
        if(this->readyToMate() == Animal::E_readyToMateNoBecauseOfAge)
            return false;

        // Are we the same animal
        // if yes no fight
        if(this == otherFox)
            return false;

        // why not
        return true;

    } else {
        return  false;
    }


}

bool Renard::readyToMateWithARabbit()
{
    return false;
}

bool Renard::readyToMateWithAFox()
{
    return true;
}


unsigned int Renard::foxId() const
{
    return m_foxId;
}

void Renard::setIcon()
{
    int i =  QRandomGenerator::global()->bounded(65536);
    m_icon =  (static_cast <unsigned int> (i)) % TerritoriesToDraw::getNbIconToDrawFoxes() ;
}

double Renard::getNumberOfBabyPerPregnancy() const
{
    return m_numberOfBabyPerPregnancy;
}

int Renard::getLifeHourglassFoxes_ageMaximumValue_Initial()
{
    return lifeHourglassFoxes_ageMaximumValue_Initial;
}

double Renard::getEatingFoxes_lifeLevelNeedPerYear() const
{
    return m_eatingFoxes_lifeLevelNeedPerYear;
}

double Renard::getEatingFoxes_lifeLevelAddedPerRabbit() const
{
    return m_eatingFoxes_lifeLevelAddedPerRabbit;
}

double Renard::getMatingFoxes_factorDeathMaximuValueToMate() const
{
    return m_matingFoxes_factorDeathMaximuValueToMate;
}

double Renard::getChangingTerritoryFoxes_rabbitsNumberAgainstAvoidingFight() const
{
    return m_changingTerritoryFoxes_rabbitsNumberAgainstAvoidingFight;
}

double Renard::getChangingTerritoryFoxes_avoidingFightAgainstRabbitsNumber() const
{
    return m_changingTerritoryFoxes_avoidingFightAgainstRabbitsNumber;
}

double Renard::getChangingTerritoryFoxes_rabbitsNumberAgainstFlirtValue() const
{
    return m_changingTerritoryFoxes_rabbitsNumberAgainstFlirtValue;
}

double Renard::getChangingTerritoryFoxes_flirtValueAgainstRabbitsNumber() const
{
    return m_changingTerritoryFoxes_flirtValueAgainstRabbitsNumber;
}

double Renard::getLifeHourglassFoxes_oldAgeDivisorFactor() const
{
    return m_lifeHourglassFoxes_oldAgeDivisorFactor;
}

double Renard::getLifeHourglassFoxes_oldAge() const
{
    return m_lifeHourglassFoxes_oldAge;
}

double Renard::getLifeHourglassFoxes_birthDivisorFactor() const
{
    return m_lifeHourglassFoxes_birthDivisorFactor;
}

double Renard::getLifeHourglassFoxes_ageMaximumValue() const
{
    return m_lifeHourglassFoxes_ageMaximumValue;
}



bool Renard::beHuntedByAnAnimal(Animal *hunterAnimal)
{
    Q_UNUSED(hunterAnimal)
    // I am a hunter, I can't be hunted

    return false;
}

bool Renard::huntAnAnimal(Animal *animalToHunt)
{
    bool log = false;

    if(this->m_eatingFoxes_numberOfMealTakenThisYear < Renard::eatingFoxes_maxNumberOfMealsTakenPerYear)
    {
        this->attacking(animalToHunt);
        if(animalToHunt->lifeLevel() <= 0)
        {
            QString myLog;
            if (log)
            {
                myLog = this->coutLight() + " is eating a rabbit(" + QString::number(this->lifeLevel());

            }

            this->IHaveAMeal(1.0);
            m_nbOfSuccessufHuntThisYear++;

            if (log)
            {
                qDebug() << myLog << ") ==> (" << this->lifeLevel() <<"), otherAnimal ("<< animalToHunt->lifeLevel() << ")";
            }
        }
        m_nbOfHuntThisYear++;
   }

   return true;
}

unsigned int Renard::getNbOfdeathThisYear()
{
    return m_nbOfdeathThisYear;
}

void Renard::yearNumberInitialization()
{
    m_nbOfdeathThisYear = 0;
    m_nbOfDeathDueToFightThisYear = 0;
    m_nbOfFightThisYear = 0;
    m_nbOfBirthThisYear = 0;
    m_nbOfUnsuccessfullDateThisYear = 0;
    m_nbOfHuntThisYear = 0;
    m_nbOfSuccessufHuntThisYear = 0;
}

unsigned int Renard::getNbOfHuntThisYear()
{
    return m_nbOfHuntThisYear;
}

unsigned int Renard::getNbOfSuccessufHuntThisYear()
{
    return m_nbOfSuccessufHuntThisYear;
}


unsigned int Renard::getNbOfUnsuccessfullDateThisYear()
{
    return m_nbOfUnsuccessfullDateThisYear;
}


unsigned int Renard::getNbOfDeathDueToFightThisYear()
{
    return m_nbOfDeathDueToFightThisYear;
}

unsigned int Renard::getNbOfFightThisYear()
{
    return m_nbOfFightThisYear;
}

unsigned int Renard::getNbOfBirthThisYear()
{
    return m_nbOfBirthThisYear;
}



void Renard::confrontationWithAnotherAnimal(Animal *otherAnimal)
{
    bool log = false;

    if(otherAnimal->beHuntedByAnAnimal(this) == false)
    {
        // 2 foxes ready To Mate
        if ( this->readyToMate()==Animal::E_readyToMateYes && otherAnimal->amIReadyToMateWith(this) )
        {
            double dateSuccessValue = Animals::randomDouble(1.0, Renard::matingFoxes_dateSuccessVariation)
                    * (otherAnimal->getMating_Seducing_Skills() + this->m_matingFoxes_Seducing_Skills);

            if(dateSuccessValue >= Renard::matingFoxes_dateSuccessHourglass)
            {
                if(Renard *otherFox = dynamic_cast<Renard*>(otherAnimal) )
                {
                    if (log)
                        qDebug() << this->coutLight() << " and " << otherAnimal->coutLight() << " are having a mate" ;

                    double averageBirthRate = this->m_numberOfBabyPerPregnancy + otherFox->m_numberOfBabyPerPregnancy;
                    int numberOfBaby = std::lround(Animals::randomDouble(averageBirthRate, 50));


                    if(this->woman())
                    {
                        for(int i = 0 ; i < numberOfBaby ; i++)
                        {
                            new Renard(*this, *otherFox);
                            m_nbOfBirthThisYear++;
                        }
                        this->m_lastPregnancyDate = yearsCounter::getInstance()->getDate();
                    }
                    else
                    {
                        for(int i = 0 ; i < numberOfBaby ; i++)
                        {
                            new Renard(*otherFox, *this);
                            m_nbOfBirthThisYear++;
                        }
                        otherFox->m_lastPregnancyDate = yearsCounter::getInstance()->getDate();
                    }

                } else {
                    qDebug() << "Error, A rabbit try to mate with a fox";
                }
                m_nbOfBirthThisYear++;

            } else {
                if (log)
                {
                    qDebug() << this->coutLight() << " and " << otherAnimal->coutLight() << " did not mate (" << dateSuccessValue << ")";
                }
                m_nbOfUnsuccessfullDateThisYear++;

            }
        } else if (this->readyToMate() != Animal::E_readyToMateNoBecauseOfAge && otherAnimal->amIReadyToFightWith(this)) {

            if (log)
                qDebug() << this->coutLight() << " and " << otherAnimal->coutLight()  << " are fighting (" << this->lifeLevel() << ", " << otherAnimal->lifeLevel() << ")" ;

            this->attacking(otherAnimal);
            this->beingAttacked(otherAnimal);

            if(this->lifeLevel() < 0) {m_nbOfDeathDueToFightThisYear++;}
            if(otherAnimal->lifeLevel()  < 0) {m_nbOfDeathDueToFightThisYear++;}
            m_nbOfFightThisYear++;

            if (log)
                qDebug() << " ==> (" << this->lifeLevel() << ", " << otherAnimal->lifeLevel() << ")"  ;

        }
    }
}

void Renard::IHaveAMeal(double portion)
{
    this->m_eatingFoxes_numberOfMealTakenThisYear++ ;

    if(this->lifeLevel() + Renard::m_eatingFoxes_lifeLevelAddedPerRabbit * portion < 100.0){
        this->setLifeLevel(this->lifeLevel() + Renard::m_eatingFoxes_lifeLevelAddedPerRabbit * portion);
    } else {
        this->setLifeLevel(100.0);
    }

}


bool Renard::IEatSomeGrass(double portion)
{
    Q_UNUSED(portion)
    // I don't eat grass
    return false;
}

double Renard::getLifeHourglassDependingOnAgeFox() const
{
    return this->getLifeHourglassDependingOnAge(
                        this->m_lifeHourglassFoxes_ageMaximumValue,
                        this->m_lifeHourglassFoxes_birthDivisorFactor,
                        this->m_lifeHourglassFoxes_oldAge,
                        this->m_lifeHourglassFoxes_oldAgeDivisorFactor
                        );
}


void Renard::annualDecreaseOfLifeLevel()
{
    this->m_eatingFoxes_numberOfMealTakenThisYear = 0;
    this->setLifeLevel(this->lifeLevel() - Renard::m_eatingFoxes_lifeLevelNeedPerYear );

}


void Renard::moveToABetterPlace(void)
{

    // Searching the best territory initialization
    Territory *territoryToCompare[5] =
        {this->getAnimalTerritory(), this->getAnimalTerritory()->getEastTerritory(), this->getAnimalTerritory()->getWestTerritory(), this->getAnimalTerritory()->getSouthTerritory(), this->getAnimalTerritory()->getNorthTerritory()};
    bool log=false;
    bool logLight=false;
    double notationFoxesPresence[5];
    double maxNotationFoxesPresence = 0.0;
    double minNotationFoxesPresence = 0.0;
    double notationRabbitsPresence[5];
    double maxNotationRabbitsPresence = 0.0;
    double finalNotation[5];
    double maxFinalNotation = 0.0;
    int chosenTerritory[5] = {5, 5, 5, 5, 5};
    double foxesPresenceWeight;
    double rabbitsPresenceWeight;
    bool correct;

    // Searching the best territory to flirt if the kids are raised and if the death is far away

    switch(this->readyToMate())
    {
    case Animal::E_readyToMateYes : // Trying to meet a mate
    {
        foxesPresenceWeight = this->m_changingTerritoryFoxes_flirtValueAgainstRabbitsNumber;
        rabbitsPresenceWeight = this->m_changingTerritoryFoxes_rabbitsNumberAgainstFlirtValue;

        for(int t = 0 ; t < 5 ; t++)
        {
            notationFoxesPresence[t] = territoryToCompare[t]->getSmellOfAnimalsReadyToMateWithMe(this);

            if(notationFoxesPresence[t] > maxNotationFoxesPresence )
            {
                maxNotationFoxesPresence = notationFoxesPresence[t];
            }

        }
        break;
    }
    case Animal::E_readyToMateNoBecauseOfAge : // That isn't a criteria to choose
    {
        foxesPresenceWeight = 0.0;
        rabbitsPresenceWeight = 1.0;
        for(int t = 0 ; t < 5 ; t++)
        {
            notationFoxesPresence[t] = 0.0;
        }
        maxNotationFoxesPresence = 0.0;
        break;
    }
    default : // The important think is to avoid fighting
    {
        foxesPresenceWeight = this->m_changingTerritoryFoxes_avoidingFightAgainstRabbitsNumber;
        rabbitsPresenceWeight = this->m_changingTerritoryFoxes_rabbitsNumberAgainstAvoidingFight;

        for(int t = 0 ; t < 5 ; t++)
        {
            notationFoxesPresence[t] = -territoryToCompare[t]->getSmellOfAnimalReadyToFightWithMe(this);

            if(notationFoxesPresence[t] < minNotationFoxesPresence )
            {
                minNotationFoxesPresence = notationFoxesPresence[t];
            }
        }

        for(int t = 0 ; t < 5 ; t++) // back to positive values
        {
            notationFoxesPresence[t] = notationFoxesPresence[t] - minNotationFoxesPresence;
            if(notationFoxesPresence[t] > maxNotationFoxesPresence )
            {
                maxNotationFoxesPresence = notationFoxesPresence[t];
            }

        }

        break;
    }

    }

    // Rabbits notation

    for(int t = 0 ; t < 5 ; t++)
    {
        // Les lapins comptent aussi
        notationRabbitsPresence[t] = territoryToCompare[t]->getSmellOfAnimalsToHunt();
        if(notationRabbitsPresence[t] > maxNotationRabbitsPresence )
        {
            maxNotationRabbitsPresence = notationRabbitsPresence[t];
        }
    }

    // Final notation
    for(int t = 0 ; t < 5 ; t++)
    {
        if(maxNotationFoxesPresence != 0.0)
        {
            finalNotation[t] = notationFoxesPresence[t] / maxNotationFoxesPresence * foxesPresenceWeight;
        }
        else
        {
            finalNotation[t] = 0;
        }

        // On additionne les lapins
        if(maxNotationRabbitsPresence != 0.0)
        {
            finalNotation[t] = finalNotation[t] + notationRabbitsPresence[t] / maxNotationRabbitsPresence * rabbitsPresenceWeight;
        }

        if(finalNotation[t] >maxFinalNotation)
        {
            maxFinalNotation = finalNotation[t];
        }

    }


    // Choix du territoire
    int c=0;
    for(int t = 0 ; t < 5 ; t++)
    {
        if(finalNotation[t]==maxFinalNotation)
        {
            chosenTerritory[c] = t;
            c++;
        }
    }
    int v1 =  QRandomGenerator::global()->bounded(65536);
    v1 =  v1 % c ;


    // Log
    QString myLog("");

    if(log == true)
    {
        double lifeHourglassDependingOnAge =  this->getLifeHourglassDependingOnAgeFox();

        double lifeLevelAgainstDeath = lifeHourglassDependingOnAge * this->lifeLevel() / 100.0;
        if(this->readyToMate()==Animal::E_readyToMateYes)
        {
            myLog  = "Flirt searching (" + QString::number(lifeLevelAgainstDeath) + " > " + QString::number(Renard::deathMaximumValueFoxes * this->m_matingFoxes_factorDeathMaximuValueToMate) + ") ";
        }
        else if(this->readyToMate()==Animal::E_readyToMateNoBecauseOfAge)
        {
            myLog =  "Young Animal searching rabbit (" + QString::number(this->GetAge()) + ") ";
        }
        else {
            myLog =  "Meeting avoiding (" + QString::number(lifeLevelAgainstDeath) + " < " + QString::number(Renard::deathMaximumValueFoxes * this->m_matingFoxes_factorDeathMaximuValueToMate) + ") ";

        }
        myLog = myLog + this->coutLight();

    }
    else if(logLight== true)
    {

        if(this->readyToMate()==Animal::E_readyToMateYes)
        {
           myLog =  "Flirt searching  ";
        }
        else
        {
            myLog =  "Meeting avoiding ";
        }
        myLog = myLog + this->coutLight();

    }

    if(log == true)
    {
        for(int t = 0 ; t < 5 ; t++ )
        {
            myLog = myLog
                    + " ("
                    + QString::number(territoryToCompare[t]->positionEastWest())
                    + ", "
                    + QString::number(territoryToCompare[t]->positionSouthNorth())
                    + ") = "
                    + QString::number(notationFoxesPresence[t])
                    + " ; " ;
        }
    }

    // Chgt de territoire
    if(territoryToCompare[chosenTerritory[v1]] != this->getAnimalTerritory())
    {

        if ((log == true) || (logLight==true))
        {
           myLog = myLog
                   + " ==> from ("
                   + QString::number(this->getAnimalTerritory()->positionEastWest())
                   + ", "
                   + QString::number(this->getAnimalTerritory()->positionSouthNorth())
                   + ")";
        }
        // Moving
        correct = this->getAnimalTerritory()->removeAnimalFromTerritoryList(this);
        this->setAnimalTerritory(territoryToCompare[chosenTerritory[v1]]);

        // Log
        if(correct == false)
        {
            myLog =  myLog + " ouh lalala ça va pas du tout " ;
        }
        else if ((log == true) || (logLight==true))
        {
           myLog = myLog
                   + " to ("
                   + QString::number(this->getAnimalTerritory()->positionEastWest())
                   + ", "
                   + QString::number(this->getAnimalTerritory()->positionSouthNorth())
                   + ")";
        }
    }
    else if ((log == true) || (logLight==true))
    {
        myLog = myLog + " Stay " + this->coutLight();
    }

    if(log || logLight)
        qDebug() << myLog ;
}

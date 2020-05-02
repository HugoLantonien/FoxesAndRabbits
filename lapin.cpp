#include "chartdatas.h"
#include "lapin.h"
#include "animals.h"
#include "territories.h"
#include "territory.h"
#include "yearscounter.h"
#include "territoriestodraw.h"
#include <QRandomGenerator>
#include <QDebug>

using  namespace std;

unsigned int Lapin::m_livingRabbitsNb = 0;
unsigned int Lapin::m_totalRabbitsNb = 0;
unsigned int Lapin::m_nbOfBirthThisYear = 0;
unsigned int Lapin::m_nbOfUnsuccessfullDateThisYear = 0;
unsigned int Lapin::m_nbOfdeathThisYear = 0;

Lapin::Lapin():Animal ()
{
    bool log = false;
    bool logLight = false;
    this->setLifeLevel(Lapin::lifeLevelRabbits_valeurInitiale);
    double lifeHourglass = Animals::randomDouble(Lapin::lifeHourglassRabbits_initialValue, Lapin::lifeHourglassRabbits_birthVariationRange);
    this->setLifeHourglass(lifeHourglass);
    this->setFighting_defencingPreservingLiveLevel(Lapin::fightingRabbits_defencingPreservingLiveLevel_initialValue);
    this->setFighting_attackingDamagesToLiveLevel(Lapin::fightingRabbits_attackingLiveLevel_initialValue);
    this->setMating_Seducing_Skills(Lapin::m_matingRabbits_Seducing_Skills);
    this->setIcon();

    m_livingRabbitsNb++;
    m_totalRabbitsNb++;
    m_rabbitId = m_totalRabbitsNb;

    if(logLight){
        qDebug()<< "A new Rabbit(" << this << ")" ;
    }

    if(log)
    {
        this->coutComplete();
    }

}

Lapin::~Lapin()
{
    bool log = false;

    if(log)
        qDebug() << "deletion of the rabbit " << this->getRabbitId();
}


Lapin::Lapin(Lapin &mere, Lapin &pere): Animal(mere,pere)

{

    bool log = false;

   this->birthSetlifeHourglass(mere, pere, this->lifeHourglassRabbits_birthVariationRange);
   this->setLifeLevel(Lapin::lifeLevelRabbits_valeurInitiale);
   this->birthSetFightingSkills(mere, pere, Lapin::fightingRabbits_birthVariationRange);
   this->birthSetSeducingSkills(mere, pere, Lapin::matingRabbits_birthVariationRange);
   this->setIcon();

   m_livingRabbitsNb++;
   m_totalRabbitsNb++;
   m_rabbitId = m_totalRabbitsNb;


   double fromFather = Animals::randomDouble(mere.m_lifeHourglassRabbits_ageMaximumValue, Lapin::lifeHourglassRabbits_birthVariationRange);
   double fromMother = Animals::randomDouble(pere.m_lifeHourglassRabbits_ageMaximumValue, Lapin::lifeHourglassRabbits_birthVariationRange);
   m_lifeHourglassRabbits_ageMaximumValue = (fromFather + fromMother)/2;
   if(m_lifeHourglassRabbits_ageMaximumValue < m_lifeHourglassRabbits_ageMaximumValue_Min)
   {m_lifeHourglassRabbits_ageMaximumValue =  m_lifeHourglassRabbits_ageMaximumValue_Min;}

   fromFather = Animals::randomDouble(mere.m_lifeHourglassRabbits_birthDivisorFactor, Lapin::lifeHourglassRabbits_birthVariationRange);
   fromMother = Animals::randomDouble(pere.m_lifeHourglassRabbits_birthDivisorFactor, Lapin::lifeHourglassRabbits_birthVariationRange);
   m_lifeHourglassRabbits_birthDivisorFactor = (fromFather + fromMother)/2;
   if(m_lifeHourglassRabbits_birthDivisorFactor < m_lifeHourglassRabbits_birthDivisorFactor_Min)
   {m_lifeHourglassRabbits_birthDivisorFactor =  m_lifeHourglassRabbits_birthDivisorFactor_Min;}

   fromFather = Animals::randomDouble(mere.m_lifeHourglassRabbits_oldAge, Lapin::lifeHourglassRabbits_birthVariationRange);
   fromMother = Animals::randomDouble(pere.m_lifeHourglassRabbits_oldAge, Lapin::lifeHourglassRabbits_birthVariationRange);
   m_lifeHourglassRabbits_oldAge = (fromFather + fromMother)/2;

   fromFather = Animals::randomDouble(mere.m_lifeHourglassRabbits_oldAgeDivisorFactor, Lapin::lifeHourglassRabbits_birthVariationRange);
   fromMother = Animals::randomDouble(pere.m_lifeHourglassRabbits_oldAgeDivisorFactor, Lapin::lifeHourglassRabbits_birthVariationRange);
   m_lifeHourglassRabbits_oldAgeDivisorFactor = (fromFather + fromMother)/2;
   if(m_lifeHourglassRabbits_oldAgeDivisorFactor < m_lifeHourglassRabbits_oldAgeDivisorFactor_Min)
   {m_lifeHourglassRabbits_oldAgeDivisorFactor =  m_lifeHourglassRabbits_oldAgeDivisorFactor_Min;}

   fromFather = Animals::randomDouble(mere.m_matingRabbits_factorDeathMaximuValueToMate, Lapin::matingRabbits_birthVariationRange);
   fromMother = Animals::randomDouble(pere.m_matingRabbits_factorDeathMaximuValueToMate, Lapin::matingRabbits_birthVariationRange);
   m_matingRabbits_factorDeathMaximuValueToMate = (fromFather + fromMother)/2;

   fromFather = Animals::randomDouble(mere.m_numberOfBabyPerPregnancy, Lapin::matingRabbits_birthVariationRange);
   fromMother = Animals::randomDouble(pere.m_numberOfBabyPerPregnancy, Lapin::matingRabbits_birthVariationRange);
   m_numberOfBabyPerPregnancy = (fromFather + fromMother)/2;
   if(m_numberOfBabyPerPregnancy > m_numberOfBabyPerPregnancy_Max)
   {m_numberOfBabyPerPregnancy =  m_numberOfBabyPerPregnancy_Max;}
   if(m_numberOfBabyPerPregnancy < m_numberOfBabyPerPregnancy_Min)
   {m_numberOfBabyPerPregnancy =  m_numberOfBabyPerPregnancy_Min;}


   fromFather = Animals::randomDouble(mere.m_changingTerritoryRabbits_flirtValue, Lapin::changingTerritoryRabbits_birthVariationRange);
   fromMother = Animals::randomDouble(pere.m_changingTerritoryRabbits_flirtValue, Lapin::changingTerritoryRabbits_birthVariationRange);
   m_changingTerritoryRabbits_flirtValue = (fromFather + fromMother)/2;

   fromFather = Animals::randomDouble(mere.m_changingTerritoryRabbits_huntersValue, Lapin::changingTerritoryRabbits_birthVariationRange);
   fromMother = Animals::randomDouble(pere.m_changingTerritoryRabbits_huntersValue, Lapin::changingTerritoryRabbits_birthVariationRange);
   m_changingTerritoryRabbits_huntersValue = (fromFather + fromMother)/2;

   fromFather = Animals::randomDouble(mere.m_changingTerritoryRabbits_grassLevel, Lapin::changingTerritoryRabbits_birthVariationRange);
   fromMother = Animals::randomDouble(pere.m_changingTerritoryRabbits_grassLevel, Lapin::changingTerritoryRabbits_birthVariationRange);
   m_changingTerritoryRabbits_grassLevel = (fromFather + fromMother)/2;

   fromFather = Animals::randomDouble(mere.m_eatingRabbits_lifeLevelAddedPerMeal, Lapin::eatingRabbits_birthVariationRange);
   fromMother = Animals::randomDouble(pere.m_eatingRabbits_lifeLevelAddedPerMeal, Lapin::eatingRabbits_birthVariationRange);
   m_eatingRabbits_lifeLevelAddedPerMeal = (fromFather + fromMother)/2;
   if(m_eatingRabbits_lifeLevelAddedPerMeal > m_eatingRabbits_lifeLevelAddedPerMeal_Max)
   {m_eatingRabbits_lifeLevelAddedPerMeal =  m_eatingRabbits_lifeLevelAddedPerMeal_Max;}


   fromFather = Animals::randomDouble(mere.m_eatingRabbits_lifeLevelNeedPerYear, Lapin::eatingRabbits_birthVariationRange);
   fromMother = Animals::randomDouble(pere.m_eatingRabbits_lifeLevelNeedPerYear, Lapin::eatingRabbits_birthVariationRange);
   m_eatingRabbits_lifeLevelNeedPerYear = (fromFather + fromMother)/2;
   if(m_eatingRabbits_lifeLevelNeedPerYear < m_eatingRabbits_lifeLevelNeedPerYear_Min)
   {m_eatingRabbits_lifeLevelNeedPerYear =  m_eatingRabbits_lifeLevelNeedPerYear_Min;}


   if(log)
   {
       qDebug() << "A new Rabbit(" << this << ") : " << this->coutLight();
   }

}

void Lapin::faceToDeath()
{
    bool log =false;

    double lifeHourglassDependingOnAge = this->getLifeHourglassDependingOnAgeRabbit();

    bool dead = this->GetFaceToDeath(lifeHourglassDependingOnAge, this->deathMaximumValueRabbits);
    if(dead)
    {
        this->death();

        m_livingRabbitsNb--;
        m_nbOfdeathThisYear++;

        ChartDatas::getInstance()->addARabbit(*this);

        if(log)
            qDebug() << "a rabbit is dead " << this->coutLight();
    }
}

void Lapin::coutComplete() const
{
    qDebug() << this->coutLight()
             << "lifeHourglass (ageMaxVal="<< m_lifeHourglassRabbits_ageMaximumValue << ") "
             << "(birthDiv="<< m_lifeHourglassRabbits_birthDivisorFactor << ") "
             << "(oldAge="<< m_lifeHourglassRabbits_oldAge << ") "
             << "(oldDiv="<< m_lifeHourglassRabbits_oldAgeDivisorFactor << ") " ;
    Animal::coutComplete();
}

QString Lapin::coutLight() const
{

    QString value = "Rabbit (" + QString::number(m_rabbitId) + ", " + QString::number(this->woman()) + ")" ; //, position (" << this->getAnimalTerritory()->positionEastWest() << ", " << this->getAnimalTerritory()->positionSouthNorth() << ")" ;
    return value;
}

unsigned int Lapin::canIBeHunted() const
{
    return 1;
}

unsigned int Lapin::canIHunt() const
{
    return 0;
}

unsigned int Lapin::getTotalRabbitsNb()
{
    return m_totalRabbitsNb;
}


unsigned int Lapin::getLivingRabbitsNb()
{
    return m_livingRabbitsNb;
}

Animal::E_readyToMate Lapin::readyToMate(void) const
{

    // age to flirt reached
    if(this->GetAge() < this->m_matingRabbits_flirtingBeginningAge)
    {
        return Animal::E_readyToMateNoBecauseOfAge;
    }

    // Time between two pregnancies
    if(
            (this->woman() == true) &&
            (yearsCounter::getInstance()->getDate() - m_lastPregnancyDate <= this->m_matingRabbits_timeBetweenPregnancies )
     )

    {
        return Animal::E_readyToMateNoBecauseLastPregnancy;
    }

    // enough life level

    double lifeHourglassDependingOnAge = this->getLifeHourglassDependingOnAgeRabbit();

    double lifeLevelAgainstDeath = lifeHourglassDependingOnAge * this->lifeLevel() / 100.0;

    if(lifeLevelAgainstDeath > Lapin::deathMaximumValueRabbits * this->m_matingRabbits_factorDeathMaximuValueToMate) {
        return Animal::E_readyToMateYes;
    } else {
        return Animal::E_readyToMateNoBecauseOfLiveLevel;
    }


}




bool Lapin::huntAnAnimal(Animal *animalToHunt)
{
    Q_UNUSED(animalToHunt)
    // Noting to do I am not a hunter
    return false;
}

bool Lapin::beHuntedByAnAnimal(Animal *hunterAnimal)
{
    return hunterAnimal->huntAnAnimal(this);
}


bool Lapin::amIReadyToMateWith(Animal *theOneProposingAMate)
{

    // Have we the same sex
    // and also are we the same animal
    if(this->woman() == theOneProposingAMate->woman())
        return false;

    // What about you are ready to mate with a rabbit
    if(theOneProposingAMate->readyToMateWithARabbit() == false)
        return false;

    // am I ready to mate
    if(this->readyToMate() != Animal::E_readyToMateYes)
        return false;

    // why not
    return true;

}

bool Lapin::amIReadyToFightWith(Animal *theOneProposingAFight)
{
    Q_UNUSED(theOneProposingAFight)
    return false; // A rabbit never fights.
}

bool Lapin::readyToMateWithARabbit()
{
    return true;
}

bool Lapin::readyToMateWithAFox()
{
    return false;
}

unsigned int Lapin::getRabbitId() const
{
    return m_rabbitId;
}


void Lapin::setIcon()
{
    int i =  QRandomGenerator::global()->bounded(65536);
    m_icon =  i % TerritoriesToDraw::getNbIconToDrawRabbits() ;
}

int Lapin::getLifeHourglassRabbits_ageMaximumValue_Initial()
{
    return lifeHourglassRabbits_ageMaximumValue_Initial;
}

double Lapin::getEatingRabbits_lifeLevelNeedPerYear() const
{
    return m_eatingRabbits_lifeLevelNeedPerYear;
}

double Lapin::getEatingRabbits_lifeLevelAddedPerMeal() const
{
    return m_eatingRabbits_lifeLevelAddedPerMeal;
}

double Lapin::getNumberOfBabyPerPregnancy() const
{
    return m_numberOfBabyPerPregnancy;
}

double Lapin::getMatingRabbits_factorDeathMaximuValueToMate() const
{
    return m_matingRabbits_factorDeathMaximuValueToMate;
}

double Lapin::getChangingTerritoryRabbits_grassLevel() const
{
    return m_changingTerritoryRabbits_grassLevel;
}

double Lapin::getChangingTerritoryRabbits_huntersValue() const
{
    return m_changingTerritoryRabbits_huntersValue;
}

double Lapin::getChangingTerritoryRabbits_flirtValue() const
{
    return m_changingTerritoryRabbits_flirtValue;
}

double Lapin::getLifeHourglassRabbits_oldAgeDivisorFactor() const
{
    return m_lifeHourglassRabbits_oldAgeDivisorFactor;
}

double Lapin::getLifeHourglassRabbits_oldAge() const
{
    return m_lifeHourglassRabbits_oldAge;
}

double Lapin::getLifeHourglassRabbits_birthDivisorFactor() const
{
    return m_lifeHourglassRabbits_birthDivisorFactor;
}

double Lapin::getLifeHourglassRabbits_ageMaximumValue() const
{
    return m_lifeHourglassRabbits_ageMaximumValue;
}

unsigned int Lapin::getNbOfdeathThisYear()
{
    return m_nbOfdeathThisYear;
}

void Lapin::yearNumberInitialization()
{
    m_nbOfdeathThisYear = 0;
    m_nbOfBirthThisYear = 0;
    m_nbOfUnsuccessfullDateThisYear=0;
}

unsigned int Lapin::getNbOfUnsuccessfullDateThisYear()
{
    return m_nbOfUnsuccessfullDateThisYear;
}


unsigned int Lapin::getNbOfBirthThisYear()
{
    return m_nbOfBirthThisYear;
}


void Lapin::confrontationWithAnotherAnimal(Animal *otherAnimal)
{
    bool log = false;

    if (otherAnimal->huntAnAnimal(this) == false)
    {
        // 2 Rabbits
        if ( this->readyToMate() == Animal::E_readyToMateYes && otherAnimal->amIReadyToMateWith(this) )
        {
            // A mate
            double dateSuccessValue = Animals::randomDouble(1.0, Lapin::matingRabbits_dateSuccessVariation)
                    * (otherAnimal->getMating_Seducing_Skills() + this->getMating_Seducing_Skills());

            if(dateSuccessValue >= Lapin::matingRabbits_dateSuccessHourglass)
            {
                if(Lapin *otherRabbit = dynamic_cast<Lapin*>(otherAnimal) )
                {

                    if (log)
                    {
                        qDebug() << this->coutLight() << " and " << otherAnimal->coutLight() << " are having a mate" ;
                    }

                    double averageBirthRate = this->m_numberOfBabyPerPregnancy + otherRabbit->m_numberOfBabyPerPregnancy;
                    int numberOfBaby = std::lround(Animals::randomDouble(averageBirthRate, 50));


                    if(this->woman())
                    {
                        for(int i = 0 ; i < numberOfBaby ; i++)
                        {
                            new Lapin(*this, *otherRabbit);
                            m_nbOfBirthThisYear++;
                            this->m_lastPregnancyDate = yearsCounter::getInstance()->getDate();
                        }
                    }
                    else
                    {
                        for(int i = 0 ; i < numberOfBaby ; i++)
                        {
                            new Lapin(*otherRabbit, *this);
                            m_nbOfBirthThisYear++;
                            otherRabbit->m_lastPregnancyDate = yearsCounter::getInstance()->getDate();
                        }
                    }
                }
                else {
                    qDebug() << "Error, A rabbit try to mate with a fox";
                }
            }
            else
            {
                m_nbOfUnsuccessfullDateThisYear++;
                if (log)
                    qDebug() << this->coutLight() << " and " << otherAnimal->coutLight() << " did not mate (" << dateSuccessValue << ")";
            }
        }
    }
    else
    {
        // Nothing happen when two same sex rabbits meet each other
    }
}

bool Lapin::IEatSomeGrass(double portion)
{
    if(this->lifeLevel() + Lapin::m_eatingRabbits_lifeLevelAddedPerMeal * portion > 100) {
        this->setLifeLevel(100);
    }
    else {
        this->setLifeLevel(this->lifeLevel() + Lapin::m_eatingRabbits_lifeLevelAddedPerMeal * portion);
    }



    return true;
}

double Lapin::getLifeHourglassDependingOnAgeRabbit() const
{
    return this->getLifeHourglassDependingOnAge(
                        this->m_lifeHourglassRabbits_ageMaximumValue,
                        this->m_lifeHourglassRabbits_birthDivisorFactor,
                        this->m_lifeHourglassRabbits_oldAge,
                        this->m_lifeHourglassRabbits_oldAgeDivisorFactor
                        );

}


void Lapin::annualDecreaseOfLifeLevel()
{
    this->setLifeLevel(this->lifeLevel() - Lapin::m_eatingRabbits_lifeLevelNeedPerYear );

}


void Lapin::moveToABetterPlace(void)
{

    // Searching the best territory initialization
    Territory *territoryToCompare[5] =
        {this->getAnimalTerritory(), this->getAnimalTerritory()->getEastTerritory(), this->getAnimalTerritory()->getWestTerritory(), this->getAnimalTerritory()->getSouthTerritory(), this->getAnimalTerritory()->getNorthTerritory()};
    bool log=false;
    bool logLight=false;


    // Searching the best territory to flirt if the kids are raised and if the death is far away
    double notationFlirtsPresence[5];
    double maxNotationFlirtsPresence = 0.0;
    if(this->readyToMate()==Animal::E_readyToMateYes)
    {
        for(int t = 0 ; t < 5 ; t++)
        {
            notationFlirtsPresence[t] = territoryToCompare[t]->getSmellOfAnimalsReadyToMateWithMe(this);

            if(notationFlirtsPresence[t] > maxNotationFlirtsPresence )
            {
                maxNotationFlirtsPresence = notationFlirtsPresence[t];
            }
        }
    } else {
        for(int t = 0 ; t < 5 ; t++)
        {
            notationFlirtsPresence[t] = 0.0;
        }
    }


    // Searching to be far away from hunting foxe
    double notationHuntersPresence[5];
    double minNotationHuntersPresence = 0.0;
    double maxNotationHuntersPresence = 0.0;

    for(int t = 0 ; t < 5 ; t++)
    {
        notationHuntersPresence[t] = -territoryToCompare[t]->getSmellOfAnimalsHunters();
        if(notationHuntersPresence[t] < minNotationHuntersPresence )
        {
            minNotationHuntersPresence = notationHuntersPresence[t];
        }
    }

    for(int t = 0 ; t < 5 ; t++)   // back to positive values
    {
        notationHuntersPresence[t] = notationHuntersPresence[t] - minNotationHuntersPresence;
        if(notationHuntersPresence[t] > maxNotationHuntersPresence )
        {
            maxNotationHuntersPresence = notationHuntersPresence[t];
        }

    }

    // Grass Level notation notation
    double notationGrassLevel[5];
    double maxNotationGrassLevel = 0.0;
    for(int t = 0 ; t < 5 ; t++)
    {
        // Les lapins comptent aussi
        notationGrassLevel[t] = territoryToCompare[t]->getSmellOfGrassOpportunity(this);
        if(notationGrassLevel[t] > maxNotationGrassLevel )
        {
            maxNotationGrassLevel = notationGrassLevel[t];
        }
    }


    // Final notation
    double finalNotation[5];
    double maxFinalNotation = 0.0;
    for(int t = 0 ; t < 5 ; t++)
    {
        if(maxNotationFlirtsPresence != 0.0)
        {
            finalNotation[t] = notationFlirtsPresence[t] / maxNotationFlirtsPresence * Lapin::m_changingTerritoryRabbits_flirtValue;
        }
        else
        {
            finalNotation[t] = 0;
        }

        if(maxNotationHuntersPresence != 0.0)
        {
            finalNotation[t] =  finalNotation[t]
                                + notationHuntersPresence[t] / maxNotationHuntersPresence * Lapin::m_changingTerritoryRabbits_huntersValue;
        }

        if(maxNotationGrassLevel != 0.0)
        {
            finalNotation[t] =  finalNotation[t]
                                + notationGrassLevel[t] / maxNotationGrassLevel * Lapin::m_changingTerritoryRabbits_grassLevel;
        }

        if(finalNotation[t] >maxFinalNotation)
        {
            maxFinalNotation = finalNotation[t];
        }

    }


    // Choix du territoire
    int c=0;
    int chosenTerritory[5] = {5, 5, 5, 5, 5};
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
    QString myLog(this->coutLight());

    if(log == true)
    {
        for(int t = 0 ; t < 5 ; t++ )
        {
            myLog = myLog
                    + " ("
                    + QString::number(territoryToCompare[t]->positionEastWest())
                    + ", "
                    + QString::number(territoryToCompare[t]->positionSouthNorth())
                    + ") = flirt["
                    + QString::number(notationFlirtsPresence[t])
                    + "] + hunter["
                    + QString::number(notationHuntersPresence[t])
                    + "] + grasse["
                    + QString::number(notationGrassLevel[t])
                    ;
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
        bool correct = this->getAnimalTerritory()->removeAnimalFromTerritoryList(this);
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

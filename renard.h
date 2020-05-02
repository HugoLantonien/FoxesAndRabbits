#ifndef RENARD_H
#define RENARD_H

#include <QString>
#include <QObject>
#include <QVector>
#include "animal.h"


class Renard : public Animal
{
    Q_OBJECT
    Q_PROPERTY(unsigned int foxid READ foxId CONSTANT)
    Q_PROPERTY(int lifeLevel READ lifeLevel CONSTANT)
    Q_PROPERTY(double lifehourglassdependingonage READ getLifeHourglassDependingOnAgeFox CONSTANT)
    Q_PROPERTY(double lifehourglass READ getLifeHourglass CONSTANT)
    Q_PROPERTY(double age READ GetAge CONSTANT)
    Q_PROPERTY(double woman READ woman CONSTANT)
    Q_PROPERTY(E_readyToMate readyToMate READ readyToMate CONSTANT)



public:
    Renard();
    Renard(Renard &mere, Renard &pere);
    virtual ~Renard();
    void coutComplete(void) const;
    QString coutLight(void) const;
    void faceToDeath(void) ;
    unsigned int canIBeHunted(void) const;
    unsigned int canIHunt(void) const;
    void moveToABetterPlace(void);
    E_readyToMate readyToMate(void) const;
    void confrontationWithAnotherAnimal(Animal *otherAnimal);
    void annualDecreaseOfLifeLevel();
    void IHaveAMeal(double portion);
    bool IEatSomeGrass(double portion);

    double getLifeHourglassDependingOnAgeFox() const;


    static unsigned int getLivingFoxesNb();
    static unsigned int getTotalFoxesNb();

    static unsigned int getNbOfBirthThisYear();
    static unsigned int getNbOfFightThisYear();
    static unsigned int getNbOfDeathDueToFightThisYear();
    static unsigned int getNbOfdeathThisYear();
    static unsigned int getNbOfUnsuccessfullDateThisYear();
    static unsigned int getNbOfSuccessufHuntThisYear();
    static unsigned int getNbOfHuntThisYear();
    static void yearNumberInitialization();




    unsigned int foxId() const;


    double getLifeHourglassFoxes_ageMaximumValue() const;
    double getLifeHourglassFoxes_birthDivisorFactor() const;
    double getLifeHourglassFoxes_oldAge() const;
    double getLifeHourglassFoxes_oldAgeDivisorFactor() const;

    double getChangingTerritoryFoxes_flirtValueAgainstRabbitsNumber() const;
    double getChangingTerritoryFoxes_rabbitsNumberAgainstFlirtValue() const;
    double getChangingTerritoryFoxes_avoidingFightAgainstRabbitsNumber() const;
    double getChangingTerritoryFoxes_rabbitsNumberAgainstAvoidingFight() const;

    double getMatingFoxes_factorDeathMaximuValueToMate() const;
    double getEatingFoxes_lifeLevelAddedPerRabbit() const;
    double getEatingFoxes_lifeLevelNeedPerYear() const;

    static int const eatingFoxes_maxNumberOfMealsTakenPerYear = 5;      // nb max de lapins mangés par mois


    static int getLifeHourglassFoxes_ageMaximumValue_Initial();

protected:
    bool huntAnAnimal(Animal *animalToHunt) ;
    bool beHuntedByAnAnimal(Animal *hunterAnimal) ;

    bool amIReadyToMateWith(Animal *theOneProposingAMate);
    bool amIReadyToFightWith(Animal *theOneProposingAMate);
    bool readyToMateWithARabbit();
    bool readyToMateWithAFox();


private:
    unsigned int m_foxId;

    void setIcon();

    static unsigned int m_livingFoxesNb;
    static unsigned int m_totalFoxesNb;

    static unsigned int m_nbOfBirthThisYear;
    static unsigned int m_nbOfUnsuccessfullDateThisYear;
    static unsigned int m_nbOfFightThisYear;
    static unsigned int m_nbOfDeathDueToFightThisYear;
    static unsigned int m_nbOfdeathThisYear;
    static unsigned int m_nbOfSuccessufHuntThisYear;
    static unsigned int m_nbOfHuntThisYear;

    // Animal created at the begining
    static int const lifeLevelFoxes_valeurInitiale = 100 ;

    // Facing death parameter
    static int const lifeHourglassFoxes_initialValue = 120;
    static int const lifeHourglassFoxes_birthVariationRange = 5;


    double m_lifeHourglassFoxes_ageMaximumValue = lifeHourglassFoxes_ageMaximumValue_Initial;
    static int const lifeHourglassFoxes_ageMaximumValue_Initial = 15;
    static double constexpr m_lifeHourglassFoxes_ageMaximumValue_Min = 1.0;
    double m_lifeHourglassFoxes_birthDivisorFactor = 1.5;
    static double constexpr m_lifeHourglassFoxes_birthDivisorFactor_Min = 1.0;
    double m_lifeHourglassFoxes_oldAge = 40.0;
    double m_lifeHourglassFoxes_oldAgeDivisorFactor = 2.0;
    static double constexpr m_lifeHourglassFoxes_oldAgeDivisorFactor_Min = 1.0;

    static double constexpr deathMaximumValueFoxes = 50.0;

    // Changing territory flirting, staying safe alone or hunting
    static int const changingTerritoryFoxes_birthVariationRange = 5;
    double m_changingTerritoryFoxes_flirtValueAgainstRabbitsNumber = 0.7;
    double m_changingTerritoryFoxes_rabbitsNumberAgainstFlirtValue = 0.3;
    double m_changingTerritoryFoxes_avoidingFightAgainstRabbitsNumber = 0.5;
    double m_changingTerritoryFoxes_rabbitsNumberAgainstAvoidingFight = 0.5;

    // Mating
    static int const matingFoxes_birthVariationRange = 5;
    double m_matingFoxes_factorDeathMaximuValueToMate = 1.2;
    int m_matingFoxes_timeBetweenPregnancies = 1;
    int m_matingFoxes_flirtingBeginningAge = 4;
    static double constexpr m_matingFoxes_Seducing_Skills = 60.0;
    static double constexpr matingFoxes_dateSuccessHourglass = 100.0;
    static double constexpr matingFoxes_dateSuccessVariation = 20.0;

    // Eating
    static int const eatingFoxes_birthVariationRange = 5;
    double m_eatingFoxes_lifeLevelAddedPerRabbit = 40.0;                // ajout de vie par repas
    static double constexpr m_eatingFoxes_lifeLevelAddedPerRabbit_Max = 70.0;                // ajout de vie par repas
    double m_eatingFoxes_lifeLevelNeedPerYear = 15.0;                   // perte de vie par an du à la faim
    static double constexpr m_eatingFoxes_lifeLevelNeedPerYear_Min = 10.0;                // ajout de vie par repas
    int m_eatingFoxes_numberOfMealTakenThisYear = 0;

    // Hunting Fighting ;
    static int const fightingFoxes_birthVariationRange = 5;
    static double constexpr  fightingFoxes_attackingLiveLevel_initialValue = 120.0;
    static double constexpr fightingFoxes_defencingPreservingLiveLevel_initialValue = 60.0; //in Animal Class



};



#endif // RENARD_H

#ifndef LAPIN_H
#define LAPIN_H

#include <QString>
#include <QObject>
#include <QVector>
#include "animal.h"


class Lapin : public Animal
{
    Q_OBJECT
    Q_PROPERTY(unsigned int rabbitId READ getRabbitId CONSTANT)
    Q_PROPERTY(int lifeLevel READ lifeLevel CONSTANT)
    Q_PROPERTY(double lifehourglassdependingonage READ getLifeHourglassDependingOnAgeRabbit CONSTANT)
    Q_PROPERTY(double lifehourglass READ getLifeHourglass CONSTANT)
    Q_PROPERTY(double age READ GetAge CONSTANT)
    Q_PROPERTY(double woman READ woman CONSTANT)
    Q_PROPERTY(E_readyToMate readyToMate READ readyToMate CONSTANT)


public:
    Lapin();
    Lapin(Lapin &mere, Lapin &pere);
    virtual ~Lapin();

    void coutComplete(void) const;
    QString coutLight(void) const;
    void faceToDeath(void) ;
    unsigned int canIBeHunted(void) const;
    unsigned int canIHunt(void) const;
    void moveToABetterPlace(void);
    E_readyToMate readyToMate(void) const;
    void confrontationWithAnotherAnimal(Animal *otherAnimal);
    void annualDecreaseOfLifeLevel();
    bool IEatSomeGrass(double portion);

    double getLifeHourglassDependingOnAgeRabbit() const;


    static unsigned int getLivingRabbitsNb();
    static unsigned int getTotalRabbitsNb();


    static unsigned int getNbOfBirthThisYear();
    static unsigned int getNbOfdeathThisYear();
    static unsigned int getNbOfUnsuccessfullDateThisYear();
    static void yearNumberInitialization();

    unsigned int getRabbitId() const;

    double getLifeHourglassRabbits_ageMaximumValue() const;
    double getLifeHourglassRabbits_birthDivisorFactor() const;
    double getLifeHourglassRabbits_oldAge() const;
    double getLifeHourglassRabbits_oldAgeDivisorFactor() const;
    double getChangingTerritoryRabbits_flirtValue() const;
    double getChangingTerritoryRabbits_huntersValue() const;
    double getChangingTerritoryRabbits_grassLevel() const;
    double getMatingRabbits_factorDeathMaximuValueToMate() const;
    double getNumberOfBabyPerPregnancy() const;
    double getEatingRabbits_lifeLevelAddedPerMeal() const;
    double getEatingRabbits_lifeLevelNeedPerYear() const;

    static int getLifeHourglassRabbits_ageMaximumValue_Initial();

protected:
    bool huntAnAnimal(Animal *animalToHunt) ;
    bool beHuntedByAnAnimal(Animal *hunterAnimal) ;

    bool amIReadyToMateWith(Animal *theOneProposingAMate);
    bool amIReadyToFightWith(Animal *theOneProposingAFight);
    bool readyToMateWithARabbit();
    bool readyToMateWithAFox();


private:
    unsigned int m_rabbitId;


    void setIcon();

    static unsigned int m_livingRabbitsNb;
    static unsigned int m_totalRabbitsNb;

    static unsigned int m_nbOfBirthThisYear;
    static unsigned int m_nbOfUnsuccessfullDateThisYear;
    static unsigned int m_nbOfdeathThisYear;

    // Animal created at the begining
    static int const lifeLevelRabbits_valeurInitiale = 100 ;        // jauge de vie pour les lapins créés à l'initialisation du jeu

    // Facing death parameter
    static int const lifeHourglassRabbits_initialValue = 120;       // définit la hauteur pour toute la vie de l'échelle de vie, valeur pour les lapin créés à l'initialisation du jeu
    static int const lifeHourglassRabbits_birthVariationRange = 5; // naissance de l'enfant, variation héréditaire des paramètres de l'échelle de la vie de l'enfant par rapport à ces paraent

    double m_lifeHourglassRabbits_ageMaximumValue = lifeHourglassRabbits_ageMaximumValue_Initial;           // (Héréditaire) Valeur échelle de la vie à l'age old age, valeur pour les lapin créés à l'initialisation du jeu
    static int const lifeHourglassRabbits_ageMaximumValue_Initial = 10;
    static int const m_lifeHourglassRabbits_ageMaximumValue_Min = 1.0;
    double m_lifeHourglassRabbits_birthDivisorFactor = 2.0;         // (Héréditaire) Diviseur de m_liveHourglass pour obtenir la valeur échelle de la vie à la naissance, valeur pour les lapin créés à l'initialisation du jeu
    static int const m_lifeHourglassRabbits_birthDivisorFactor_Min = 1.0;
    double m_lifeHourglassRabbits_oldAge = 20.0;                    // (Héréditaire) Valeur du point old age de l'échelle de la vie, valeur pour les lapin créés à l'initialisation du jeu
    double m_lifeHourglassRabbits_oldAgeDivisorFactor = 2.5;        // (Héréditaire) Diviseur de m_liveHourglass pour obtenir la valeur échelle de la vie à l'a naissance'age old age, valeur pour les lapin créés à l'initialisation du jeu
    static int const m_lifeHourglassRabbits_oldAgeDivisorFactor_Min = 1.0;

    static double constexpr deathMaximumValueRabbits = 50.0;               // m_lifeHourglassRabbits * m_lifeLevel doivent être supérieur pour rester vivant

    // Changing territory flirting, staying safe alone or hunting
    static int const changingTerritoryRabbits_birthVariationRange = 5;     // Variation à la naissance des paramètres de choix du prochain territoire
    double m_changingTerritoryRabbits_flirtValue = 0.15;                     // (Héréditaire) Poids de l'envie de flirt dans la décision de chgt de territoire
    double m_changingTerritoryRabbits_huntersValue = 0.15;                   // (Héréditaire) Poids de l'envie de flirt dans la décision de chgt de territoire
    double m_changingTerritoryRabbits_grassLevel = 0.7;                     // (Héréditaire) Poids de l'envie d'herbe dans la décision de chgt de territoire

    // Mating
    static int const matingRabbits_birthVariationRange = 5;                // Variation à la naissance des paramètre de mating
    double m_matingRabbits_factorDeathMaximuValueToMate = 1.2;              // (Héréditaire) *  m_lifeHourglassRabbits * m_lifeLevel doit être supérieur à deathMaximumValue pour envisager mating
    double m_numberOfBabyPerPregnancy = 1;
    static double constexpr m_numberOfBabyPerPregnancy_Max = 4;
    static double constexpr m_numberOfBabyPerPregnancy_Min = 0.5;
    int m_matingRabbits_timeBetweenPregnancies = 1;                         // nbre d'année entre 2 grossesses
    int m_matingRabbits_flirtingBeginningAge = 3;                           // age de début du flirt
    static double constexpr m_matingRabbits_Seducing_Skills = 60.0;         // (Héréditaire)
    static double constexpr matingRabbits_dateSuccessHourglass = 100.0;     // somme des seducing skills des 2 partenaire doit être supérieur pour mate
    static double constexpr matingRabbits_dateSuccessVariation = 20.0;

    // Eating
    static int const eatingRabbits_birthVariationRange = 5;                // Variation à la naissance des paramètre eating
    double m_eatingRabbits_lifeLevelAddedPerMeal = 50.0;                    // ajout de vie par grass level
    static double constexpr m_eatingRabbits_lifeLevelAddedPerMeal_Max = 80.0;
    double m_eatingRabbits_lifeLevelNeedPerYear = 50.0;                     // perte de vie du à la faim par an
    static double constexpr m_eatingRabbits_lifeLevelNeedPerYear_Min = 20.0;

    // Hunting Fighting ;
    static int const fightingRabbits_birthVariationRange = 5;
    static double constexpr  fightingRabbits_attackingLiveLevel_initialValue = 0.0;
    static double constexpr fightingRabbits_defencingPreservingLiveLevel_initialValue = 20.0; //in Animal Class

};


#endif // LAPIN_H

#ifndef ChartData_H
#define ChartData_H

#include "lapin.h"
#include "renard.h"

class ChartData
{
public:
    ChartData();

    friend class ChartDatas;

protected:

    void addAFox(const Renard &theFoxToadd );
    void addARabbit(const Lapin &theRabbitToadd );

    friend bool operator==(const ChartData &left, const ChartData &right); // allow to use qEqual
    friend bool operator<(const ChartData &left, const ChartData &right); // allows to use qSort

private:
    void addAAnimal(const Animal &theAnimalToadd );

    int generation = 0;                              // average between the mother and the father generation
    int nbOfAnimals = 0;

    double lifeHourglass = 0.0;                           //
    double lifeHourglass_ageMaximumValue = 0.0;           //
    double lifeHourglass_birthDivisorFactor = 0.0;        //
    double lifeHourglass_oldAge = 0.0;                    //
    double lifeHourglass_oldAgeDivisorFactor = 0.0;       //
    double fighting_defencingPreservingLiveLevel = 0.0;   //
    double fighting_attackingDamagesToLiveLevel = 0.0;    //
    double mating_Seducing_Skills = 0.0;                  //
    double mating_factorDeathMaximuValueToMate = 0.0;     //
    double mating_numberOfBabyPerPregnancy = 0.0;         //
    double eating_lifeLevelAddedPerMeal = 0.0;            //
    double eating_lifeLevelNeedPerYear = 0.0;             //
    int deathAge = 0;                                     //


    double changingTerritory_flirtValueAgainstRabbitsNumber = 0.0;        //
    double changingTerritory_rabbitsNumberAgainstFlirtValue = 0.0;        //
    double changingTerritory_avoidingFightAgainstRabbitsNumber = 0.0;     //
    double changingTerritory_rabbitsNumberAgainstAvoidingFight = 0.0;     //

    double changingTerritory_flirtValue = 0.0;        //
    double changingTerritory_huntersValue = 0.0;      //
    double changingTerritory_grassLevel = 0.0;        //



};

#endif // ChartData_H

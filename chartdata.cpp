#include "chartdata.h"

ChartData::ChartData() : nbOfAnimals(0)
{

}

void ChartData::addAFox(const Renard &theFoxToadd)
{
    this->addAAnimal(theFoxToadd);

    this->lifeHourglass_ageMaximumValue += theFoxToadd.getLifeHourglassFoxes_ageMaximumValue();
    this->lifeHourglass_birthDivisorFactor += theFoxToadd.getLifeHourglassFoxes_birthDivisorFactor();
    this->lifeHourglass_oldAge += theFoxToadd.getLifeHourglassFoxes_oldAge();
    this->lifeHourglass_oldAgeDivisorFactor += theFoxToadd.getLifeHourglassFoxes_oldAgeDivisorFactor();

    this->mating_factorDeathMaximuValueToMate += theFoxToadd.getMatingFoxes_factorDeathMaximuValueToMate();
    // this->mating_numberOfBabyPerPregnancy only for rabbit
    this->eating_lifeLevelAddedPerMeal+= theFoxToadd.getEatingFoxes_lifeLevelAddedPerRabbit();
    this->eating_lifeLevelNeedPerYear+= theFoxToadd.getEatingFoxes_lifeLevelNeedPerYear();

    this->changingTerritory_flirtValueAgainstRabbitsNumber += theFoxToadd.getChangingTerritoryFoxes_flirtValueAgainstRabbitsNumber();
    this->changingTerritory_rabbitsNumberAgainstFlirtValue += theFoxToadd.getChangingTerritoryFoxes_rabbitsNumberAgainstFlirtValue();
    this->changingTerritory_avoidingFightAgainstRabbitsNumber += theFoxToadd.getChangingTerritoryFoxes_avoidingFightAgainstRabbitsNumber();
    this->changingTerritory_rabbitsNumberAgainstAvoidingFight += theFoxToadd.getChangingTerritoryFoxes_rabbitsNumberAgainstFlirtValue();

}


void ChartData::addARabbit(const Lapin &theRabbitToadd)
{
    this->addAAnimal(theRabbitToadd);

    this->lifeHourglass_ageMaximumValue += theRabbitToadd.getLifeHourglassRabbits_ageMaximumValue();
    this->lifeHourglass_birthDivisorFactor += theRabbitToadd.getLifeHourglassRabbits_birthDivisorFactor();
    this->lifeHourglass_oldAge += theRabbitToadd.getLifeHourglassRabbits_oldAge();
    this->lifeHourglass_oldAgeDivisorFactor += theRabbitToadd.getLifeHourglassRabbits_oldAgeDivisorFactor();

    this->mating_factorDeathMaximuValueToMate += theRabbitToadd.getMatingRabbits_factorDeathMaximuValueToMate();
    this->mating_numberOfBabyPerPregnancy += theRabbitToadd.getNumberOfBabyPerPregnancy();
    this->eating_lifeLevelAddedPerMeal+= theRabbitToadd.getEatingRabbits_lifeLevelAddedPerMeal();
    this->eating_lifeLevelNeedPerYear+= theRabbitToadd.getEatingRabbits_lifeLevelNeedPerYear();

    this->changingTerritory_flirtValue+= theRabbitToadd.getChangingTerritoryRabbits_flirtValue();
    this->changingTerritory_huntersValue+=theRabbitToadd.getChangingTerritoryRabbits_huntersValue();
    this->changingTerritory_grassLevel+=theRabbitToadd.getChangingTerritoryRabbits_grassLevel();

}

void ChartData::addAAnimal(const Animal &theAnimalToadd)
{
    this->nbOfAnimals++;
    this->deathAge += theAnimalToadd.GetAge();
    this->lifeHourglass += theAnimalToadd.getLifeHourglass();
    this->mating_Seducing_Skills += theAnimalToadd.getMating_Seducing_Skills();
    this->fighting_attackingDamagesToLiveLevel += theAnimalToadd.getFighting_attackingDamagesToLiveLevel();
    this->fighting_defencingPreservingLiveLevel += theAnimalToadd.getFighting_defencingPreservingLiveLevel();
}

bool operator==(const ChartData &left, const ChartData &right)
{
    return (left.generation == right.generation);
}

bool operator<(const ChartData &left, const ChartData &right)
{
    return (left.generation < right.generation);
}

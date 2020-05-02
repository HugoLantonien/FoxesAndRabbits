#pragma once

#ifndef ANIMAL_H
#define ANIMAL_H

#include <QString>
#include <QObject>

class Territory;

class Animal : public QObject
{

public:
    typedef enum {
        E_readyToMateNoBecauseOfAge,
        E_readyToMateNoBecauseLastPregnancy,
        E_readyToMateNoBecauseOfLiveLevel,
        E_readyToMateYes
    } E_readyToMate;

    virtual void faceToDeath(void)=0 ;
    virtual QString coutLight(void) const=0;
    virtual unsigned int canIBeHunted() const=0;
    virtual unsigned int canIHunt() const=0;
    virtual void moveToABetterPlace(void) = 0;

    virtual E_readyToMate readyToMate(void) const = 0;
    virtual ~Animal();
    virtual void coutComplete(void) const;
    virtual void confrontationWithAnotherAnimal(Animal *otherAnimal) = 0;
    virtual void annualDecreaseOfLifeLevel() = 0;
    virtual bool IEatSomeGrass(double portion) = 0;
    virtual bool amIReadyToMateWith(Animal *theOneProposingAMate) = 0;
    virtual bool amIReadyToFightWith(Animal *theOneProposingAFight) = 0;
    virtual bool readyToMateWithARabbit() = 0;
    virtual bool readyToMateWithAFox() = 0;
    virtual bool huntAnAnimal(Animal *animalToHunt) = 0 ;
    virtual bool beHuntedByAnAnimal(Animal *hunterAnimal) = 0 ;

    void attacking(Animal *otherAnimal);
    void beingAttacked(Animal *otherAnimal);


    void setAnimalTerritory(Territory *animalTerritory);
    Territory *getAnimalTerritory() const;

    bool Getalive() const { return m_alive; }
    bool GetFaceToDeath(double lifeHourglass_dependingOnAge, double deathMaximuValue);
    double lifeLevel() const;
    double getLifeHourglass() const;

    bool woman() const;
    double getGeneration() const;
    int getBirthDate() const;
    int GetAge(void) const;

    unsigned int getIcon() const;

    double getMating_Seducing_Skills() const;

    double getFighting_defencingPreservingLiveLevel() const;
    double getFighting_attackingDamagesToLiveLevel() const;
    void deletionOfTheAnimal();


protected:

    Animal(QObject *parent = nullptr);
    Animal(Animal &mere, Animal &pere, QObject *parent = nullptr);

    void birthSetlifeHourglass(Animal &mere, Animal &pere, double variationNaissance);
    void birthSetFightingSkills(Animal &mere, Animal &pere, double variationNaissance);
    void birthSetSeducingSkills(Animal &mere, Animal &pere, double variationNaissance);
    double getLifeHourglassDependingOnAge(double lifeHourglass_ageMaximumValue,
                                          double lifeHourglass_birthDivisorFactor,
                                          double lifeHourglass_oldAge,
                                          double lifeHourglass_oldAgeDivisorFactor) const;

    void setLifeHourglass(double lifeHourglass);

    void setLifeLevel(double lifeLevel);

    void setFighting_defencingPreservingLiveLevel(double fighting_defencingPreservingLiveLeve);
    void setFighting_attackingDamagesToLiveLevel(double fighting_attackingDamagesToLiveLevel);
    void setMating_Seducing_Skills(double mating_Seducing_Skills);

    void death(void);



    int m_lastPregnancyDate = -2;
    unsigned int m_icon;


private:

    Territory *m_animalTerritory;
    unsigned int m_animalId;
    unsigned int m_generationFatherWay;
    unsigned int m_generationMotherWay;
    bool m_alive;
    bool m_woman;
    double m_lifeHourglass;
    static double constexpr m_lifeHourglass_Max = 150;
    double m_lifeLevel;
    Animal *pere;
    Animal *mere;
    int m_birthDate;
    double m_fighting_defencingPreservingLiveLevel;
    double m_fighting_attackingDamagesToLiveLevel;
    double m_mating_Seducing_Skills;

    virtual void setIcon()=0;

};


#endif // ANIMAL_H


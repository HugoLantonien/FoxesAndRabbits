#pragma once


#ifndef ANIMALSLIST_H
#define ANIMALSLIST_H

#include "animalslistnode.h"
#include <QVector>

class AnimalsList
{
public:
    AnimalsList();
    ~AnimalsList();

    void addAnimalToList(Animal *animalToAdd);
    bool removeAnimalFromList(Animal *animalToRemove);

    Animal *getLastAnimalAddedAndMove(void);
    Animal *getNextAnimalAddedAndMove(void);
    Animal *getAnimalAddedAPositionFurther(unsigned int numberOfPositions );

    unsigned int getTotalAnimalsInList() const;
    unsigned int getTotalAnimalsInListByRecounting(); // for debug


private:

    unsigned int m_totalAnimalsInList = 0;
    AnimalsListNode *m_animalListEnd;
    AnimalsListNode *m_animalListNodeCurrent;


};

#endif // ANIMALSLIST_H

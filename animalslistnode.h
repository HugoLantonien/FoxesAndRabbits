#pragma once

#ifndef ANIMALSLISTNODE_H
#define ANIMALSLISTNODE_H


#include "animal.h"


class AnimalsListNode
{
    friend class AnimalsList;

private:
    AnimalsListNode(Animal *animalToAdd, AnimalsListNode *nextNodeToAdd);
    ~ AnimalsListNode();

    Animal *nodeAnimal;
    AnimalsListNode *nextNode;
    AnimalsListNode *previousNode;


};

#endif // ANIMALSLISTNODE_H

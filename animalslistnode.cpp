#include "animalslistnode.h"
#include "animals.h"

AnimalsListNode::AnimalsListNode(Animal *animalToAdd, AnimalsListNode *nextNodeToAdd)
    : nodeAnimal(animalToAdd), nextNode(nextNodeToAdd), previousNode(nullptr)
{

}

AnimalsListNode::~AnimalsListNode()
{

}

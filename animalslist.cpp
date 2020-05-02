#include "animalslist.h"
#include "animalslistnode.h"
#include "animals.h"
#include <QDebug>




AnimalsList::AnimalsList()
{
    m_animalListEnd = nullptr;
    m_animalListNodeCurrent = nullptr;
}

AnimalsList::~AnimalsList()
{
    AnimalsListNode *nodeToDelete;

    while (m_animalListEnd != nullptr)
    {
        nodeToDelete = m_animalListEnd;
        m_animalListEnd = m_animalListEnd->nextNode;
        delete nodeToDelete;
    }
}

void AnimalsList::addAnimalToList(Animal *animalToAdd)
{
    AnimalsListNode *newNode = new AnimalsListNode(animalToAdd, m_animalListEnd);
    if(m_animalListEnd !=nullptr)
    {
        m_animalListEnd->previousNode = newNode;
    }
    m_animalListEnd = newNode;
    m_totalAnimalsInList++;
}

bool AnimalsList::removeAnimalFromList(Animal *animalToRemove)
{
    AnimalsListNode *currentNode = m_animalListEnd;

    while(currentNode != nullptr)
    {
        if(animalToRemove == currentNode->nodeAnimal)
        {
            if(currentNode->previousNode != nullptr)
            {
                (currentNode->previousNode)->nextNode = currentNode->nextNode;
            }
            if(currentNode->nextNode != nullptr)
            {
                (currentNode->nextNode)->previousNode = currentNode->previousNode;
            }

            if(m_animalListEnd == currentNode)
            {
                m_animalListEnd = currentNode->nextNode;
            }

            delete currentNode;
            currentNode = nullptr;
            m_totalAnimalsInList--;
            return true;
        }
        currentNode = currentNode->nextNode;
    }
    return false;

}
Animal *AnimalsList::getLastAnimalAddedAndMove(void)
{
    m_animalListNodeCurrent = m_animalListEnd;
    if(m_animalListNodeCurrent != nullptr)
    {
        return m_animalListNodeCurrent->nodeAnimal;
    }
    else
    {
        return nullptr;
    }
}

Animal *AnimalsList::getNextAnimalAddedAndMove(void)
{
    if(m_animalListNodeCurrent != nullptr)
    {
        if(m_animalListNodeCurrent->nextNode != nullptr)
        {
            m_animalListNodeCurrent = m_animalListNodeCurrent->nextNode;
            return m_animalListNodeCurrent->nodeAnimal;
        }
        else
        {
            return nullptr;
        }
    }
    else
    {
        return nullptr;
    }
}

Animal* AnimalsList::getAnimalAddedAPositionFurther(unsigned int numberOfPositions)
{

    AnimalsListNode *nodeToExplore =  m_animalListNodeCurrent;

    for(unsigned int p = 0 ; p < numberOfPositions ; p++)
    {
        if(nodeToExplore != nullptr)
        {
            if(nodeToExplore->nextNode != nullptr)
            {
                nodeToExplore = nodeToExplore->nextNode;
            }
            else
            {
                return nullptr;
            }
        }
        else
        {
            return nullptr;
        }
    }
    return nodeToExplore->nodeAnimal;

}

unsigned int AnimalsList::getTotalAnimalsInList() const
{
    return m_totalAnimalsInList;
}

unsigned int AnimalsList::getTotalAnimalsInListByRecounting()
{
    unsigned int counter = 0;
    Animal *currentAnimal = this->getLastAnimalAddedAndMove();

    while (currentAnimal != nullptr) {
        counter++;
        currentAnimal = this->getNextAnimalAddedAndMove();
    }
return counter;
}



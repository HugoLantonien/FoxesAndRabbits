#include "yearscounter.h"
#include "animals.h"
#include "animal.h"
#include "renard.h"
#include "territories.h"
#include "territory.h"
#include "territoriestodraw.h"
#include <QDebug>
#include "chartdatas.h"


yearsCounter* yearsCounter::instance = nullptr;


yearsCounter::yearsCounter(QObject *parent):
    QObject (parent), m_date(0)
{
    qDebug() << "got years counter on" ;
}

int yearsCounter::getNbOfYearToPlay() const
{
    return m_nbOfYearToPlay;
}

void yearsCounter::setNbOfYearToPlay(int nbOfYearToPlay)
{
    qDebug()<< "nbOfYearToPlay : " << m_nbOfYearToPlay << " ==> " << nbOfYearToPlay;
    if(nbOfYearToPlay != m_nbOfYearToPlay)
    {
        m_nbOfYearToPlay = nbOfYearToPlay;
        emit nbOfYearToPlayChanged();
    }
}

int yearsCounter::getDate() const
{
    return m_date;
}


yearsCounter* yearsCounter::getInstance()
{
    if(yearsCounter::instance == nullptr)
    {
        yearsCounter::instance = new yearsCounter;
        //yearsCounter::instance->playYears(0);
    }
    return yearsCounter::instance;
}

void yearsCounter::playYears(int nbYearsToPlay)
{

    static bool continueRunning = true;
    bool log = false;

    for (int newYear = 0 ; newYear < nbYearsToPlay && continueRunning == true; newYear++ ) {

        // Initialisation des compteurs annuels
        Renard::yearNumberInitialization();
        Lapin::yearNumberInitialization();

        // jeu de l'année
        Animals::getInstance()->moveToABetterPlace(); // using animal list
        Territories::getInstance()->aYearOfHappeningInsideTerritories(); //eating grass and then confrontation in each territory
        Animals::getInstance()->deathWindOnAnimals(); // face to death and then annual decrease of life

        // Statistics and log
        ChartDatas::getInstance()->addAYear(m_date);
        if(log)
        {
            // trace de fin d'année
            qDebug() << "**********************"<< "end of year (" << m_date << ")" << "*******************************" ;
            qDebug() << "Living foxes (" << Renard::getLivingFoxesNb() << "), total (" << Renard::getTotalFoxesNb()<< ")";
            qDebug() << "birth (" << Renard::getNbOfBirthThisYear() << "), missed date (" << Renard::getNbOfUnsuccessfullDateThisYear();
            qDebug() << "death (" << Renard::getNbOfdeathThisYear() << "), cause of fight (" << Renard::getNbOfDeathDueToFightThisYear() << ")" << "total fight(" << Renard::getNbOfFightThisYear() << ")";
            qDebug() << "****";
            qDebug() << "Living rabbits (" << Lapin::getLivingRabbitsNb() << "), total (" << Lapin::getTotalRabbitsNb()<< ")";
            qDebug() << "birth (" << Lapin::getNbOfBirthThisYear() << "), missed date (" << Lapin::getNbOfUnsuccessfullDateThisYear();
            qDebug() << "death (" << Lapin::getNbOfdeathThisYear() << "), cause of Hunt (" << Renard::getNbOfSuccessufHuntThisYear() << ")" << "total hunt (" << Renard::getNbOfHuntThisYear() << ")";


            // quelques calculs pour le contrôle de cohérence
            unsigned int numberOfAnimalInTerritoriesByListCounter = Territories::getInstance()->getTotalAnimalsInTerritoriesByListCounter();
            unsigned int numberOfAnimalInTerritoriesByRecounting = Territories::getInstance()->getTotalAnimalsInTerritoriesByRecounting();
            unsigned int numberOfAnimalInListByListCounter = Animals::getInstance()->getTotalAnimalsInAnimalsListByListCounter();
            unsigned int numberOfAnimalInListByRecounting = Animals::getInstance()->getTotalAnimalsInAnimalsListByRecounting();
            unsigned int numberOfAnimalInListByCounter = Animals::getInstance()->getLivingAnimalsNb();

            // Traces contrôle de cohérence
            qDebug() << "nb in territories (" << numberOfAnimalInTerritoriesByListCounter << ", " << numberOfAnimalInTerritoriesByRecounting << "), "
                     << "nb in list (" << numberOfAnimalInListByListCounter << ", " << numberOfAnimalInListByRecounting << "), "
                     << "nb fox/rabbit counter (" << Lapin::getLivingRabbitsNb() + Renard::getLivingFoxesNb() << "), "
                     << "nb animal counter (" << numberOfAnimalInListByCounter <<")" ;
        }


        // sortie de la boucle
        m_date++;
        if (Renard::getLivingFoxesNb() <= 0 || Lapin::getLivingRabbitsNb() <=0 || (Renard::getLivingFoxesNb()+Lapin::getLivingRabbitsNb()) > 40000){
            continueRunning = false;
        }

    }



}

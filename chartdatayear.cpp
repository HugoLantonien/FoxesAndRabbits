#include "chartdatayear.h"
#include "renard.h"
#include "lapin.h"

ChartDataYear::ChartDataYear()
{

}

void ChartDataYear::addAYear()
{
    this->m_yearsNumber++;
    this->m_nbOfFoxesBirth += Renard::getNbOfBirthThisYear();
    this->m_nbOfFoxesDeath += Renard::getNbOfdeathThisYear();
    this->m_nbOfRabbitsBirth += Lapin::getNbOfBirthThisYear();
    this->m_nbOfRabbitsDeath += Lapin::getNbOfdeathThisYear();
    this->m_nbOfFoxesDeathDueToFight += Renard::getNbOfDeathDueToFightThisYear();
    this->m_nbOfRabbitsDeathDueToHunt += Renard::getNbOfSuccessufHuntThisYear();
    this->m_nbOfFoxesUnsuccessfullDate += Renard::getNbOfUnsuccessfullDateThisYear();
    this->m_nbOfRabbitsUnsuccessfullDate += Lapin::getNbOfUnsuccessfullDateThisYear();
    this->m_nbOfLivingRabbits += Lapin::getLivingRabbitsNb();
    this->m_nbOfLivingFoxes += Renard::getLivingFoxesNb();
}

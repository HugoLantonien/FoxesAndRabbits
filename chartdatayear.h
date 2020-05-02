#ifndef CHARTDATAYEAR_H
#define CHARTDATAYEAR_H


class ChartDataYear
{
public:
    ChartDataYear();

    friend class ChartDatas;

    void addAYear();

private:
    int m_year = 0;
    int m_yearsNumber = 0;
    int m_nbOfLivingRabbits = 0;
    int m_nbOfRabbitsBirth = 0;
    int m_nbOfRabbitsUnsuccessfullDate = 0;
    int m_nbOfRabbitsDeath = 0;
    int m_nbOfRabbitsDeathDueToHunt = 0;
    int m_nbOfLivingFoxes = 0;
    int m_nbOfFoxesBirth = 0;
    int m_nbOfFoxesUnsuccessfullDate = 0;
    int m_nbOfFoxesDeath = 0;
    int m_nbOfFoxesDeathDueToFight = 0;

};

#endif // CHARTDATAYEAR_H

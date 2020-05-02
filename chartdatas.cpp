#include <QtMath>
#include <QDebug>
#include "chartdata.h"
#include "chartdatayear.h"
#include "chartdatas.h"
#include "renard.h"
#include "animals.h"

ChartDatas *ChartDatas::instance = nullptr;

QString const descriptionCurve_lifeHourglassCurve =  "Evolution through generations of the life level maximum depending on age (the highest it is the farest death is).";
QString const descriptionCurve_seducingSkills =  "Evolution through generations of the seducing skills, if high then meeting will mean mating";
QString const descriptionCurve_yearPopulation =  "Evolution of rabbits and foxes population";
QString const bug =  "Shall not be displayed";

QString const ChartDatas::graphDescription [Animal_noMoreAnimal] [Graph_noMoreCurve]  =
{
    {
        /* graph_lifeHourglassCurve,                            */  descriptionCurve_lifeHourglassCurve,
        /* graph_attackingDefencingSkills,                      */  "Evolution through generations of the attacking and defending skills, used when a fox fights against a fox, or when it hunts a rabbit",
        /* graph_seducingSkills,                                */  descriptionCurve_seducingSkills,
        /* graph_lifeLevelAddedPerMealNeededPerYear,            */  "Evolution through generations of the life level added when eating a rabbit (max "  + QString::number(Renard::eatingFoxes_maxNumberOfMealsTakenPerYear) + " per years) and needed for one year life",
        /* graph_rabbit_numberOfBabyPerPregnancy,               */  bug,
        /* graph_rabbit_changingTerritoryCriteria,              */  bug,
        /* graph_fox_changingTerritoryCriteriasIfHighLifeLevel, */  "Evolution through generations of the choosing a new territory criterias in case of high life level, hunting a lot of rabbit or having a lot of date",
        /* graph_fox_changingTerritoryCriteriasIfLowLifeLevel,  */  "Evolution through generations of the choosing a new territory criterias in case of high life level, hunting a lot of rabbit or avoiding fights",
        /* Graph_year_population                                */  "Evolution through years of the rabbits and foxes population",
        /* Graph_year_rabbits                                   */  bug,
        /* Graph_year_foxes                                     */  "Evolution through years of the foxes birth, death"
    },
    {
        /* graph_lifeHourglassCurve,                            */  descriptionCurve_lifeHourglassCurve,
        /* graph_attackingDefencingSkills,                      */  "Evolution through generations of the defending skills, used when being hunted by a fox",
        /* graph_seducingSkills,                                */  descriptionCurve_seducingSkills,
        /* graph_lifeLevelAddedPerMealNeededPerYear,            */  "Evolution through generations of the life level added when eating all the year's grass available and needed for one year life",
        /* graph_rabbit_numberOfBabyPerPregnancy,               */  "Evolution through generations of the average number of babies",
        /* graph_rabbit_changingTerritoryCriteria,              */  "Evolution through generations of the choosing a new territory criterias, avoiding hunters or having a lot of date or eating a lot of grasse",
        /* graph_fox_changingTerritoryCriteriasIfHighLifeLevel, */  bug,
        /* graph_fox_changingTerritoryCriteriasIfLowLifeLevel,  */  bug,
        /* Graph_year_population                                */  "Evolution through years of the rabbits and foxes population",
        /* Graph_year_rabbits                                   */  "Evolution through years of the rabbits birth, death",
        /* Graph_year_foxes                                     */  bug
    }
};

QString const ChartDatas::graphTitle [Graph_noMoreCurve]  =
{
    /* graph_lifeHourglassCurve,                            */  "Life level vs age",
    /* graph_attackingDefencingSkills,                      */  "Attacking and defending skills",
    /* graph_seducingSkills,                                */  "Seducing skills",
    /* graph_lifeLevelAddedPerMealNeededPerYear,            */  "Eating and living a year",
    /* graph_rabbit_numberOfBabyPerPregnancy,               */  "Number of babies",
    /* graph_rabbit_changingTerritoryCriteria,              */  "Changing territory",
    /* graph_fox_changingTerritoryCriteriasIfHighLifeLevel, */  "Changing territory (high life level)",
    /* graph_fox_changingTerritoryCriteriasIfLowLifeLevel,  */  "Changing territory (low life level)",
    /* Graph_year_population                                */  "Population evolution",
    /* Graph_year_rabbits                                   */  "Rabbits deaths and births",
    /* Graph_year_foxes                                     */  "foxes deaths and births",
};

unsigned int const ChartDatas::numberOfSeries[Graph_noMoreCurve] =
{
    /* graph_lifeHourglassCurve,                            */  4,
    /* graph_attackingDefencingSkills,                      */  2,
    /* graph_seducingSkills,                                */  1,
    /* graph_lifeLevelAddedPerMealNeededPerYear,            */  2,
    /* graph_rabbit_numberOfBabyPerPregnancy,               */  1,
    /* graph_rabbit_changingTerritoryCriteria,              */  3,
    /* graph_fox_changingTerritoryCriteriasIfHighLifeLevel, */  2,
    /* graph_fox_changingTerritoryCriteriasIfLowLifeLevel,  */  2,
    /* Graph_year_population                                */  2,
    /* Graph_year_rabbits                                   */  4,
    /* Graph_year_foxes                                     */  4
};


bool const ChartDatas::basedOnGeneration[Graph_noMoreCurve] =
{
    /* graph_lifeHourglassCurve,                            */  true,
    /* graph_attackingDefencingSkills,                      */  true,
    /* graph_seducingSkills,                                */  true,
    /* graph_lifeLevelAddedPerMealNeededPerYear,            */  true,
    /* graph_rabbit_numberOfBabyPerPregnancy,               */  true,
    /* graph_rabbit_changingTerritoryCriteria,              */  true,
    /* graph_fox_changingTerritoryCriteriasIfHighLifeLevel, */  true,
    /* graph_fox_changingTerritoryCriteriasIfLowLifeLevel,  */  true,
    /* Graph_year_population                                */  false,
    /* Graph_year_rabbits                                   */  false,
    /* Graph_year_foxes                                     */  false
};

QString const ChartDatas::seriesTitle[Graph_noMoreCurve] [maxNumberOfSeries]=
{
    /* graph_lifeHourglassCurve,                            */  {"age=0",       "Adult",                                    "Old",                                  "at death time"},
    /* graph_attackingDefencingSkills,                      */  {"attacking",   "defending",                                bug,                                    bug},
    /* graph_seducingSkills,                                */  {"value",       bug,                                        bug,                                    bug},
    /* graph_lifeLevelAddedPerMealNeededPerYear,            */  {"+ eating",    "- needed",                                 bug,                                    bug},
    /* graph_rabbit_numberOfBabyPerPregnancy,               */  {"number",      bug,                                        bug,                                    bug},
    /* graph_rabbit_changingTerritoryCriteria,              */  {"- hunters",   "+ grass",                                  "+ dates",                              bug},
    /* graph_fox_changingTerritoryCriteriasIfHighLifeLevel, */  {"+ rabbits",   "+ dates",                                  bug,                                    bug},
    /* graph_fox_changingTerritoryCriteriasIfLowLifeLevel,  */  {"+ rabbits",   "- fights",                                 bug,                                    bug},
    /* Graph_year_population                                */  {"rabbits",     "foxes",                                    bug,                                    bug},
    /* Graph_year_rabbits                                   */  {"births",      "unsuccesfull date",                        "deaths",                               "hunting deaths"},
    /* Graph_year_foxes                                     */  {"births",      "unsuccesfull date",                        "deaths",                               "fighting deaths"}

};


ChartDatas::E_GraphKind const ChartDatas::foxCharts[] = {
    ChartDatas::Graph_lifeHourglassCurve,                               // 0
    ChartDatas::Graph_attackingDefencingSkills,                         // 1
    ChartDatas::Graph_seducingSkills,                                   // 2
    ChartDatas::Graph_lifeLevelAddedPerMealNeededPerYear,               // 3
    ChartDatas::Graph_fox_changingTerritoryCriteriasIfHighLifeLevel,    // 6
    ChartDatas::Graph_fox_changingTerritoryCriteriasIfLowLifeLevel,     // 7
    ChartDatas::Graph_year_population,                                  // 8
    ChartDatas::Graph_year_foxes                                        // 9
};

ChartDatas::E_GraphKind const ChartDatas::rabbitCharts[] = {
    ChartDatas::Graph_lifeHourglassCurve,                               // 0
    ChartDatas::Graph_attackingDefencingSkills,                         // 1
    ChartDatas::Graph_seducingSkills,                                   // 2
    ChartDatas::Graph_lifeLevelAddedPerMealNeededPerYear,               // 3
    ChartDatas::Graph_rabbit_numberOfBabyPerPregnancy,                  // 4
    ChartDatas::Graph_rabbit_changingTerritoryCriteria,                 // 5
    ChartDatas::Graph_year_population,                                  // 8
    ChartDatas::Graph_year_rabbits                                      // 9
};



ChartDatas::ChartDatas(QObject *parent):
    QObject (parent),
    m_graphTitle(ChartDatas::graphTitle[m_currentChartNumber]),
    m_graphDescription(ChartDatas::graphDescription [m_animal] [m_currentChartNumber])
{

}


ChartDatas *ChartDatas::getInstance()
{
    if(instance == nullptr)
    {
        instance = new ChartDatas();
    }
    return instance;
}


ChartDatas::E_GraphKind ChartDatas::getCurrentChartNumber() const
{
    return m_currentChartNumber;
}

ChartDatas::E_GraphAnimal ChartDatas::getAnimal() const
{
    return m_animal;
}

void ChartDatas::setAnimal(const ChartDatas::E_GraphAnimal &animal)
{
    if(animal != m_animal)
    {
        m_animal = animal;
        emit animalChanged();
    }
}

QString ChartDatas::getGraphTitle() const
{
    return m_graphTitle;
}

QString ChartDatas::getGraphDescription() const
{

    return m_graphDescription;
}

unsigned int ChartDatas::getNumberOfSeries() const
{
    return m_numberOfSeries;
}


void ChartDatas::prepareGraphics(int graphicCounter)
{
    bool log = true;

    if(log)
        qDebug() << "prepareGraphics";

    unsigned int myCounter = (unsigned int) (graphicCounter);
    ChartDatas::E_GraphKind graphToDraw;

    if(m_animal == Animal_fox)
    {
        unsigned int myChart = myCounter % (sizeof(foxCharts)/sizeof(foxCharts[0]));
        graphToDraw = foxCharts[myChart];
    }
    else
    {
        unsigned int myChart = myCounter % (sizeof(rabbitCharts)/sizeof(rabbitCharts[0]));
        graphToDraw = rabbitCharts[myChart];
    }

    setCurrentChartNumber(graphToDraw);
    setGraphTitle(ChartDatas::graphTitle[graphToDraw]);
    setGraphDescription(ChartDatas::graphDescription[m_animal][graphToDraw]);
    setNumberOfSeries(ChartDatas::numberOfSeries[graphToDraw], true);

    m_valueMax = 0;
    m_valueMin = 999999999999999;

}

void ChartDatas::prepareSerie(QLineSeries *lineSerie, unsigned int lineSerieNumber)
{
    // Some initializations
    bool log = false;
    double valueMin = m_valueMin, valueMax = m_valueMax;
    lineSerie->clear(); // remove all points
    double x=0.0, y=0.0;
    lineSerie->setName(ChartDatas::seriesTitle[m_currentChartNumber] [lineSerieNumber]);


    // graph based on generation
    if(ChartDatas::basedOnGeneration[m_currentChartNumber])
    {
        QVector<ChartData> *generation = &m_generationCurveRabbits ;
        int lifeHourglass_ageMaximumValue_Initial = Lapin::getLifeHourglassRabbits_ageMaximumValue_Initial();

        if(m_animal == Animal_fox)
        {
            generation = &m_generationCurveFoxes;
            lifeHourglass_ageMaximumValue_Initial = Renard::getLifeHourglassFoxes_ageMaximumValue_Initial();
        }


        if(log)
            qDebug() << "prepareSerie : &generation = " << generation
                     << ", &fox = " << &m_generationCurveFoxes
                     << ", &rabbit = " << &m_generationCurveRabbits;

        for(int i = 0 ; i < generation->count() ; i++)
        {
            if((*generation)[i].nbOfAnimals ==0)
            {
                y=0;
            }
            else
            {
                switch (m_currentChartNumber) {

                case Graph_lifeHourglassCurve:

                    switch (lineSerieNumber) {

                    case 0: // life hourglass at birthtime
                        y = Animals::getLifeHourglassDependingOnAge(
                                    0,
                                    (*generation)[i].lifeHourglass / (*generation)[i].nbOfAnimals,
                                    (*generation)[i].lifeHourglass_ageMaximumValue / (*generation)[i].nbOfAnimals,
                                    (*generation)[i].lifeHourglass_birthDivisorFactor / (*generation)[i].nbOfAnimals,
                                    (*generation)[i].lifeHourglass_oldAge / (*generation)[i].nbOfAnimals,
                                    (*generation)[i].lifeHourglass_oldAgeDivisorFactor / (*generation)[i].nbOfAnimals
                                    ) ;
                        break;

                    case 1: // life hourglass at age maximum value
                        y = Animals::getLifeHourglassDependingOnAge(
                                    lifeHourglass_ageMaximumValue_Initial,
                                    (*generation)[i].lifeHourglass / (*generation)[i].nbOfAnimals,
                                    (*generation)[i].lifeHourglass_ageMaximumValue / (*generation)[i].nbOfAnimals,
                                    (*generation)[i].lifeHourglass_birthDivisorFactor / (*generation)[i].nbOfAnimals,
                                    (*generation)[i].lifeHourglass_oldAge / (*generation)[i].nbOfAnimals,
                                    (*generation)[i].lifeHourglass_oldAgeDivisorFactor / (*generation)[i].nbOfAnimals
                                    ) ;
                        break;

                    case 2: // life hourglass at age maximum value
                        y = Animals::getLifeHourglassDependingOnAge(
                                    lifeHourglass_ageMaximumValue_Initial * 2,
                                    (*generation)[i].lifeHourglass / (*generation)[i].nbOfAnimals,
                                    (*generation)[i].lifeHourglass_ageMaximumValue / (*generation)[i].nbOfAnimals,
                                    (*generation)[i].lifeHourglass_birthDivisorFactor / (*generation)[i].nbOfAnimals,
                                    (*generation)[i].lifeHourglass_oldAge / (*generation)[i].nbOfAnimals,
                                    (*generation)[i].lifeHourglass_oldAgeDivisorFactor / (*generation)[i].nbOfAnimals
                                    ) ;
                        break;

                    case 3: // life hourglass at death age
                        y = Animals::getLifeHourglassDependingOnAge(
                                    lround((*generation)[i].deathAge / (*generation)[i].nbOfAnimals),
                                    (*generation)[i].lifeHourglass / (*generation)[i].nbOfAnimals,
                                    (*generation)[i].lifeHourglass_ageMaximumValue / (*generation)[i].nbOfAnimals,
                                    (*generation)[i].lifeHourglass_birthDivisorFactor / (*generation)[i].nbOfAnimals,
                                    (*generation)[i].lifeHourglass_oldAge / (*generation)[i].nbOfAnimals,
                                    (*generation)[i].lifeHourglass_oldAgeDivisorFactor / (*generation)[i].nbOfAnimals
                                    ) ;

                        break;

                    default:
                        y=0;
                        break;
                    }
                    // some log
                    log=false;
                    if(log)
                    {
                        double division;
                        if((*generation)[i].nbOfAnimals !=0)
                            division = (*generation)[i].nbOfAnimals;
                        else
                            division = 1;

                        qDebug() << "x=" << x << ", y=" << y
                                 << ", nb=" << (*generation)[i].nbOfAnimals
                                 << ", bd=" << (*generation)[i].lifeHourglass_birthDivisorFactor / division
                                 << ", aM=" << (*generation)[i].lifeHourglass_ageMaximumValue / division
                                 << ", aMV=" << (*generation)[i].lifeHourglass / division
                                 << ", oA=" << (*generation)[i].lifeHourglass_oldAge / division
                                 << ", oAd=" << (*generation)[i].lifeHourglass_oldAgeDivisorFactor /division
                                    ;
                    }
                    break;

                case Graph_attackingDefencingSkills:
                    switch (lineSerieNumber) {
                    case 0:  y = (*generation)[i].fighting_attackingDamagesToLiveLevel / (*generation)[i].nbOfAnimals;      break;
                    case 1:  y = (*generation)[i].fighting_defencingPreservingLiveLevel / (*generation)[i].nbOfAnimals;     break;
                    default: y =0; break;
                    }
                    break;

                case Graph_seducingSkills:
                    switch (lineSerieNumber) {
                    case 0:  y = (*generation)[i].mating_Seducing_Skills / (*generation)[i].nbOfAnimals;          break;
                    default: y =0; break;
                    }
                    break;

                case Graph_lifeLevelAddedPerMealNeededPerYear:
                    switch (lineSerieNumber) {
                    case 0:  y = (*generation)[i].eating_lifeLevelAddedPerMeal / (*generation)[i].nbOfAnimals;    break;
                    case 1:  y = (*generation)[i].eating_lifeLevelNeedPerYear / (*generation)[i].nbOfAnimals;     break;
                    default: y =0; break;
                    }
                    break;

                case Graph_rabbit_numberOfBabyPerPregnancy:
                    switch (lineSerieNumber) {
                    case 0:  y = (*generation)[i].mating_numberOfBabyPerPregnancy / (*generation)[i].nbOfAnimals;      break;
                    default: y =0; break;
                    }
                    break;

                case Graph_rabbit_changingTerritoryCriteria:
                    switch (lineSerieNumber) {
                    case 0:  y = (*generation)[i].changingTerritory_huntersValue / (*generation)[i].nbOfAnimals;        break;
                    case 1:  y = (*generation)[i].changingTerritory_grassLevel / (*generation)[i].nbOfAnimals;          break;
                    case 2:  y = (*generation)[i].changingTerritory_flirtValue / (*generation)[i].nbOfAnimals;          break;
                    default: y =0; break;
                    }
                    break;

                case Graph_fox_changingTerritoryCriteriasIfHighLifeLevel:
                    switch (lineSerieNumber) {
                    case 0:  y = (*generation)[i].changingTerritory_rabbitsNumberAgainstFlirtValue / (*generation)[i].nbOfAnimals;        break;
                    case 1:  y = (*generation)[i].changingTerritory_flirtValueAgainstRabbitsNumber / (*generation)[i].nbOfAnimals;          break;
                    default: y =0; break;
                    }
                    break;

                case Graph_fox_changingTerritoryCriteriasIfLowLifeLevel:
                    switch (lineSerieNumber) {
                    case 0:  y = (*generation)[i].changingTerritory_rabbitsNumberAgainstAvoidingFight / (*generation)[i].nbOfAnimals;        break;
                    case 1:  y = (*generation)[i].changingTerritory_avoidingFightAgainstRabbitsNumber / (*generation)[i].nbOfAnimals;          break;
                    default: y =0; break;
                    }
                    break;
                default:
                    break;
                }
            }

            // x and append
            x = (*generation)[i].generation;
            lineSerie->append(x, y);

            // valueMax and valueMin for axis scale
            if(y > valueMax)
                valueMax = y;

            if(y < valueMin)
                valueMin = y;

            log=false;
            if(log)
            {
                qDebug() << "x=" << x << ", y=" << y;
            }
        }
        setXMax((generation->count()-1) * numberOfGenerationInAChartData);

    } else {
        // graph based on years counter

        for(int i = 0 ; i < m_year.count() ; i++)
        {
            switch (m_currentChartNumber) {
            case Graph_year_population:
                switch (lineSerieNumber) {
                case 0:  y = m_year[i].m_nbOfLivingRabbits / m_year[i].m_yearsNumber;        break;
                case 1:  y = m_year[i].m_nbOfLivingFoxes / m_year[i].m_yearsNumber;          break;
                default: y =0; break;
                }
                break;

            case Graph_year_rabbits :
                switch (lineSerieNumber) {
                case 0:  y = m_year[i].m_nbOfRabbitsBirth / m_year[i].m_yearsNumber;                    break;
                case 1:  y = m_year[i].m_nbOfRabbitsUnsuccessfullDate / m_year[i].m_yearsNumber;        break;
                case 2:  y = m_year[i].m_nbOfRabbitsDeath/ m_year[i].m_yearsNumber;                     break;
                case 3:  y = m_year[i].m_nbOfRabbitsDeathDueToHunt/ m_year[i].m_yearsNumber;            break;
                default: y =0; break;
                }
                break;

            case Graph_year_foxes :
                switch (lineSerieNumber) {
                case 0:  y = m_year[i].m_nbOfFoxesBirth / m_year[i].m_yearsNumber;                    break;
                case 1:  y = m_year[i].m_nbOfFoxesUnsuccessfullDate / m_year[i].m_yearsNumber;        break;
                case 2:  y = m_year[i].m_nbOfFoxesDeath/ m_year[i].m_yearsNumber;                     break;
                case 3:  y = m_year[i].m_nbOfFoxesDeathDueToFight/ m_year[i].m_yearsNumber;           break;
                default: y =0; break;
                }
                break;

            default:
                break;
            }
            // x and append
            x = m_year[i].m_year;
            lineSerie->append(x, y);

            // valueMax and valueMin for axis scale
            if(y > valueMax)
                valueMax = y;

            if(y < valueMin)
                valueMin = y;

            log=false;
            if(log)
            {
                qDebug() << "x=" << x << ", y=" << y;
            }
        }
        setXMax((m_year.count()-1) * numberOfYearsInAChartData);
    }

    setValueMax(valueMax);
    setValueMin(valueMin);


}




void ChartDatas::setCurrentChartNumber(const ChartDatas::E_GraphKind &chartNumber)
{
    if(m_currentChartNumber != chartNumber)
    {
        m_currentChartNumber = chartNumber;
        emit currentChartNumberChanged();
    }
}

void ChartDatas::setNumberOfSeries(unsigned int numberOfSeries, bool emitWhatever)
{
    bool log=true;
    if(numberOfSeries != m_numberOfSeries)
    {
        m_numberOfSeries = numberOfSeries;
        emit numberOfSeriesChanged();
    } else if(emitWhatever) {
        emit numberOfSeriesChanged();
    }
    if(log)
        qDebug() << "setNumberOfSeries : " << m_numberOfSeries << ", " << emitWhatever;

}

double ChartDatas::getXMax() const
{
    return xMax;
}

void ChartDatas::setXMax(double value)
{
    if(value != xMax)
    {
        xMax = value;
        emit xMaxChanged();
    }
}

double ChartDatas::getValueMin() const
{
    return m_valueMin;
}

void ChartDatas::setValueMin(double valueMin)
{
    if(valueMin != m_valueMin)
    {
        m_valueMin = valueMin;
        emit valueMinChanged();
    }
}

double ChartDatas::getValueMax() const
{
    return m_valueMax;
}

void ChartDatas::setValueMax(double valueMax)
{
    if(valueMax != m_valueMax)
    {
        m_valueMax = valueMax;
        emit valueMaxChanged();
    }
}

void ChartDatas::setGraphDescription(const QString &graphDescription)
{
    if(m_graphDescription != graphDescription)
    {
        m_graphDescription = graphDescription;
        emit graphDescriptionChanged();
    }
}

void ChartDatas::setGraphTitle(const QString &graphTitle)
{
    if(m_graphTitle != graphTitle)
    {
        m_graphTitle = graphTitle;
        emit graphTitleChanged();
    }
}

void ChartDatas::addAYear(const int yearToAdd)
{
    bool log = false;


    int year_index = qFloor(yearToAdd/numberOfYearsInAChartData) ;

    if(year_index<0)
    {
        qDebug()<< "findTheChartData erreur fatale";
        return;
    }

    if(year_index < m_year.count())
    {
        if(log)
            qDebug() << "findTheChartData existing: " << year_index << ", " << m_year.count();
    }

    while(year_index >= m_year.count())
    {
        ChartDataYear *myChartDataYear = new ChartDataYear;
        myChartDataYear->m_year = m_year.count() * numberOfYearsInAChartData;
        m_year.append(*myChartDataYear);
        if(log)
            qDebug() << "findTheChartData append: " << year_index << ", " << m_year.count();
    }

    m_year[year_index].addAYear();

}

void ChartDatas::addAFox(const Renard &theFoxToadd )
{
    ChartData *myChartData = this->findTheChartData(m_generationCurveFoxes, theFoxToadd);
    myChartData->addAFox(theFoxToadd);
}

void ChartDatas::addARabbit(const Lapin &theRabbitToadd)
{
    ChartData *myChartData = this->findTheChartData(m_generationCurveRabbits, theRabbitToadd);
    myChartData->addARabbit(theRabbitToadd);
}

ChartData *ChartDatas::findTheChartData(QVector <ChartData> &myVector, const Animal &animalToAdd)
{
    bool log = false;

    int generation_index = qFloor(animalToAdd.getGeneration()/numberOfGenerationInAChartData) ;

    if(generation_index<0)
    {
        qDebug()<< "findTheChartData erreur fatale";
        return  nullptr;
    }

    if(generation_index < myVector.count())
    {
        if(log)
            qDebug() << "findTheChartData existing: " << generation_index << ", " << myVector.count();
    }

    while(generation_index >= myVector.count())
    {
        ChartData *myChartData = new ChartData;
        myChartData->generation = myVector.count() * numberOfGenerationInAChartData;
        myVector.append(*myChartData);
        if(log)
            qDebug() << "findTheChartData append: " << generation_index << ", " << myVector.count();
    }

    return &(myVector.data()[generation_index]);
}

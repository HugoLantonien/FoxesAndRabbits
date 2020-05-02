#ifndef ChartDatas_H
#define ChartDatas_H

#include <QObject>
#include <QVector>
#include <QtCharts>
#include "renard.h"
#include "lapin.h"
#include "chartdata.h"
#include "chartdatayear.h"

using namespace QtCharts;



class ChartDatas : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ChartDatas::E_GraphKind currentChartNumber READ getCurrentChartNumber NOTIFY currentChartNumberChanged)
    Q_PROPERTY(ChartDatas::E_GraphAnimal animal READ getAnimal WRITE setAnimal NOTIFY animalChanged)

    Q_PROPERTY(QString graphTitle READ getGraphTitle NOTIFY graphTitleChanged)
    Q_PROPERTY(QString graphDescription READ getGraphDescription NOTIFY graphDescriptionChanged)
    Q_PROPERTY(unsigned int numberOfSeries READ getNumberOfSeries NOTIFY numberOfSeriesChanged)
    Q_PROPERTY(double valueMax READ getValueMax NOTIFY valueMaxChanged)
    Q_PROPERTY(double valueMin READ getValueMin NOTIFY valueMinChanged)
    Q_PROPERTY(double xMax READ getXMax NOTIFY xMaxChanged)

public:

    enum E_GraphKind {
        Graph_lifeHourglassCurve,                               // 4 curves, birth, max, old, mate
        Graph_attackingDefencingSkills,                         // 2 curves, attacking, defencing
        Graph_seducingSkills,                                   // 1 curve
        Graph_lifeLevelAddedPerMealNeededPerYear,               // 2 curves
        Graph_rabbit_numberOfBabyPerPregnancy,                  // 1 curve
        Graph_rabbit_changingTerritoryCriteria,                 // 3 curves
        Graph_fox_changingTerritoryCriteriasIfHighLifeLevel,    // 2 curves
        Graph_fox_changingTerritoryCriteriasIfLowLifeLevel,     // 2 curves
        Graph_year_population,                                  // 2 curves
        Graph_year_rabbits,                                     // 4 curves
        Graph_year_foxes,                                       // 4 curves
        Graph_noMoreCurve
    } ;

    Q_ENUM(E_GraphKind)

    enum E_GraphAnimal {
        Animal_fox,
        Animal_rabbit,
        Animal_noMoreAnimal
    };

    Q_ENUM(E_GraphAnimal)


    static ChartDatas *getInstance(void);

    void addAFox(const Renard &theFoxToadd);
    void addARabbit(const Lapin &theRabbitToadd );
    void addAYear(const int yearToAdd );


    E_GraphKind getCurrentChartNumber() const;

    E_GraphAnimal getAnimal() const;
    void setAnimal(const ChartDatas::E_GraphAnimal &animal);

    QString getGraphTitle() const;
    QString getGraphDescription() const;
    unsigned int getNumberOfSeries() const;

    double getValueMax() const;
    void setValueMax(double valueMax);

    double getValueMin() const;
    void setValueMin(double valueMin);

    double getXMax() const;
    void setXMax(double value);

public slots:
    void prepareGraphics(int graphicCounter);
    void prepareSerie(QLineSeries * lineSerie, unsigned int lineSerieNumber);

signals:
    void currentChartNumberChanged();
    void animalChanged();
    void graphTitleChanged();
    void graphDescriptionChanged();
    void numberOfSeriesChanged();
    void valueMaxChanged();
    void valueMinChanged();
    void xMaxChanged();

private:
    static unsigned int const maxNumberOfSeries = 4;
    static QString const graphDescription [Animal_noMoreAnimal][Graph_noMoreCurve] ;
    static QString const graphTitle[Graph_noMoreCurve];
    static QString const seriesTitle[Graph_noMoreCurve] [maxNumberOfSeries];
    static bool const basedOnGeneration[Graph_noMoreCurve];
    static unsigned int const numberOfSeries[Graph_noMoreCurve];
    static ChartDatas::E_GraphKind const foxCharts[];
    static ChartDatas::E_GraphKind const rabbitCharts[];


    void setCurrentChartNumber(const ChartDatas::E_GraphKind &chartNumber);
    E_GraphKind m_currentChartNumber = Graph_lifeHourglassCurve;
    E_GraphAnimal m_animal = Animal_fox;

    void setGraphTitle(const QString &graphTitle);
    void setGraphDescription(const QString &graphDescription);
    void setNumberOfSeries(unsigned int numberOfSeries, bool emitWhatever=false);
    QString m_graphTitle;
    QString m_graphDescription;
    unsigned int m_numberOfSeries;

    double m_valueMax = 0;
    double m_valueMin = 999999999999999;
    double xMax = 0;


    static const int numberOfGenerationInAChartData = 5;
    static const int numberOfYearsInAChartData = 50;

    static ChartDatas *instance;
    ChartDatas(QObject *parent = nullptr);

    ChartData *findTheChartData(QVector <ChartData> &myVector, const Animal &animalToAdd);

    QVector<ChartData> m_generationCurveFoxes;
    QVector<ChartData> m_generationCurveRabbits;
    QVector<ChartDataYear> m_year;
};

#endif // ChartDatas_H

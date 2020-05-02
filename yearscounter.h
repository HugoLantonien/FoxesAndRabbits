#ifndef YEARSCOUNTER_H
#define YEARSCOUNTER_H

#include <QObject>

class yearsCounter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int nbOfYearToPlay READ getNbOfYearToPlay WRITE setNbOfYearToPlay NOTIFY nbOfYearToPlayChanged)

public:
    static yearsCounter *getInstance();

    Q_INVOKABLE void playYears(int nbYearsToPlay);
    int getDate() const;


    int getNbOfYearToPlay() const;
    void setNbOfYearToPlay(int nbOfYearToPlay);

signals:
    void nbOfYearToPlayChanged();

private:
    yearsCounter(QObject *parent = nullptr);
    int m_date ;
    int m_nbOfYearToPlay = 200;

    static yearsCounter* instance;


};

#endif // YEARSCOUNTER_H

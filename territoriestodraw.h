#pragma once

#ifndef TERRITORIESTODRAW_H
#define TERRITORIESTODRAW_H

#include "territories.h"
#include "lapin.h"
#include "renard.h"
#include <QAbstractTableModel>

#define TABLE_VIEW_ON // to be commented if gridview or listview

class TerritoriesToDraw : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(Territories *territorriesList READ territorriesList WRITE setTerritorriesList NOTIFY territorriesListChanged)
    Q_PROPERTY(Lapin *lapinToBeEdited READ lapinToBeEdited WRITE setLapinToBeEdited NOTIFY lapinToBeEditedChanged)
    Q_PROPERTY(Renard *renardToBeEdited READ renardToBeEdited WRITE setRenardToBeEdited NOTIFY renardToBeEditedChanged)

    Q_PROPERTY(unsigned int nbPixelPerTerritory READ getNbPixelPerTerritory CONSTANT)
    Q_PROPERTY(unsigned int nbTerritoriesDisplayedInFrame READ getNbTerritoriesDisplayedInFrame CONSTANT)

public:

    static unsigned int getNbPixelPerTerritory();
    static unsigned int getNbIconToDrawFoxes();
    static unsigned int getNbIconToDrawRabbits();
    static unsigned int getNbTerritoriesDisplayedInFrame();

    explicit TerritoriesToDraw(QObject *parent = nullptr);

    enum {
        LadyFox1= Qt::UserRole,
        LadyFox2,
        LadyFox3,
        GentlemanFox1,
        GentlemanFox2,
        GentlemanFox3,
        LadyRabbit1,
        LadyRabbit2,
        LadyRabbit3,
        GentlemanRabbit1,
        GentlemanRabbit2,
        GentlemanRabbit3,
        GrassLevelRole,
    };



    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

#ifdef TABLE_VIEW_ON
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
#endif

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
  /* bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;
   Qt::ItemFlags flags(const QModelIndex& index) const override;
 */
    virtual QHash<int, QByteArray> roleNames() const override;


    Q_INVOKABLE void reDraw();


    Territories *territorriesList() const;
    void setTerritorriesList(Territories *territorriesList);


    Lapin *lapinToBeEdited() const;
    void setLapinToBeEdited(Lapin *lapinToBeEdited);
    Q_INVOKABLE Lapin *getLapinInATerritory(int index, bool woman, int numberInTerritory);

    Renard *renardToBeEdited() const;
    void setRenardToBeEdited(Renard *renardToBeEdited);
    Q_INVOKABLE Renard *getRenardInATerritory(int index, bool woman, int numberInTerritory);





signals:
    void territorriesListChanged();
    void lapinToBeEditedChanged();
    void renardToBeEditedChanged();

private:
    Territories *m_territorries;
    Lapin *m_lapinToBeEdited;
    Renard *m_renardToBeEdited;

    static const unsigned int nbPixelPerTerritory = 70;
    static const unsigned int nbTerritoriesDisplayedInFrame = 11;
    static const unsigned int nbIconToDrawFoxes = 6;
    static const unsigned int nbIconToDrawRabbits = 5;

};

#endif // TERRITORIESTODRAW_H

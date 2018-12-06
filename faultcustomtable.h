#ifndef FAULTCUSTOMTABLE_H
#define FAULTCUSTOMTABLE_H

#include <QAbstractTableModel>
#include <QTimer>
#include <QObject>

class FaultCustomTable : public QAbstractTableModel
{
    Q_OBJECT
public:
    FaultCustomTable(QObject * parent);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    // controls the data shown in each cell
    QVariant data(const QModelIndex &index, int role) const;
    //controls the header data
    QVariant headerData(int section, Qt::Orientation orientaion,int role) const;

private:
    QTimer * timer;
    QTimer * faultTimer;

};

#endif // FAULTCUSTOMTABLE_H

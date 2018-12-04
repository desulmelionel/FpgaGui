#include "faultcustomtable.h"
#include <QFont>
#include <QBrush>
#include <QTime>
#include <QTimer>

FaultCustomTable::FaultCustomTable(QObject * parent) : QAbstractTableModel (parent)
{
    timer = new QTimer(this);
    timer->setInterval(1000);

    connect(timer,&QTimer::timeout,[=](){
        QModelIndex topLeft = index(0,3);
        // notify the view of the change the time in the model
        emit dataChanged(topLeft,topLeft);
    });

    timer->start();
}

int FaultCustomTable::rowCount(const QModelIndex &parent) const
{
    return 5;

}

int FaultCustomTable::columnCount(const QModelIndex &parent) const
{
    return 5;

}

QVariant FaultCustomTable::data(const QModelIndex &index, int role) const
{
    /*
        if(role == Qt::DisplayRole)
        {
            QString value = QString("Row %1, Col %2")
                    .arg(index.row() +1)
                    .arg(index.column() +1);

            return value;
        }
        */

        int row = index.row();
        int col = index.column();

        switch(role)
        {
            case Qt::DisplayRole:
                if(row == 0 && col == 0) return QString ("FAULT 1");
                if(row == 1 && col == 0) return QString ("FAULT 2");
                if(row == 2 && col == 0) return QString ("FAULT 3");
                if(row == 3 && col == 0) return QString ("FAULT 4");
                if(row == 4 && col == 0) return QString ("FAULT 5");


                if(row == 0 && col == 3)
                {// returns the current time ( with out changing)
                    return QTime::currentTime().toString();
                }
                if(row == 1 && col == 3)
                {// returns the current time ( with out changing)
                    return QTime::currentTime().toString();
                }
                //if(row == 1 && col == 1) return QString ("Right-->");

                return QString("Row %1, Col %2")
                        .arg(row)
                        .arg(col);

            case Qt::FontRole:
                // makes that cell BOLD
                if(col == 0)
                {
                    QFont font;
                    font.setBold(true);
                    return font;
                }
                break;

            case Qt::BackgroundColorRole:
                if(row == 1 && col == 2)
                 {
                    QBrush background(Qt::yellow);
                    return background;
                 }
                 break;

            case Qt::TextAlignmentRole:
                {
                    if(col == 1)
                {

                    return Qt::AlignLeft;
                }
                break;

                }

        }

        return QVariant();
}

QVariant FaultCustomTable::headerData(int section, Qt::Orientation orientaion, int role) const
{


    // controls the header for each column
    if(role == Qt::DisplayRole)
    {
        if(orientaion == Qt::Horizontal)
        {
            switch(section)
            {
                case 0:

                    return QString("FAULT");
                    //break;

                case 1:
                    return QString("STATUS");
                    //break;

                case 2:
                    return QString("DATE");
                   // break;

                case 3:
                    return QString("TIME");
                    //break;

                case 4:
                    return QString("LAST RESET");
                    //break;

                default:
                    return QString("Default");
                    //break;
            }
        }

    }
    return QVariant();
}

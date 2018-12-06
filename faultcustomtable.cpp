#include "faultcustomtable.h"
#include <QBrush>
#include <QDate>
#include <QFont>
#include <QTime>
#include <QTimer>
#include <QtDebug>

FaultCustomTable::FaultCustomTable(QObject * parent) : QAbstractTableModel (parent)
{
    timer = new QTimer(this);
    timer->setInterval(1000);

    connect(timer,&QTimer::timeout,[=](){
        QModelIndex topLeft = index(1,3);
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
      //index for each cell (row,col)
        int row = index.row();
        int col = index.column();

      //control for setting
        bool faultControl = true;

     //index for each colum
      /*  int indexStatusCol = 1;
        int indexDateCol = 2;
        int indexTimeCol = 3;
        int indexLastResetCol = 4;
      */
        switch(role)
        {
            case Qt::DisplayRole:
                // Display the faults in the first colum with zero for value
                if(row == 0 && col == 0) return QString ("FAULT 1");
                if(row == 1 && col == 0) return QString ("FAULT 2");
                if(row == 2 && col == 0) return QString ("FAULT 3");
                if(row == 3 && col == 0) return QString ("FAULT 4");
                if(row == 4 && col == 0) return QString ("FAULT 5");

                if(row == 1 && col == 3)
                {
                   // returns the time of the trip
                   return QTime::currentTime().toString();
                }
//-------------------------------------------------------------------------------------------------------------------
                //Display the status of each fault
                     // if col == 1 then fault is clear else highlight and light up faultPushButton
                if(faultControl == true)
                {// marks the status of the row as faulted
                    if(row == 0 && col == 1)
                    {
                        return QString ("FAULT");
                    }

                    if(row == 0 && col == 2)
                    {
                        // reports the date of the trip
                        return QDate::currentDate().toString("dd-MM-yyyy");
                    }
                    if(row == 0 && col == 3)
                    {
                       // returns the time of the trip
                       return QTime::currentTime().toString();
                    }
                }
                else
                {
                    if(row == 0 && col == 1)
                    {
                        return QString ("CLEARED");
                    }
                    /* once reset signal is sent this should be executed (no reset signal as of now)
                    if(row == 2 && col == 4)
                    {
                        // reports the date of the trip
                        return QDate::currentDate().toString();
                    }*/
                }
                break;
//-------------------------------------------------------------------------------------------------------------------
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
                if(faultControl == true)
                 {
                    if(row == 0)
                    {
                    QBrush background(Qt::yellow);
                    return background;
                    }
                 }
                else
                {
                    QBrush background(Qt::white);
                    return background;
                }
                 break;

            case Qt::TextAlignmentRole:
                {
                    if(col == 1)
                {

                    return Qt::AlignCenter;
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

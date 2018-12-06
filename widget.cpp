#include "widget.h"
#include "ui_widget.h"
#include "faultcustomtable.h"
#include <QDateTime>
#include <QInputDialog>
#include <QPushButton>
#include <QPalette>
#include <QtDebug>
#include <QTime>
#include <QTimer>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    // Editing the colors of the PushButtons
    ui->offButton->setStyleSheet("background-color: green");
    ui->stdbButton->setStyleSheet("background-color: yellow");
    ui->onButton->setStyleSheet("background-color: red");

    // Have remoteRadioButton selected at start
    ui->remoteRadioButton->setChecked(true);
    ui->remoteRadioButton->click();

    //Fault table Display
    ui->tableView->verticalHeader()->hide();
    FaultCustomTable * model = new FaultCustomTable(this);
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();// expends the colums to fit the size the data thats in the cell
   // ui->tableView->resizeColumnToContents(2);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //extends the tableView when user goes full screen

    //display date and time
    timer = new QTimer(this);
    timer->setInterval(1000);
    QString timeString = QTime::currentTime().toString();
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(upDateTime()));
    timer->start(1000);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::upDateTime()
{//Clock management for main widget
     ui->dateTimeLabel->setText(QDateTime::currentDateTime().toString("MM-dd-yyyy  hh:mm:ss"));
}

void Widget::on_localRadioButton_clicked()
{
    // when local buttons are enabled
    ui->offButton->setEnabled(true);
    ui->stdbButton->setEnabled(true);
    ui->onButton->setEnabled(true);
    ui->iRefButton->setEnabled(true);


}

void Widget::on_remoteRadioButton_clicked()
{
    // when remote local buttons are disabled
    ui->offButton->setEnabled(false);
    ui->stdbButton->setEnabled(false);
    ui->onButton->setEnabled(false);
    ui->iRefButton->setEnabled(false);

}

void Widget::on_offButton_clicked()
{   // Change the statusLabel
    ui->statusLabel->setText("OFF");
}

void Widget::on_stdbButton_clicked()
{    // Change the statusLabel
     ui->statusLabel->setText("STANDBY");
}

void Widget::on_onButton_clicked()
{    // Change the statusLabel
     ui->statusLabel->setText("ON");
}

void Widget::on_faultButton_clicked()
{

}

void Widget::on_iRefButton_clicked()
{
    //Creates a dialog and prompts the user to enter a desired refference.
    bool OK;
    double dialogRefInput = QInputDialog::getDouble(this,tr("QInputDialog::getDouble()"),
                                            tr("Amount:"), 0, -100, 100,2, &OK);
    //pass the desired value from the dialog to the global variable named lcdRefInput
    lcdRefInput = dialogRefInput;
    //lcd display refInput from dialog
    ui->irefLcdNumber->display(lcdRefInput);
}

double Widget::getLcdRefInput() const
{
    //Makes the reference picked global
    return lcdRefInput;
}



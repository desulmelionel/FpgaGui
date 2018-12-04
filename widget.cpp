#include "widget.h"
#include "ui_widget.h"
#include "faultcustomtable.h"
#include <QPushButton>
#include <QPalette>
#include <QDateTime>
#include <QTimer>
#include <QTime>

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

    //Fault table Display
    ui->tableView->verticalHeader()->hide();
    FaultCustomTable * model = new FaultCustomTable(this);
    ui->tableView->setModel(model);

    //display date and time
    timer = new QTimer(this);
    timer->setInterval(1000);
    QString timeString = QTime::currentTime().toString();
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(upDateTime()));
    timer->start(1000);}

Widget::~Widget()
{
    delete ui;
}

void Widget::upDateTime()
{
     ui->dateTimeLabel->setText(QDateTime::currentDateTime().toString("MM-dd-yyyy  hh:mm:ss"));
}



void Widget::on_localRadioButton_clicked()
{
    // when local buttons are enabled
    ui->offButton->setEnabled(true);
    ui->stdbButton->setEnabled(true);
    ui->onButton->setEnabled(true);

}

void Widget::on_remoteRadioButton_clicked()
{
    // when remote local buttons are disabled
    ui->offButton->setEnabled(false);
    ui->stdbButton->setEnabled(false);
    ui->onButton->setEnabled(false);
}

void Widget::on_offButton_clicked()
{
    ui->statusLabel->setText("OFF");
}

void Widget::on_stdbButton_clicked()
{
     ui->statusLabel->setText("STANDBY");
}

void Widget::on_onButton_clicked()
{
     ui->statusLabel->setText("ON");
}

void Widget::on_faultButton_clicked()
{

}




#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_offButton_clicked();

    void on_stdbButton_clicked();

    void on_onButton_clicked();

    void on_localRadioButton_clicked();

    void on_remoteRadioButton_clicked();

    void on_faultButton_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H

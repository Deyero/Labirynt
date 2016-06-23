#ifndef RANDOMMAPDIALOG_H
#define RANDOMMAPDIALOG_H
#include "ui_randommapdialog.h"
#include "generator.h"
/**
*Opisuje okienko losowania nowej mapy.
*/
class RandomMapDialog : public QDialog
{
    Q_OBJECT

    Ui::RandomMapDialog ui;
    void clearParameters();
    public:
    RandomMapDialog(QWidget *parent = 0);
    QString getWidth(){return ui.lineEditWidth->text();}
    QString getHeight(){return ui.lineEditHeight->text();}
    QString getParam1(){return ui.lineEditParam1->text();}
    QString getParam2(){return ui.lineEditParam2->text();}
    QString getParam3();
    Generator::Method getMethod();
    private slots:
    void on_radioButton_2_toggled(bool checked);
    void on_radioButton_toggled(bool checked);
};

#endif // RANDOMMAPDIALOG_H

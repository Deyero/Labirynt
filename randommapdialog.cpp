#include "randommapdialog.h"
#include <QMessageBox>
RandomMapDialog::RandomMapDialog(QWidget *parent):
    QDialog(parent)
{
    ui.setupUi(this);
    ui.labelParam2->hide();
    ui.lineEditParam2->hide();
}

Generator::Method RandomMapDialog::getMethod()
{
    if(ui.radioButton->isChecked())
        return Generator::PLAIN;
    if(ui.radioButton_2->isChecked())
        return Generator::WALKER;

    return Generator::PLAIN;
}

void RandomMapDialog::clearParameters()
{
    ui.labelParam1->hide();
    ui.labelParam2->hide();
    ui.lineEditParam1->hide();
    ui.lineEditParam2->hide();
}


void RandomMapDialog::on_radioButton_2_toggled(bool checked)
{
    if(!checked)
        return;
    clearParameters();
    ui.labelParam1->setText("Liczba kroków");
    ui.labelParam1->show();
    ui.lineEditParam1->setText("100");
    ui.lineEditParam1->show();
}

void RandomMapDialog::on_radioButton_toggled(bool checked)
{
    if(!checked)
        return;
    clearParameters();
    ui.labelParam1->setText("P('C')");
    ui.labelParam1->show();
    ui.lineEditParam1->setText("0.5");
    ui.lineEditParam1->show();

}

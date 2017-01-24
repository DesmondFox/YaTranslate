#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    ui->labelBuild->setText("Build time: "+QString(__DATE__)+" "+QString(__TIME__));
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

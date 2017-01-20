#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    trans   = new Translator(QString("trnsl.1.1.20170119T172651Z.6515d44d0b7d462b.c2fef498738e6da7a95efd083b1386b718e67e43"));
    trans->getLangList();
    ui->cbLang1->insertItems(0, trans->langList());
    ui->cbLang2->insertItems(0, trans->langList());
    ui->cbLang2->setCurrentIndex(1);
    connect(ui->plainLang1, SIGNAL(textChanged()), SLOT(slotTranslate()));
    connect(this, SIGNAL(translateText(QString,QString,QString)), trans, SLOT(getText(QString,QString,QString)));
    connect(trans, SIGNAL(translate(QString,QString)), SLOT(getTranslate(QString,QString)));
}

MainWindow::~MainWindow()
{
    delete trans;
    delete ui;
}

void MainWindow::slotTranslate()
{
    if (!ui->plainLang1->toPlainText().isEmpty())
    {
        if (ui->checkAutoTranslate->isChecked())
        {
            emit translateText(ui->plainLang1->toPlainText(),
                               ui->cbLang1->currentText(),
                               ui->cbLang2->currentText());
        }
    }
}

void MainWindow::getTranslate(QString text, QString lang)
{
    ui->plainLang2->setPlainText(text);
    ui->cbLang1->setCurrentText(lang);
}

void MainWindow::on_pushSwap_clicked()
{

}

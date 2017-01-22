#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    trans   = new Translator(QString("trnsl.1.1.20170119T172651Z.6515d44d0b7d462b.c2fef498738e6da7a95efd083b1386b718e67e43"));
    trans->getLangList();
    ui->cbLang1->addItem("Определить язык");        // TODO:
    ui->cbLang1->insertItems(1, trans->langList());
    ui->cbLang2->insertItems(0, trans->langList());
    ui->cbLang2->setCurrentIndex(2);
    ui->checkAutoTranslate->setChecked(true);
    ui->pushSwap->setEnabled(false);

    timerInterval = 500;
//    connect(ui->plainLang1, SIGNAL(textChanged()), SLOT(slotTranslate()));
    connect(this, SIGNAL(translateText(QString,QString,QString)), trans, SLOT(getText(QString,QString,QString)));
    connect(trans, SIGNAL(translate(QString,QString)), SLOT(getTranslate(QString,QString)));

    // Инициализация таймера
    timer   = new QTimer(this);
    timer->start(timerInterval);
    connect(timer, SIGNAL(timeout()), SLOT(slotTimerTick()));
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
            translate();
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
    int tmp = ui->cbLang2->currentIndex();
    ui->cbLang2->setCurrentIndex(ui->cbLang1->currentIndex()-1);
    ui->cbLang1->setCurrentIndex(tmp+1);
    translate();
}

void MainWindow::slotTimerTick()
{
    if (dumpText != ui->plainLang1->toPlainText())
    {
        if (ui->cbLang1->currentIndex() != 1)
        {
            translate();
        }
    }
}

void MainWindow::on_checkAutoTranslate_clicked()
{
    if (ui->checkAutoTranslate->isChecked())
    {
        timer->start(1000);
        timer->start(timerInterval);
        qDebug() << "Note:\t" << "Timer started(" << timer->interval() << ")";
    }
    else
    {
        timer->stop();
        qDebug() << "Note:\t" << "Timer stopped";
    }
}

void MainWindow::on_pushTranslate_clicked()
{
    if (ui->cbLang1->currentIndex() != 0)
    {
        translate();
    }
}

void MainWindow::translate()
{
    dumpText = ui->plainLang1->toPlainText();
    emit translateText(ui->plainLang1->toPlainText(),
                       ui->cbLang1->currentText(),
                       ui->cbLang2->currentText());

}



void MainWindow::on_cbLang1_currentIndexChanged(int index)
{
    if (ui->cbLang1->currentIndex() != 0)
    {
        ui->pushSwap->setEnabled(true);
        translate();
    }
    else
        ui->pushSwap->setEnabled(false);
}

void MainWindow::on_cbLang2_currentIndexChanged(int index)
{

    translate();
}

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
}

MainWindow::~MainWindow()
{
    delete trans;
    delete ui;
}

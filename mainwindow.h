#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDebug>
#include "translator.h"
#include "labelpossiblelang.h"
#include "aboutdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Translator      *trans;
//    LabelPossibleLang *lblPoss;

public slots:
    void slotTranslate();
    void getTranslate(QString text, QString lang);

private slots:
    void on_pushSwap_clicked();
    void slotTimerTick();                       // Тайминг запросов до яндекса
    void slotPossibleLang(QString langName);    // Показ "Возможный язык: название языка"
    void slotChangeLangFrom();                  // Изменения языка перевода

    void on_checkAutoTranslate_clicked();
    void on_pushTranslate_clicked();
    void on_cbLang1_currentIndexChanged(int index);
    void on_cbLang2_currentIndexChanged(int index);
    void on_possibleAction_triggered();

private:
    Ui::MainWindow  *ui;
    QString         dumpText;
    QTimer          *timer;
    void            translate();
    int             timerInterval;
    QString         tmpPossLang;    // Для временного хранения возможного языка (слишком часто употребляю слово "Возможный")

signals:
    void translateText(QString text, QString langFrom, QString langTo);

};

#endif // MAINWINDOW_H

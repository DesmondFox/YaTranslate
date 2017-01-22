#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDebug>
#include "translator.h"

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

public slots:
    void slotTranslate();
    void getTranslate(QString text, QString lang);

private slots:
    void on_pushSwap_clicked();
    void slotTimerTick();                       // Тайминг запросов до яндекса
    void slotPossibleLang(QString langName);    // Показ "Возможный язык: название языка"

    void on_checkAutoTranslate_clicked();
    void on_pushTranslate_clicked();
    void on_cbLang1_currentIndexChanged(int index);
    void on_cbLang2_currentIndexChanged(int index);
    void on_possibleAction_triggered();

    void on_labelPossibleLang_linkActivated(const QString &link);

private:
    Ui::MainWindow  *ui;
    QString         dumpText;
    QTimer          *timer;
    void            translate();
    int             timerInterval;
signals:
    void translateText(QString text, QString langFrom, QString langTo);

};

#endif // MAINWINDOW_H

#include <QApplication>
#include "translator.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    Translator trans("trnsl.1.1.20170119T172651Z.6515d44d0b7d462b.c2fef498738e6da7a95efd083b1386b718e67e43");
//    trans.getLangList();
//    trans.langList();
    MainWindow window;
    window.show();

//    QApplication::exit(0);
    return a.exec();
}

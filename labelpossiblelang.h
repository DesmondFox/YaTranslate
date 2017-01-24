#ifndef LABELPOSSIBLELANG_H
#define LABELPOSSIBLELANG_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QDebug>
// Виджет, наследуемый от QLabel для того, чтобы
// Можно было кликать на строку "Возможный язык"

class LabelPossibleLang : public QLabel
{
    Q_OBJECT
public:
    explicit LabelPossibleLang(const QString &text = "", QWidget *parent = 0);
    explicit LabelPossibleLang(QWidget *parent = 0);
    ~LabelPossibleLang();

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent  *event);
};

#endif // LABELPOSSIBLELANG_H

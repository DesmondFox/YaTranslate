#include "labelpossiblelang.h"

LabelPossibleLang::LabelPossibleLang(const QString &text, QWidget *parent)
    : QLabel(parent)
{
    this->setText(text);

}

LabelPossibleLang::LabelPossibleLang(QWidget *parent)
    : QLabel(parent)
{
    this->setText("");
}

LabelPossibleLang::~LabelPossibleLang()
{

}

void LabelPossibleLang::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        emit clicked();
    qDebug() << "clicked";
}

void LabelPossibleLang::mouseMoveEvent(QMouseEvent *event)
{
    this->setCursor(QCursor(Qt::PointingHandCursor));
}

//
//
// animator.cpp
//
// LE Viet Man
// 05/07/2011
//
//

#include "animator.h"

#define TIMER      (2000)

Animator::Animator(QObject *parent)
{
    this->glSOMScene = (GLSOMScene*)parent;
}

Animator::~Animator()
{
    glSOMScene = 0;
}

void Animator::animate(qreal dx, qreal dy)
{
    int msec = 0;

    QPropertyAnimation *animDXY;

    animDXY = new QPropertyAnimation(glSOMScene, "dXY");

    animDXY->setDuration(TIMER);
    animDXY->setStartValue(glSOMScene->dXY());
    animDXY->setEndValue(glSOMScene->dXY() + QPointF(dx, dy));
    animDXY->setEasingCurve(QEasingCurve::OutBack);

    msec += TIMER / 10;
    pushAnimation(msec, animDXY);
}

void Animator::finishAnimation()
{
    emit finished();
}

void Animator::pushAnimation(int msec, QAbstractAnimation *animation)
{
    QTimer::singleShot(msec, animation, SLOT(start()));
    connect(animation, SIGNAL(finished()), this, SLOT(finishAnimation()));
    connect(animation, SIGNAL(finished()), animation, SLOT(deleteLater()));
}

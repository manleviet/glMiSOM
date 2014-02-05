//
//
// animator.h
//
// LE Viet Man
// 05/07/2011
//
//

#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <QObject>
#include <QAbstractAnimation>
#include <QPropertyAnimation>
#include <QTimer>
#include "Scene/glsomscene.h"

class GLSOMScene;

class Animator : public QObject
{
    Q_OBJECT

public:
    explicit Animator(QObject *parent = 0);
    ~Animator();

    void animate(qreal dx, qreal dy);

signals:
    void finished();

private slots:
    void finishAnimation();

private:
    GLSOMScene *glSOMScene;

    void pushAnimation(int msec, QAbstractAnimation *animation);
};

#endif // ANIMATOR_H

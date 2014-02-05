//
//
// cellsom.h
//
// Une classe demonstrate une casse dans la carte de Kohonen
//
// LE Viet Man
// 20/07/2011
//
//

#ifndef CELLSOM_H
#define CELLSOM_H

#include <QList>
#include <QColor>
#include <QGLWidget>
#include "Core/image.h"
#include "SOM/winnerinfo.h"

class CellSOM
{
public:
    CellSOM();
    ~CellSOM();

    bool isEmpty() { return imgs.isEmpty(); }

    void addImage(Image *img, double diff, QColor color = Qt::white);
    Image* getImage();
    double getDiff();
    QList<Image*> getAllImage() const;
    QList<double> getAllDiff() const;

    int getQuantityOfImages() const;

    void setColor(QColor c);
    QColor getColor() { return color; }

    void removeAllExceptWinner(WinnerInfo *winner);
    void removeImage(Image *img);

    bool contains(Image *img);

    void addTexture(GLuint texture, QRectF rect);
    GLuint getTexture(int index);
    QRectF getRectF(int index);

    QString getClass();
    bool containsImageOfClass(QString classname);

private:
    QList<Image*> imgs;
    QList<double> diffs;

    // pour visualiser dans OpenGL
    QList<GLuint> textures;
    QList<QRectF> rects;

    // pour classifier
    QColor color;
};

#endif // CELLSOM_H

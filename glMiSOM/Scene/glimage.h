//
//
// glimage.h
//
// LE Viet Man
// 17/08/2011
//
//

#ifndef GLIMAGE_H
#define GLIMAGE_H

#include <QtOpenGL>
#include <QPoint>
#include "Core/cellsom.h"
#include "util.h"

const qreal SIZE_OF_IMAGE = 100;
const qreal SIZE_BETWEEN_IMAGES = 12;
const qreal SIZE_BORDER = 3;
const qreal SIZE_SHADOW = 3;

const qreal SIZE_OF_ID = 30;

class GLImage
{
public:
    GLImage(int index, QGLWidget *widget, QPointF pos, CellSOM *cell);
    ~GLImage();

    void draw();
    void loadImage();
    CellSOM *getCell() { return cell; }

    void setSelected(bool selected);
    void setBackgroundColor(QColor color);

    void removeImage(Image *img);

private:
    int id;
    QGLWidget *parent;
    CellSOM *cell;

    QList<GLuint> idTextures;
    QList<QRectF> idRects;

    bool selected;
    bool drawID;

    QColor color;
    QPointF origine;

    void loadTextureImage(Image *img, GLuint &texture, QRectF &rect);

    QString createImageIdentify(int id);
    void drawCircle(float radius);
    void loadTextureId();
};

#endif // GLIMAGE_H

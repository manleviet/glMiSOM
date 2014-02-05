//
//
// glsomscene.h
//
// LE Viet Man
// 17/08/2011
//
//

#ifndef GLSOMSCENE_H
#define GLSOMSCENE_H

#include <QGLWidget>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QList>
#include <QPoint>
#include "mainwindow.h"
#include "Scene/glimage.h"
#include "Scene/animator.h"
#include "Core/gridsom.h"
#include "Core/cellsom.h"
#include "SOM/mapsom.h"

class Animator;
class MainWindow;

class GLSOMScene : public QGLWidget
{
    Q_OBJECT
    Q_PROPERTY(QPointF dXY READ dXY WRITE setDXY)

public:
    GLSOMScene(GridSOM *grid, MapSOM *map, QWidget *parent = 0);
    ~GLSOMScene();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

    void viewOriginPosition();
    bool isAnimatable() { return animatable; }
    void setAnimatable(bool anim);

    void setDXY(QPointF dXY);
    QPointF dXY() const;

    bool isChangedPosition() { return changedPosition; }

    void saveGeometryBeforeFullscreen();

    void search(QPoint point);

    void removeImageAt(Image *img);

signals:
    void changed(bool);
    void changePosition(bool);
    void viewMetadata(QList<Image*> imgs, QList<double> diffs);
    void viewImage(QList<Image*> img, QList<double> diffs);
    void deleteImage(Image *img);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);

private slots:
    void keyPress(GLSOMScene *scene, QKeyEvent *event);
    void finishAnimation();
    void viewMetadata();
    void viewImage();
    void chooseColor();
    void classify();
    void deleteImage();
    void showClass();
    void resetColorBackground();

private:
    MainWindow *mainWindow;
    MapSOM *som;
    GridSOM *grid;
    QPoint lastPos;

    QList<GLImage*> imageList;

    Animator *animator;

    int xdim, ydim;
    qreal xdimOfSOM, ydimOfSOM;

    // utilise par move et zoom
    qreal xRot;
    qreal yRot;
    GLfloat distance;

    bool changedPosition;
    bool animatable;

    // utilise par click event
    int indexViewMetadata;

    // menu popup
    QAction *viewMDAction;
    QAction *viewImgAction;
    QAction *choseColorAction;
    QAction *classifyAction;
    QAction *deleteAction;
    QAction *classAction;
    QMenu *menu;

    // menu 2
    QAction *resetBackgroundAction;
    QMenu *menu2;

    QRect oldGeo;

    void createMenu();

    void createObjects();
    QPointF calculPositionOfCell(int x, int y);
    int imageAtPosition(const QPointF &pos);

    void setBackgroundColor(QPoint point, QColor color);
};

#endif // GLSOMSCENE_H

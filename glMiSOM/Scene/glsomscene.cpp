//
//
// glsomscene.h
//
// LE Viet Man
// 17/08/2011
//
//

#include "glsomscene.h"

//
// Constructeur
//
GLSOMScene::GLSOMScene(GridSOM *grid, MapSOM *map, QWidget *parent)
    : QGLWidget(parent)
{
    mainWindow = (MainWindow*)parent;
    connect(mainWindow, SIGNAL(keyPress(GLSOMScene*,QKeyEvent*)), this, SLOT(keyPress(GLSOMScene*,QKeyEvent*)));

    lastPos = QPoint(0, 0);

    distance = -500.0f;
    xRot = yRot = 0;

    this->grid = grid;
    this->som = map;

    animatable = false;
    changedPosition = false;

    indexViewMetadata = -1;

    createMenu();
}

GLSOMScene::~GLSOMScene()
{
    mainWindow = 0;
    grid = 0;
    som = 0;
    while (!imageList.isEmpty())
    {
         delete imageList.takeFirst();
    }
    delete animator;
    delete choseColorAction;
    delete classifyAction;
    delete deleteAction;
    delete classAction;
    delete viewMDAction;
    delete viewImgAction;
    delete menu;

    delete resetBackgroundAction;
    delete menu2;
}

QSize GLSOMScene::minimumSizeHint() const
{
    return QSize(100, 100);
}

QSize GLSOMScene::sizeHint() const
{
    return QSize(300, 300);
}

void GLSOMScene::viewOriginPosition()
{
    distance = -500.0f;
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, distance);
    updateGL();
    xRot = yRot = 0;
    updateGL();
    changedPosition = false;
}

void GLSOMScene::setAnimatable(bool anim)
{
    animatable = anim;
}

void GLSOMScene::setDXY(QPointF dXY)
{
    xRot = dXY.x();
    yRot = dXY.y();
    updateGL();
}

QPointF GLSOMScene::dXY() const
{
    return QPointF(xRot, yRot);
}

void GLSOMScene::saveGeometryBeforeFullscreen()
{
    oldGeo = geometry();
}

void GLSOMScene::search(QPoint point)
{
    int index = point.x() * ydim + point.y();
    glMatrixMode(GL_MODELVIEW);
    for (int i = 0; i < imageList.size(); i++)
    {
        if (i == index)
            imageList[i]->setSelected(true);
        else
            imageList[i]->setSelected(false);
    }
    updateGL();

    qreal dx, dy;

    // calculer le centre de l'image
    QPointF cenImg;
    cenImg = calculPositionOfCell(point.x(), point.y());
    cenImg += QPointF(SIZE_OF_IMAGE / 2, (-1) * SIZE_OF_IMAGE / 2);

    dx = cenImg.x() - xRot;
    dy = (-1) * cenImg.y() - yRot;

    setEnabled(false);
    animator->animate(dx, dy);
}

void GLSOMScene::removeImageAt(Image *img)
{
    CellSOM *cell;
    foreach (GLImage *glimage, imageList)
    {
        cell = glimage->getCell();

        if (cell->contains(img))
            glimage->removeImage(img);
    }

    update();
}

// PROTECTED

void GLSOMScene::initializeGL()
{
    createObjects();

    // Make sure depth testing and lighting are disabled for 2D rendering until
    // we are finished rendering in 2D
    glPushAttrib( GL_DEPTH_BUFFER_BIT | GL_LIGHTING_BIT );
    glDisable( GL_DEPTH_TEST );
    glDisable( GL_LIGHTING );
    glDisable( GL_DITHER );
    glDisable( GL_BLEND );

    // Enable the texture rectangle extension
    glEnable(GL_TEXTURE_2D);

    glClearColor (1.0, 1.0, 1.0, 0.6);
}

void GLSOMScene::resizeGL(int width, int height)
{
    double side = qMin(width, height);

    glViewport(0, 0, width, height);
    // Save a copy of the projection matrix so that we can restore it
    // when it's time to do 3D rendering again.
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glFrustum(-width/side, width/side, -height/side, height/side, 1.0, 2000.0);
    glMatrixMode( GL_MODELVIEW );

    glLoadIdentity();
    glTranslatef(0.0, 0.0, distance);
}

void GLSOMScene::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
        glTranslatef(-xRot, yRot, 0.0);
        for (int i = 0; i < imageList.size(); i++)
        {
            imageList[i]->draw();
        }
    glPopMatrix();
    glFlush();

    swapBuffers();
}

void GLSOMScene::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        setCursor(Qt::ClosedHandCursor);
        lastPos = event->pos();

        // selected
        int idSelected = imageAtPosition(event->posF());
        glMatrixMode(GL_MODELVIEW);
        for (int i = 0; i < imageList.size(); i++)
        {
            if (i == idSelected)
                imageList[i]->setSelected(true);
            else
                imageList[i]->setSelected(false);
        }
        updateGL();

        if (animatable)
        {
            qreal dx, dy;

            // calculer le centre de l'image
            QPointF cenImg;
            int x = idSelected / ydim;
            int y = idSelected % ydim;
            cenImg = calculPositionOfCell(x, y);
            cenImg += QPointF(SIZE_OF_IMAGE / 2, (-1) * SIZE_OF_IMAGE / 2);

            dx = cenImg.x() - xRot;
            dy = (-1) * cenImg.y() - yRot;

            setEnabled(false);
            animator->animate(dx, dy);
        }
    }
}

void GLSOMScene::mouseMoveEvent(QMouseEvent *event)
{
    if (animatable) return;

    if (event->buttons() & Qt::LeftButton) {
        xRot += lastPos.x() - event->x();
        yRot += lastPos.y() - event->y();
        lastPos = event->pos();
        updateGL();

        changedPosition = true;
        emit changePosition(changedPosition);
    }
}

void GLSOMScene::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        setCursor(Qt::ArrowCursor);
    }
}

void GLSOMScene::wheelEvent(QWheelEvent *event)
{
    distance -= event->delta() / 10.0f;
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, distance);
    updateGL();

    changedPosition = true;
    emit changePosition(changedPosition);
}

void GLSOMScene::keyPressEvent(QKeyEvent *event)
{
    if (this->parent() == 0 && event->key() == Qt::Key_Escape) {
        mainWindow->setParent(0);
        mainWindow->show();
        mainWindow->addWindowToWorkspace(this);
        setGeometry(oldGeo);
        show();
    }

    switch (event->key())
    {
        case Qt::Key_Left:
            xRot += 4;
            updateGL();
            changedPosition = true;
            emit changePosition(changedPosition);
            break;
        case Qt::Key_Right:
            xRot -= 4;
            updateGL();
            changedPosition = true;
            emit changePosition(changedPosition);
            break;
        case Qt::Key_Up:
            yRot += 4;
            updateGL();
            changedPosition = true;
            emit changePosition(changedPosition);
            break;
        case Qt::Key_Down:
            yRot -= 4;
            updateGL();
            changedPosition = true;
            emit changePosition(changedPosition);
            break;
    }
}

void GLSOMScene::contextMenuEvent(QContextMenuEvent *event)
{
    int idSelected = imageAtPosition(event->pos());
    glMatrixMode(GL_MODELVIEW);

    if (idSelected != -1)
    {
        indexViewMetadata = idSelected;

        menu->exec(event->globalPos());
    }
    else
    {
        menu2->exec(event->globalPos());
    }
}

// PRIVATE SLOTS

void GLSOMScene::keyPress(GLSOMScene *scene, QKeyEvent *event)
{
    if (this == scene)
        keyPressEvent(event);
}

void GLSOMScene::finishAnimation()
{
    setEnabled(true);
}

void GLSOMScene::viewMetadata()
{
    if (indexViewMetadata == -1) return;

    CellSOM *cell = imageList[indexViewMetadata]->getCell();

    emit viewMetadata(cell->getAllImage(), cell->getAllDiff());

    cell = 0;
}

void GLSOMScene::viewImage()
{
    if (indexViewMetadata == -1) return;

    CellSOM *cell = imageList[indexViewMetadata]->getCell();

    emit viewImage(cell->getAllImage(), cell->getAllDiff());

    cell = 0;
}

void GLSOMScene::chooseColor()
{
    if (indexViewMetadata == -1) return;

    QColor color;
        color = QColorDialog::getColor(Qt::green, this, "Select Color", QColorDialog::DontUseNativeDialog);

    if (color.isValid()) {
        imageList[indexViewMetadata]->setBackgroundColor(color);

        emit changed(true);
    }
}

void GLSOMScene::classify()
{
    if (indexViewMetadata == -1) return;

    QColor color;
    color = QColorDialog::getColor(Qt::green, this, "Select Color", QColorDialog::DontUseNativeDialog);

    if (color.isValid()) {
        double aqe = grid->getAQE();

        QPoint point = QPoint(indexViewMetadata / ydim, indexViewMetadata % ydim);
        QList<QPoint> neighbours, neigh, last;

        neighbours << point;

        // tinh toan de loan mau ra
        while (!neighbours.isEmpty())
        {
            point = neighbours.takeFirst();
            last << point;
            setBackgroundColor(point, color);

            neigh = som->classify(grid, point, aqe);

            foreach (QPoint p, neigh)
            {
                if ((!last.contains(p)) && (!neighbours.contains(p)))
                    neighbours << p;
            }
        }
        emit changed(true);
    }
}

void GLSOMScene::deleteImage()
{
    if (indexViewMetadata == -1) return;

    Image *img = imageList[indexViewMetadata]->getCell()->getImage();

    emit deleteImage(img);
}

void GLSOMScene::showClass()
{
    if (indexViewMetadata == -1) return;

    QColor color;
    color = QColorDialog::getColor(Qt::green, this, "Select Color for this class", QColorDialog::DontUseNativeDialog);

    if (color.isValid()) {
        QPoint pos = QPoint(indexViewMetadata / ydim, indexViewMetadata % ydim);

        QList<QPoint> cells = grid->getImagesSameClass(pos);

        foreach (QPoint pos, cells)
        {
            setBackgroundColor(pos, color);
        }

        emit changed(true);
    }
}

void GLSOMScene::resetColorBackground()
{
    foreach (GLImage *img, imageList)
    {
        img->setBackgroundColor(Qt::white);
    }
    updateGL();
    emit changed(true);
}

// PRIVATE

//
// Creer le menu popup
//
void GLSOMScene::createMenu()
{
    viewMDAction = new QAction(QObject::tr("View metadata"), this);
    viewMDAction->setStatusTip(QObject::tr("Show metadata of image"));
    connect(viewMDAction, SIGNAL(triggered()), this, SLOT(viewMetadata()));

    viewImgAction = new QAction(QObject::tr("View image"), this);
    viewImgAction->setStatusTip(QObject::tr("Show image"));
    connect(viewImgAction, SIGNAL(triggered()), this, SLOT(viewImage()));

    choseColorAction = new QAction(QObject::tr("Choose a color..."), this);
    choseColorAction->setStatusTip(QObject::tr("Choose a color for background color of image"));
    connect(choseColorAction, SIGNAL(triggered()), this, SLOT(chooseColor()));

    classifyAction = new QAction(QObject::tr("Classify..."), this);
    classifyAction->setStatusTip(QObject::tr("Choose a color for classification"));
    connect(classifyAction, SIGNAL(triggered()), this, SLOT(classify()));

    deleteAction = new QAction(QObject::tr("Delete"), this);
    deleteAction->setStatusTip(QObject::tr("Delete this image"));
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(deleteImage()));

    classAction = new QAction(QObject::tr("Show same class..."), this);
    connect(classAction, SIGNAL(triggered()), this, SLOT(showClass()));

    menu = new QMenu(this);
    menu->addAction(viewImgAction);
    menu->addAction(viewMDAction);
    menu->addAction(choseColorAction);
    menu->addAction(classifyAction);
    menu->addAction(deleteAction);
    menu->addAction(classAction);

    resetBackgroundAction = new QAction(QObject::tr("Reset Color Background"), this);
    connect(resetBackgroundAction, SIGNAL(triggered()), this, SLOT(resetColorBackground()));

    menu2 = new QMenu(this);
    menu2->addAction(resetBackgroundAction);
}

//
// Creer les objects pour OpenGL
//
void GLSOMScene::createObjects()
{
    // calculer la taille de la carte de Kohonen
    xdim = grid->getXDim();
    ydim = grid->getYDim();

    xdimOfSOM = (xdim * (SIZE_OF_IMAGE)) + ((xdim - 1) * SIZE_BETWEEN_IMAGES);
    ydimOfSOM = (ydim * (SIZE_OF_IMAGE)) + ((ydim - 1) * SIZE_BETWEEN_IMAGES);

    QPointF pos;
    GLImage *glImage;
    CellSOM *cell;
    int index;
    for (int i = 0; i < xdim; i++)
    {
        for (int j = 0; j < ydim; j++)
        {
            cell = grid->getCell(i, j);

            index = i * ydim + j;

            pos = calculPositionOfCell(i, j);

            glImage = new GLImage(index, this, pos, cell);
            glImage->loadImage();

            imageList << glImage;
        }
    }
    cell = 0;
    glImage = 0;

    // initier animator
    animator = new Animator(this);
    connect(animator, SIGNAL(finished()), this, SLOT(finishAnimation()));
}

QPointF GLSOMScene::calculPositionOfCell(int x, int y)
{
    qreal xpos, ypos;
    xpos = (y * (SIZE_OF_IMAGE + SIZE_BETWEEN_IMAGES)) - (xdimOfSOM / 2);
    ypos = ((-1) * x * (SIZE_OF_IMAGE + SIZE_BETWEEN_IMAGES)) + (ydimOfSOM / 2);

    return QPointF(xpos, ypos);
}

int GLSOMScene::imageAtPosition(const QPointF &pos)
{
    const int MaxSize = 512;
    int w = this->width();
    int h = this->height();
    double side = qMin(w, h);
    GLuint buffer[MaxSize];
    GLint viewport[4];

    glGetIntegerv(GL_VIEWPORT, viewport);
    glSelectBuffer(MaxSize, buffer);
    glRenderMode(GL_SELECT);

    glInitNames();
    glPushName(0);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluPickMatrix(GLdouble(pos.x()), GLdouble(viewport[3] - pos.y()),
                  5.0, 5.0, viewport);
    glFrustum(-w/side, w/side, -h/side, h/side, 1.0, 2000.0);
    updateGL();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    if (!glRenderMode(GL_RENDER))
        return -1;
    return buffer[3];
}

void GLSOMScene::setBackgroundColor(QPoint point, QColor color)
{
    int index = point.x() * ydim + point.y();
    imageList[index]->setBackgroundColor(color);
}

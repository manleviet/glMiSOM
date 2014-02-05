//
//
// glimage.cpp
//
// LE Viet Man
// 17/08/2011
//
//

#include "glimage.h"

//
// Constructeur
//
GLImage::GLImage(int index, QGLWidget *widget, QPointF position, CellSOM *cell)
{
    id = index;
    parent = widget;
    this->cell = cell;
    selected = false;
    drawID = false;
    origine = position;
    color = cell->getColor();
}

GLImage::~GLImage()
{
    cell = 0;
    parent = 0;
}

//
// Dessiner l'image utilisant OpenGL
//
void GLImage::draw()
{
    if (cell->isEmpty()) return;

    QRectF rect = cell->getRectF(0);

    glPushMatrix();
        glLoadName(id);

        glDisable(GL_TEXTURE_2D);
        // dessiner le fond
        if (color != Qt::white)
        {
            qreal size = SIZE_OF_IMAGE + SIZE_BORDER + (2 * SIZE_SHADOW) + (SIZE_BETWEEN_IMAGES / 4);
            qreal dx, dy;
            dx = SIZE_BORDER + (SIZE_BETWEEN_IMAGES / 8);
            dy = SIZE_BORDER + SIZE_SHADOW + (SIZE_BETWEEN_IMAGES / 8);

            parent->qglColor(color);
            glBegin(GL_QUADS);
                glVertex2i(origine.x() - dx, origine.y() -dy);
                glVertex2i(origine.x() - dx + size, origine.y() - dy);
                glVertex2i(origine.x() - dx + size, origine.y() -dy + size);
                glVertex2i(origine.x() - dx, origine.y() - dy + size);
            glEnd();
        }

        // dessiner l'ombre de l'image
        glColor4f(0.7, 0.7, 0.7, 0.5);
        glBegin(GL_QUADS);
            glVertex2i(-SIZE_BORDER +  rect.x() + SIZE_SHADOW,
                       -SIZE_BORDER + rect.y() - SIZE_SHADOW);
            glVertex2i(+SIZE_BORDER + rect.x() + rect.width() + SIZE_SHADOW,
                       -SIZE_BORDER + rect.y() - SIZE_SHADOW);
            glVertex2i(+SIZE_BORDER + rect.x() + rect.width() + SIZE_SHADOW,
                       SIZE_BORDER + rect.y() + rect.height() - SIZE_SHADOW);
            glVertex2i(-SIZE_BORDER + rect.x() + SIZE_SHADOW,
                       SIZE_BORDER + rect.y() + rect.height() - SIZE_SHADOW);
        glEnd();

        // dessiner la cadre de l'image
        if (selected)
            glColor4f(1.0, 0.0, 0.0, 0.0);
        else
            glColor4f(0.0, 0.0, 0.0, 0.0);

        glBegin(GL_QUADS);
            glVertex2i(-SIZE_BORDER +  rect.x(),
                       -SIZE_BORDER + rect.y());
            glVertex2i(+SIZE_BORDER + rect.x() + rect.width(),
                       -SIZE_BORDER + rect.y());
            glVertex2i(+SIZE_BORDER + rect.x() + rect.width(),
                       SIZE_BORDER + rect.y() + rect.height());
            glVertex2i(-SIZE_BORDER + rect.x(),
                       SIZE_BORDER + rect.y() + rect.height());
        glEnd();

        glEnable(GL_TEXTURE_2D);
        glColor4f(1.0f, 1.0f, 1.0f, 0.0);
        parent->drawTexture(rect, cell->getTexture(0), GL_TEXTURE_2D);

        if (drawID)
        {
            // dessiner le nombre d'images
            glDisable(GL_TEXTURE_2D);
            glPushMatrix();
                parent->qglColor(Qt::black);
                glTranslatef(rect.x(), rect.y(), 0);
                drawCircle(SIZE_OF_ID / 2);
                parent->qglColor(Qt::red);
                drawCircle((SIZE_OF_ID / 2) - 2);
            glPopMatrix();

            glEnable(GL_TEXTURE_2D);
            glColor4f(1.0f, 1.0f, 1.0f, 0.0);

            GLuint idTexture = idTextures[cell->getQuantityOfImages() - 2];
            QRectF idRect = idRects[cell->getQuantityOfImages() - 2];

            idRect = QRectF( rect.x() - idRect.x(), rect.y() - idRect.y(), idRect.width(), idRect.height());

            parent->drawTexture(idRect, idTexture, GL_TEXTURE_2D);
        }
    glPopMatrix();
}

//
// Charger des images pour creer le texture
//
void GLImage::loadImage()
{
    if (cell->isEmpty()) return;

    QList<Image*> imgs = cell->getAllImage();
    GLuint texture;
    QRectF rect;
    foreach (Image *img, imgs)
    {
        loadTextureImage(img, texture, rect);
        cell->addTexture(texture, rect);
    }

    // le nombre des images
    if (cell->getQuantityOfImages() >= 2)
    {
        drawID = true;

        loadTextureId();
    }
}

void GLImage::setSelected(bool selected)
{
    this->selected = selected;
}

void GLImage::setBackgroundColor(QColor color)
{
    this->color = color;
    cell->setColor(color);
}

//
// Effacer une image
// @param :
//      Image *img : un object Image
//
void GLImage::removeImage(Image *img)
{
    cell->removeImage(img);

    // mettre a jour le nombre d'images
    drawID = false;
    loadImage();
}

//
// Charger le texture de l'image pour dessiner dans OpenGL
// @param :
//      Image *img : un object Image qui stocke le chemin de l'image
//      GLuint &texture : l'indice du texture
//      QRectF &rect : la region pour dessiner le texture
//
void GLImage::loadTextureImage(Image *img, GLuint &texture, QRectF &rect)
{
    if (img == NULL) return;

    QPointF pos = origine;

    QPixmap image;
    image.load(img->getPath());

    qreal factor = 1;
    if (image.width() > image.height())
    {
        factor = SIZE_OF_IMAGE / image.width();
    }
    else
    {
        factor = SIZE_OF_IMAGE / image.height();
    }
    image = image.scaled(image.width() * factor, image.height() * factor);

    texture = parent->bindTexture(image, GL_TEXTURE_2D);

    qreal width = image.width();
    qreal height = image.height();

    // re-calculer la position a dessiner
    pos += QPointF((SIZE_OF_IMAGE - width) / 2, (SIZE_OF_IMAGE - height) / 2);

    rect = QRectF(pos, QSizeF(width, height));
}

QString GLImage::createImageIdentify(int id)
{
    // prendre le chemin du fichier id image
    QString path = Util::getPathImageId(id);
    QPixmap img;

    if (!img.load(path))
    {
        // dessiner le nombre d'images
        QImage idImage;

        if (!idImage.load(Util::getPathImageTransparent())) return "";

        qreal size = idImage.width();

        QString quantity = QString("%1").arg(id);

        QPainter *painter = new QPainter();
        painter->begin(&idImage);
        painter->setRenderHint(QPainter::Antialiasing, true); // beaute

        // font size
        painter->setFont(QFont(painter->font().family(), 100, QFont::Bold));
        while ((size - painter->fontMetrics().width(quantity)) < 6) {
            int pointSize = painter->font().pointSize() - 1;
            int weight = (pointSize < 6) ? QFont::Normal : QFont::Bold;
            painter->setFont(QFont(painter->font().family(), painter->font().pointSize() - 1, weight));
        }

        // draw
        painter->setPen(QPen(Qt::white, 2));
        painter->setBrush(QBrush(Qt::red));
        painter->drawRect(0, 0, size, size);
        painter->drawText(0, 0, size, size, Qt::AlignCenter, quantity);

        painter->end();

        // save
        idImage.save(path);
    }

    return path;
}

void GLImage::drawCircle(float radius)
{
    float DEG2RAD = 3.14159/180;
    float degInRad;

    glBegin(GL_TRIANGLE_FAN);
        for (int i = 0; i < 360; i++)
        {
            degInRad = i * DEG2RAD;
            glVertex2f(qCos(degInRad) * radius, qSin(degInRad) * radius);
        }
    glEnd();
}

void GLImage::loadTextureId()
{
    GLuint idTexture;
    QRectF idRect;
    QPixmap img;
    QPointF idPos;
    qreal factor;
    for (int i = 2; i <= cell->getQuantityOfImages(); i++)
    {
        QString path = createImageIdentify(i);

        if (!path.isEmpty())
        {
            img.load(path);

            factor = (SIZE_OF_ID - 2) / (img.width() * qSqrt(2));
            img = img.scaled(img.width() * factor, img.height() * factor);

            idTexture = parent->bindTexture(img, GL_TEXTURE_2D);

            qreal idWidth = img.width();
            qreal idHeight = img.height();

            idPos = QPointF(idWidth / 2, idHeight / 2);

            idRect = QRectF(idPos, QSizeF(idWidth, idHeight));
        }

        idTextures << idTexture;
        idRects << idRect;
    }
}

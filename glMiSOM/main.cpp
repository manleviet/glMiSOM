#include <QtGui/QApplication>
#include "mainwindow.h"

Q_IMPORT_PLUGIN(colorhistogramextractor)
Q_IMPORT_PLUGIN(humomentsextractor)
Q_IMPORT_PLUGIN(matrixcooccurrence2extractor)

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (!QGLFormat::hasOpenGL()) {
        QMessageBox::information(0, "OpenGL",
                                 "This system does not support OpenGL.");
        return -1;
    }

    MainWindow w;
    w.resize(w.sizeHint());
    w.show();

    return a.exec();
}

/****************************************************************************
** Meta object code from reading C++ file 'glsomscene.h'
**
** Created: Sat Oct 15 11:51:48 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../glMiSOM/Scene/glsomscene.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'glsomscene.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GLSOMScene[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       1,   84, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      26,   11,   11,   11, 0x05,
      58,   47,   11,   11, 0x05,
     110,  100,   11,   11, 0x05,
     153,  149,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
     185,  173,   11,   11, 0x08,
     218,   11,   11,   11, 0x08,
     236,   11,   11,   11, 0x08,
     251,   11,   11,   11, 0x08,
     263,   11,   11,   11, 0x08,
     277,   11,   11,   11, 0x08,
     288,   11,   11,   11, 0x08,
     302,   11,   11,   11, 0x08,
     314,   11,   11,   11, 0x08,

 // properties: name, type, flags
     345,  337, 0x1a095103,

       0        // eod
};

static const char qt_meta_stringdata_GLSOMScene[] = {
    "GLSOMScene\0\0changed(bool)\0"
    "changePosition(bool)\0imgs,diffs\0"
    "viewMetadata(QList<Image*>,QList<double>)\0"
    "img,diffs\0viewImage(QList<Image*>,QList<double>)\0"
    "img\0deleteImage(Image*)\0scene,event\0"
    "keyPress(GLSOMScene*,QKeyEvent*)\0"
    "finishAnimation()\0viewMetadata()\0"
    "viewImage()\0chooseColor()\0classify()\0"
    "deleteImage()\0showClass()\0"
    "resetColorBackground()\0QPointF\0dXY\0"
};

const QMetaObject GLSOMScene::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_GLSOMScene,
      qt_meta_data_GLSOMScene, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GLSOMScene::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GLSOMScene::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GLSOMScene::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GLSOMScene))
        return static_cast<void*>(const_cast< GLSOMScene*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int GLSOMScene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: changed((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: changePosition((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: viewMetadata((*reinterpret_cast< QList<Image*>(*)>(_a[1])),(*reinterpret_cast< QList<double>(*)>(_a[2]))); break;
        case 3: viewImage((*reinterpret_cast< QList<Image*>(*)>(_a[1])),(*reinterpret_cast< QList<double>(*)>(_a[2]))); break;
        case 4: deleteImage((*reinterpret_cast< Image*(*)>(_a[1]))); break;
        case 5: keyPress((*reinterpret_cast< GLSOMScene*(*)>(_a[1])),(*reinterpret_cast< QKeyEvent*(*)>(_a[2]))); break;
        case 6: finishAnimation(); break;
        case 7: viewMetadata(); break;
        case 8: viewImage(); break;
        case 9: chooseColor(); break;
        case 10: classify(); break;
        case 11: deleteImage(); break;
        case 12: showClass(); break;
        case 13: resetColorBackground(); break;
        default: ;
        }
        _id -= 14;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QPointF*>(_v) = dXY(); break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setDXY(*reinterpret_cast< QPointF*>(_v)); break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void GLSOMScene::changed(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GLSOMScene::changePosition(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GLSOMScene::viewMetadata(QList<Image*> _t1, QList<double> _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void GLSOMScene::viewImage(QList<Image*> _t1, QList<double> _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void GLSOMScene::deleteImage(Image * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE

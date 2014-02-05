/****************************************************************************
** Meta object code from reading C++ file 'chosendescriptors.h'
**
** Created: Sat Oct 15 11:20:11 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../glMiSOM/UI/chosendescriptors.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chosendescriptors.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ChosenDescriptors[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
      35,   18,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ChosenDescriptors[] = {
    "ChosenDescriptors\0\0chooseFeature()\0"
    "deleteItem()\0"
};

const QMetaObject ChosenDescriptors::staticMetaObject = {
    { &QTableWidget::staticMetaObject, qt_meta_stringdata_ChosenDescriptors,
      qt_meta_data_ChosenDescriptors, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ChosenDescriptors::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ChosenDescriptors::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ChosenDescriptors::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ChosenDescriptors))
        return static_cast<void*>(const_cast< ChosenDescriptors*>(this));
    return QTableWidget::qt_metacast(_clname);
}

int ChosenDescriptors::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTableWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: chooseFeature(); break;
        case 1: deleteItem(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void ChosenDescriptors::chooseFeature()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE

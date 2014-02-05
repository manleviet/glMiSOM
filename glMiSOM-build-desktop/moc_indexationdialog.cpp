/****************************************************************************
** Meta object code from reading C++ file 'indexationdialog.h'
**
** Created: Sat Oct 15 11:20:09 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../glMiSOM/UI/indexationdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'indexationdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_IndexationDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      22,   18,   17,   17, 0x05,
      40,   35,   17,   17, 0x05,
      63,   35,   17,   17, 0x05,
      96,   89,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
     110,   17,   17,   17, 0x08,
     134,   17,   17,   17, 0x08,
     157,   17,   17,   17, 0x08,
     169,   17,   17,   17, 0x08,
     185,   17,   17,   17, 0x08,
     192,   17,   17,   17, 0x08,
     205,   17,   17,   17, 0x08,
     218,   17,   17,   17, 0x08,
     229,   17,   17,   17, 0x08,
     240,   17,   17,   17, 0x08,
     249,   17,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_IndexationDialog[] = {
    "IndexationDialog\0\0geo\0close(QRect)\0"
    "grid\0finishVisual(GridSOM*)\0"
    "finishRearrange(GridSOM*)\0enable\0"
    "saveMap(bool)\0on_btnDefault_clicked()\0"
    "on_btnCancel_clicked()\0viewCodes()\0"
    "chooseFeature()\0init()\0saveWeight()\0"
    "loadWeight()\0ordering()\0converge()\0"
    "visual()\0rearrange()\0"
};

const QMetaObject IndexationDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_IndexationDialog,
      qt_meta_data_IndexationDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &IndexationDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *IndexationDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *IndexationDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_IndexationDialog))
        return static_cast<void*>(const_cast< IndexationDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int IndexationDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: close((*reinterpret_cast< QRect(*)>(_a[1]))); break;
        case 1: finishVisual((*reinterpret_cast< GridSOM*(*)>(_a[1]))); break;
        case 2: finishRearrange((*reinterpret_cast< GridSOM*(*)>(_a[1]))); break;
        case 3: saveMap((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: on_btnDefault_clicked(); break;
        case 5: on_btnCancel_clicked(); break;
        case 6: viewCodes(); break;
        case 7: chooseFeature(); break;
        case 8: init(); break;
        case 9: saveWeight(); break;
        case 10: loadWeight(); break;
        case 11: ordering(); break;
        case 12: converge(); break;
        case 13: visual(); break;
        case 14: rearrange(); break;
        default: ;
        }
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void IndexationDialog::close(QRect _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void IndexationDialog::finishVisual(GridSOM * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void IndexationDialog::finishRearrange(GridSOM * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void IndexationDialog::saveMap(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE

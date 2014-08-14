/****************************************************************************
** Meta object code from reading C++ file 'Nansy.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/NansyLib/Nansy.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Nansy.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Nansy_t {
    QByteArrayData data[12];
    char stringdata[148];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Nansy_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Nansy_t qt_meta_stringdata_Nansy = {
    {
QT_MOC_LITERAL(0, 0, 5),
QT_MOC_LITERAL(1, 6, 7),
QT_MOC_LITERAL(2, 14, 0),
QT_MOC_LITERAL(3, 15, 13),
QT_MOC_LITERAL(4, 29, 8),
QT_MOC_LITERAL(5, 38, 11),
QT_MOC_LITERAL(6, 50, 11),
QT_MOC_LITERAL(7, 62, 16),
QT_MOC_LITERAL(8, 79, 18),
QT_MOC_LITERAL(9, 98, 17),
QT_MOC_LITERAL(10, 116, 17),
QT_MOC_LITERAL(11, 134, 13)
    },
    "Nansy\0showSth\0\0menuTriggered\0QAction*\0"
    "hideAllMenu\0showAllMenu\0setViewMode2Move\0"
    "setViewMode2Rotate\0setViewMode2Scale\0"
    "setViewMode2Fixed\0resetViewMode"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Nansy[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x08 /* Private */,
       3,    1,   60,    2, 0x08 /* Private */,
       5,    0,   63,    2, 0x08 /* Private */,
       6,    1,   64,    2, 0x08 /* Private */,
       7,    0,   67,    2, 0x08 /* Private */,
       8,    0,   68,    2, 0x08 /* Private */,
       9,    0,   69,    2, 0x08 /* Private */,
      10,    0,   70,    2, 0x08 /* Private */,
      11,    0,   71,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Nansy::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Nansy *_t = static_cast<Nansy *>(_o);
        switch (_id) {
        case 0: _t->showSth(); break;
        case 1: _t->menuTriggered((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 2: _t->hideAllMenu(); break;
        case 3: _t->showAllMenu((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 4: _t->setViewMode2Move(); break;
        case 5: _t->setViewMode2Rotate(); break;
        case 6: _t->setViewMode2Scale(); break;
        case 7: _t->setViewMode2Fixed(); break;
        case 8: _t->resetViewMode(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        }
    }
}

const QMetaObject Nansy::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Nansy.data,
      qt_meta_data_Nansy,  qt_static_metacall, 0, 0}
};


const QMetaObject *Nansy::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Nansy::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Nansy.stringdata))
        return static_cast<void*>(const_cast< Nansy*>(this));
    return QWidget::qt_metacast(_clname);
}

int Nansy::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

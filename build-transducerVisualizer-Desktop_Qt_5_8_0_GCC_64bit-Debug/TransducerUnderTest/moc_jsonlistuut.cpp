/****************************************************************************
** Meta object code from reading C++ file 'jsonlistuut.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../TransducerVisualizerSolution/TransducerUnderTest/JSON/jsonlistuut.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'jsonlistuut.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_JSONListUUT_t {
    QByteArrayData data[5];
    char stringdata0[47];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_JSONListUUT_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_JSONListUUT_t qt_meta_stringdata_JSONListUUT = {
    {
QT_MOC_LITERAL(0, 0, 11), // "JSONListUUT"
QT_MOC_LITERAL(1, 12, 9), // "EmptyList"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 9), // "Singleton"
QT_MOC_LITERAL(4, 33, 13) // "ListOfStrings"

    },
    "JSONListUUT\0EmptyList\0\0Singleton\0"
    "ListOfStrings"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_JSONListUUT[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x08 /* Private */,
       3,    0,   30,    2, 0x08 /* Private */,
       4,    0,   31,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void JSONListUUT::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        JSONListUUT *_t = static_cast<JSONListUUT *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->EmptyList(); break;
        case 1: _t->Singleton(); break;
        case 2: _t->ListOfStrings(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject JSONListUUT::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_JSONListUUT.data,
      qt_meta_data_JSONListUUT,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *JSONListUUT::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *JSONListUUT::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_JSONListUUT.stringdata0))
        return static_cast<void*>(const_cast< JSONListUUT*>(this));
    return QObject::qt_metacast(_clname);
}

int JSONListUUT::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'plot.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Telemetrie_0_1/plot.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'plot.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Plot_t {
    QByteArrayData data[12];
    char stringdata0[165];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Plot_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Plot_t qt_meta_stringdata_Plot = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Plot"
QT_MOC_LITERAL(1, 5, 17), // "setIntervalLength"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 13), // "setXAxisValue"
QT_MOC_LITERAL(4, 38, 13), // "minimalerWert"
QT_MOC_LITERAL(5, 52, 13), // "maximalerWert"
QT_MOC_LITERAL(6, 66, 13), // "setYAxisValue"
QT_MOC_LITERAL(7, 80, 11), // "setPenStyle"
QT_MOC_LITERAL(8, 92, 3), // "pen"
QT_MOC_LITERAL(9, 96, 14), // "indexMessdaten"
QT_MOC_LITERAL(10, 111, 25), // "mauskoordinatenAktivieren"
QT_MOC_LITERAL(11, 137, 27) // "mauskoordinatenDeaktivieren"

    },
    "Plot\0setIntervalLength\0\0setXAxisValue\0"
    "minimalerWert\0maximalerWert\0setYAxisValue\0"
    "setPenStyle\0pen\0indexMessdaten\0"
    "mauskoordinatenAktivieren\0"
    "mauskoordinatenDeaktivieren"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Plot[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x0a /* Public */,
       3,    2,   47,    2, 0x0a /* Public */,
       6,    2,   52,    2, 0x0a /* Public */,
       7,    2,   57,    2, 0x0a /* Public */,
      10,    0,   62,    2, 0x0a /* Public */,
      11,    0,   63,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,    4,    5,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,    4,    5,
    QMetaType::Void, QMetaType::QPen, QMetaType::Int,    8,    9,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Plot::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Plot *_t = static_cast<Plot *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setIntervalLength((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->setXAxisValue((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 2: _t->setYAxisValue((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 3: _t->setPenStyle((*reinterpret_cast< QPen(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->mauskoordinatenAktivieren(); break;
        case 5: _t->mauskoordinatenDeaktivieren(); break;
        default: ;
        }
    }
}

const QMetaObject Plot::staticMetaObject = {
    { &QwtPlot::staticMetaObject, qt_meta_stringdata_Plot.data,
      qt_meta_data_Plot,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Plot::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Plot::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Plot.stringdata0))
        return static_cast<void*>(this);
    return QwtPlot::qt_metacast(_clname);
}

int Plot::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QwtPlot::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

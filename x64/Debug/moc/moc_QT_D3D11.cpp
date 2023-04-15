/****************************************************************************
** Meta object code from reading C++ file 'QT_D3D11.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../QT_D3D11.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QT_D3D11.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QT_D3D11_t {
    QByteArrayData data[14];
    char stringdata0[287];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QT_D3D11_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QT_D3D11_t qt_meta_stringdata_QT_D3D11 = {
    {
QT_MOC_LITERAL(0, 0, 8), // "QT_D3D11"
QT_MOC_LITERAL(1, 9, 27), // "on_actionOpenFile_triggered"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 22), // "on_actionTex_triggered"
QT_MOC_LITERAL(4, 61, 26), // "on_radioWhiteLight_clicked"
QT_MOC_LITERAL(5, 88, 25), // "on_radioBlueLight_clicked"
QT_MOC_LITERAL(6, 114, 24), // "on_radioRedLight_clicked"
QT_MOC_LITERAL(7, 139, 21), // "on_rBtnNormal_clicked"
QT_MOC_LITERAL(8, 161, 20), // "on_rBtnWater_clicked"
QT_MOC_LITERAL(9, 182, 19), // "on_rBtnFire_clicked"
QT_MOC_LITERAL(10, 202, 19), // "on_cBtnSpec_clicked"
QT_MOC_LITERAL(11, 222, 20), // "on_BtnModify_clicked"
QT_MOC_LITERAL(12, 243, 20), // "on_CamSlidee_changed"
QT_MOC_LITERAL(13, 264, 22) // "on_LightSlidee_changed"

    },
    "QT_D3D11\0on_actionOpenFile_triggered\0"
    "\0on_actionTex_triggered\0"
    "on_radioWhiteLight_clicked\0"
    "on_radioBlueLight_clicked\0"
    "on_radioRedLight_clicked\0on_rBtnNormal_clicked\0"
    "on_rBtnWater_clicked\0on_rBtnFire_clicked\0"
    "on_cBtnSpec_clicked\0on_BtnModify_clicked\0"
    "on_CamSlidee_changed\0on_LightSlidee_changed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QT_D3D11[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x08 /* Private */,
       3,    0,   75,    2, 0x08 /* Private */,
       4,    0,   76,    2, 0x08 /* Private */,
       5,    0,   77,    2, 0x08 /* Private */,
       6,    0,   78,    2, 0x08 /* Private */,
       7,    0,   79,    2, 0x08 /* Private */,
       8,    0,   80,    2, 0x08 /* Private */,
       9,    0,   81,    2, 0x08 /* Private */,
      10,    1,   82,    2, 0x08 /* Private */,
      11,    0,   85,    2, 0x08 /* Private */,
      12,    1,   86,    2, 0x08 /* Private */,
      13,    1,   89,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void QT_D3D11::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QT_D3D11 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_actionOpenFile_triggered(); break;
        case 1: _t->on_actionTex_triggered(); break;
        case 2: _t->on_radioWhiteLight_clicked(); break;
        case 3: _t->on_radioBlueLight_clicked(); break;
        case 4: _t->on_radioRedLight_clicked(); break;
        case 5: _t->on_rBtnNormal_clicked(); break;
        case 6: _t->on_rBtnWater_clicked(); break;
        case 7: _t->on_rBtnFire_clicked(); break;
        case 8: _t->on_cBtnSpec_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->on_BtnModify_clicked(); break;
        case 10: _t->on_CamSlidee_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->on_LightSlidee_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QT_D3D11::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_QT_D3D11.data,
    qt_meta_data_QT_D3D11,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QT_D3D11::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QT_D3D11::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QT_D3D11.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int QT_D3D11::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

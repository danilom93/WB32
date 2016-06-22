/****************************************************************************
** Meta object code from reading C++ file 'NetworkConfig.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../MTempClient/NetworkConfig.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'NetworkConfig.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_NetworkConfig_t {
    QByteArrayData data[21];
    char stringdata0[449];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NetworkConfig_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NetworkConfig_t qt_meta_stringdata_NetworkConfig = {
    {
QT_MOC_LITERAL(0, 0, 13), // "NetworkConfig"
QT_MOC_LITERAL(1, 14, 28), // "on_netKeyShowChecbox_clicked"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 7), // "checked"
QT_MOC_LITERAL(4, 52, 30), // "on_netNameLineEdit_textChanged"
QT_MOC_LITERAL(5, 83, 4), // "arg1"
QT_MOC_LITERAL(6, 88, 29), // "on_netKeyLineEdit_textChanged"
QT_MOC_LITERAL(7, 118, 30), // "on_boardIPLineEdit_textChanged"
QT_MOC_LITERAL(8, 149, 31), // "on_usernameLineEdit_textChanged"
QT_MOC_LITERAL(9, 181, 32), // "on_password1LineEdit_textChanged"
QT_MOC_LITERAL(10, 214, 32), // "on_password2LineEdit_textChanged"
QT_MOC_LITERAL(11, 247, 32), // "on_boardPortLineEdit_textChanged"
QT_MOC_LITERAL(12, 280, 22), // "on_clearButton_clicked"
QT_MOC_LITERAL(13, 303, 22), // "on_abortButton_clicked"
QT_MOC_LITERAL(14, 326, 26), // "on_configureButton_clicked"
QT_MOC_LITERAL(15, 353, 15), // "notifyConnected"
QT_MOC_LITERAL(16, 369, 11), // "notifyError"
QT_MOC_LITERAL(17, 381, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(18, 410, 18), // "notifyDisconnected"
QT_MOC_LITERAL(19, 429, 9), // "rxHandler"
QT_MOC_LITERAL(20, 439, 9) // "txHandler"

    },
    "NetworkConfig\0on_netKeyShowChecbox_clicked\0"
    "\0checked\0on_netNameLineEdit_textChanged\0"
    "arg1\0on_netKeyLineEdit_textChanged\0"
    "on_boardIPLineEdit_textChanged\0"
    "on_usernameLineEdit_textChanged\0"
    "on_password1LineEdit_textChanged\0"
    "on_password2LineEdit_textChanged\0"
    "on_boardPortLineEdit_textChanged\0"
    "on_clearButton_clicked\0on_abortButton_clicked\0"
    "on_configureButton_clicked\0notifyConnected\0"
    "notifyError\0QAbstractSocket::SocketError\0"
    "notifyDisconnected\0rxHandler\0txHandler"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NetworkConfig[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   94,    2, 0x08 /* Private */,
       4,    1,   97,    2, 0x08 /* Private */,
       6,    1,  100,    2, 0x08 /* Private */,
       7,    1,  103,    2, 0x08 /* Private */,
       8,    1,  106,    2, 0x08 /* Private */,
       9,    1,  109,    2, 0x08 /* Private */,
      10,    1,  112,    2, 0x08 /* Private */,
      11,    1,  115,    2, 0x08 /* Private */,
      12,    0,  118,    2, 0x08 /* Private */,
      13,    0,  119,    2, 0x08 /* Private */,
      14,    0,  120,    2, 0x08 /* Private */,
      15,    0,  121,    2, 0x08 /* Private */,
      16,    1,  122,    2, 0x08 /* Private */,
      18,    0,  125,    2, 0x08 /* Private */,
      19,    0,  126,    2, 0x08 /* Private */,
      20,    0,  127,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 17,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void NetworkConfig::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NetworkConfig *_t = static_cast<NetworkConfig *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_netKeyShowChecbox_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->on_netNameLineEdit_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->on_netKeyLineEdit_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->on_boardIPLineEdit_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->on_usernameLineEdit_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->on_password1LineEdit_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->on_password2LineEdit_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->on_boardPortLineEdit_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->on_clearButton_clicked(); break;
        case 9: _t->on_abortButton_clicked(); break;
        case 10: _t->on_configureButton_clicked(); break;
        case 11: _t->notifyConnected(); break;
        case 12: _t->notifyError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 13: _t->notifyDisconnected(); break;
        case 14: _t->rxHandler(); break;
        case 15: _t->txHandler(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 12:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    }
}

const QMetaObject NetworkConfig::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_NetworkConfig.data,
      qt_meta_data_NetworkConfig,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *NetworkConfig::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NetworkConfig::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_NetworkConfig.stringdata0))
        return static_cast<void*>(const_cast< NetworkConfig*>(this));
    return QDialog::qt_metacast(_clname);
}

int NetworkConfig::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'MClient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../MTempClient/MClient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MClient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MClient_t {
    QByteArrayData data[32];
    char stringdata0[340];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MClient_t qt_meta_stringdata_MClient = {
    {
QT_MOC_LITERAL(0, 0, 7), // "MClient"
QT_MOC_LITERAL(1, 8, 14), // "addressChanged"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 10), // "newAddress"
QT_MOC_LITERAL(4, 35, 11), // "portChanged"
QT_MOC_LITERAL(5, 47, 7), // "newPort"
QT_MOC_LITERAL(6, 55, 9), // "connected"
QT_MOC_LITERAL(7, 65, 12), // "disconnected"
QT_MOC_LITERAL(8, 78, 5), // "error"
QT_MOC_LITERAL(9, 84, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(10, 113, 9), // "lastError"
QT_MOC_LITERAL(11, 123, 13), // "tokenReceived"
QT_MOC_LITERAL(12, 137, 10), // "dataSended"
QT_MOC_LITERAL(13, 148, 13), // "connectToHost"
QT_MOC_LITERAL(14, 162, 18), // "disconnectFromHost"
QT_MOC_LITERAL(15, 181, 5), // "write"
QT_MOC_LITERAL(16, 187, 3), // "str"
QT_MOC_LITERAL(17, 191, 7), // "waitFor"
QT_MOC_LITERAL(18, 199, 12), // "dataReceived"
QT_MOC_LITERAL(19, 212, 11), // "bufferClear"
QT_MOC_LITERAL(20, 224, 10), // "setAddress"
QT_MOC_LITERAL(21, 235, 4), // "addr"
QT_MOC_LITERAL(22, 240, 7), // "setPort"
QT_MOC_LITERAL(23, 248, 4), // "port"
QT_MOC_LITERAL(24, 253, 16), // "connectedBouncer"
QT_MOC_LITERAL(25, 270, 18), // "diconnectedBouncer"
QT_MOC_LITERAL(26, 289, 12), // "errorBouncer"
QT_MOC_LITERAL(27, 302, 3), // "err"
QT_MOC_LITERAL(28, 306, 9), // "rxHandler"
QT_MOC_LITERAL(29, 316, 9), // "txHandler"
QT_MOC_LITERAL(30, 326, 5), // "bytes"
QT_MOC_LITERAL(31, 332, 7) // "address"

    },
    "MClient\0addressChanged\0\0newAddress\0"
    "portChanged\0newPort\0connected\0"
    "disconnected\0error\0QAbstractSocket::SocketError\0"
    "lastError\0tokenReceived\0dataSended\0"
    "connectToHost\0disconnectFromHost\0write\0"
    "str\0waitFor\0dataReceived\0bufferClear\0"
    "setAddress\0addr\0setPort\0port\0"
    "connectedBouncer\0diconnectedBouncer\0"
    "errorBouncer\0err\0rxHandler\0txHandler\0"
    "bytes\0address"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MClient[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       2,  158, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  119,    2, 0x06 /* Public */,
       4,    1,  122,    2, 0x06 /* Public */,
       6,    0,  125,    2, 0x06 /* Public */,
       7,    0,  126,    2, 0x06 /* Public */,
       8,    1,  127,    2, 0x06 /* Public */,
      11,    0,  130,    2, 0x06 /* Public */,
      12,    0,  131,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    0,  132,    2, 0x0a /* Public */,
      14,    0,  133,    2, 0x0a /* Public */,
      15,    1,  134,    2, 0x0a /* Public */,
      17,    1,  137,    2, 0x0a /* Public */,
      18,    0,  140,    2, 0x0a /* Public */,
      19,    0,  141,    2, 0x0a /* Public */,
      10,    0,  142,    2, 0x0a /* Public */,
      20,    1,  143,    2, 0x0a /* Public */,
      22,    1,  146,    2, 0x0a /* Public */,
      24,    0,  149,    2, 0x08 /* Private */,
      25,    0,  150,    2, 0x08 /* Private */,
      26,    1,  151,    2, 0x08 /* Private */,
      28,    0,  154,    2, 0x08 /* Private */,
      29,    1,  155,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::UShort,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool, QMetaType::QString,   16,
    QMetaType::Bool, QMetaType::QString,   16,
    QMetaType::QString,
    QMetaType::Void,
    QMetaType::QString,
    QMetaType::Bool, QMetaType::QString,   21,
    QMetaType::Bool, QMetaType::UShort,   23,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   27,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong,   30,

 // properties: name, type, flags
      31, QMetaType::QString, 0x00495103,
      23, QMetaType::UShort, 0x00495103,

 // properties: notify_signal_id
       0,
       1,

       0        // eod
};

void MClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MClient *_t = static_cast<MClient *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->addressChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->portChanged((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 2: _t->connected(); break;
        case 3: _t->disconnected(); break;
        case 4: _t->error((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 5: _t->tokenReceived(); break;
        case 6: _t->dataSended(); break;
        case 7: { bool _r = _t->connectToHost();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 8: { bool _r = _t->disconnectFromHost();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 9: { bool _r = _t->write((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 10: { bool _r = _t->waitFor((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 11: { QString _r = _t->dataReceived();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 12: _t->bufferClear(); break;
        case 13: { QString _r = _t->lastError();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 14: { bool _r = _t->setAddress((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 15: { bool _r = _t->setPort((*reinterpret_cast< const quint16(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 16: _t->connectedBouncer(); break;
        case 17: _t->diconnectedBouncer(); break;
        case 18: _t->errorBouncer((*reinterpret_cast< const QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 19: _t->rxHandler(); break;
        case 20: _t->txHandler((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        case 18:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MClient::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MClient::addressChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MClient::*_t)(quint16 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MClient::portChanged)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (MClient::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MClient::connected)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (MClient::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MClient::disconnected)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (MClient::*_t)(QAbstractSocket::SocketError );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MClient::error)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (MClient::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MClient::tokenReceived)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (MClient::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MClient::dataSended)) {
                *result = 6;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        MClient *_t = static_cast<MClient *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->address(); break;
        case 1: *reinterpret_cast< quint16*>(_v) = _t->port(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        MClient *_t = static_cast<MClient *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setAddress(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setPort(*reinterpret_cast< quint16*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject MClient::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MClient.data,
      qt_meta_data_MClient,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MClient::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MClient.stringdata0))
        return static_cast<void*>(const_cast< MClient*>(this));
    return QObject::qt_metacast(_clname);
}

int MClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void MClient::addressChanged(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MClient::portChanged(quint16 _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MClient::connected()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void MClient::disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void MClient::error(QAbstractSocket::SocketError _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MClient::tokenReceived()
{
    QMetaObject::activate(this, &staticMetaObject, 5, Q_NULLPTR);
}

// SIGNAL 6
void MClient::dataSended()
{
    QMetaObject::activate(this, &staticMetaObject, 6, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE

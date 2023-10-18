/****************************************************************************
** Meta object code from reading C++ file 'TcpClient.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ControlGrua_Qt_TCP/TcpClient.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TcpClient.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TCPClient_t {
    QByteArrayData data[12];
    char stringdata0[145];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TCPClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TCPClient_t qt_meta_stringdata_TCPClient = {
    {
QT_MOC_LITERAL(0, 0, 9), // "TCPClient"
QT_MOC_LITERAL(1, 10, 20), // "setConnectedCheckBox"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 10), // "QCheckBox*"
QT_MOC_LITERAL(4, 43, 12), // "connectd_chk"
QT_MOC_LITERAL(5, 56, 11), // "onReadyRead"
QT_MOC_LITERAL(6, 68, 8), // "sendData"
QT_MOC_LITERAL(7, 77, 4), // "data"
QT_MOC_LITERAL(8, 82, 19), // "sendDataIteratively"
QT_MOC_LITERAL(9, 102, 12), // "getConnected"
QT_MOC_LITERAL(10, 115, 15), // "getDisconnected"
QT_MOC_LITERAL(11, 131, 13) // "sendHeartbeat"

    },
    "TCPClient\0setConnectedCheckBox\0\0"
    "QCheckBox*\0connectd_chk\0onReadyRead\0"
    "sendData\0data\0sendDataIteratively\0"
    "getConnected\0getDisconnected\0sendHeartbeat"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TCPClient[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x0a /* Public */,
       5,    0,   52,    2, 0x0a /* Public */,
       6,    1,   53,    2, 0x0a /* Public */,
       8,    0,   56,    2, 0x0a /* Public */,
       9,    0,   57,    2, 0x0a /* Public */,
      10,    0,   58,    2, 0x0a /* Public */,
      11,    0,   59,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::LongLong, QMetaType::QByteArray,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void TCPClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TCPClient *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setConnectedCheckBox((*reinterpret_cast< QCheckBox*(*)>(_a[1]))); break;
        case 1: _t->onReadyRead(); break;
        case 2: { qint64 _r = _t->sendData((*reinterpret_cast< QByteArray(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< qint64*>(_a[0]) = std::move(_r); }  break;
        case 3: _t->sendDataIteratively(); break;
        case 4: _t->getConnected(); break;
        case 5: _t->getDisconnected(); break;
        case 6: _t->sendHeartbeat(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCheckBox* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TCPClient::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_TCPClient.data,
    qt_meta_data_TCPClient,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TCPClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TCPClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TCPClient.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int TCPClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'ipmsg_protocol.h'
**
** Created: Tue Apr 24 17:55:35 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ipmsg_protocol.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ipmsg_protocol.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_IpMsgProtocol[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      22,   15,   14,   14, 0x05,
      65,   47,   14,   14, 0x05,
     101,   95,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
     124,   14,   14,   14, 0x08,
     147,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_IpMsgProtocol[] = {
    "IpMsgProtocol\0\0packet\0newMsg(IpMsgRecvPacket*)\0"
    "strUserName,strIp\0onUserOnline(QString,QString)\0"
    "strIp\0onUserOffline(QString)\0"
    "readPendingDatagrams()\0processSendMsg()\0"
};

void IpMsgProtocol::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        IpMsgProtocol *_t = static_cast<IpMsgProtocol *>(_o);
        switch (_id) {
        case 0: _t->newMsg((*reinterpret_cast< IpMsgRecvPacket*(*)>(_a[1]))); break;
        case 1: _t->onUserOnline((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 2: _t->onUserOffline((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->readPendingDatagrams(); break;
        case 4: _t->processSendMsg(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData IpMsgProtocol::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject IpMsgProtocol::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_IpMsgProtocol,
      qt_meta_data_IpMsgProtocol, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &IpMsgProtocol::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *IpMsgProtocol::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *IpMsgProtocol::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_IpMsgProtocol))
        return static_cast<void*>(const_cast< IpMsgProtocol*>(this));
    return QObject::qt_metacast(_clname);
}

int IpMsgProtocol::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void IpMsgProtocol::newMsg(IpMsgRecvPacket * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void IpMsgProtocol::onUserOnline(const QString & _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void IpMsgProtocol::onUserOffline(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE

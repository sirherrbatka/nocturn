/****************************************************************************
** Meta object code from reading C++ file 'maincontroler.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "maincontroler.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'maincontroler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainControler[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   15,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      86,   14,   14,   14, 0x0a,
      98,   14,   14,   14, 0x0a,
     126,  110,   14,   14, 0x0a,
     179,  164,   14,   14, 0x0a,
     221,  216,   14,   14, 0x0a,
     256,  252,   14,   14, 0x0a,
     300,  295,   14,   14, 0x0a,
     325,   14,   14,   14, 0x0a,
     337,   14,   14,   14, 0x0a,
     354,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainControler[] = {
    "MainControler\0\0,\0"
    "StatusChanged(SharedTypes::PlaybackState,SharedTypes::PlaybackState)\0"
    "nextTrack()\0prevTrack()\0currentPlaylist\0"
    "changeCurrentPlayList(PlayListModel*)\0"
    "activePlayList\0changeActivePlayList(PlayListModel*)\0"
    "list\0addPathToPlayList(QList<QUrl>)\0"
    "key\0deletePlayList(unsigned long long int)\0"
    "path\0playFile(const QString*)\0fileEnded()\0"
    "togglePlayback()\0startPlayback()\0"
};

void MainControler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainControler *_t = static_cast<MainControler *>(_o);
        switch (_id) {
        case 0: _t->StatusChanged((*reinterpret_cast< SharedTypes::PlaybackState(*)>(_a[1])),(*reinterpret_cast< SharedTypes::PlaybackState(*)>(_a[2]))); break;
        case 1: _t->nextTrack(); break;
        case 2: _t->prevTrack(); break;
        case 3: _t->changeCurrentPlayList((*reinterpret_cast< PlayListModel*(*)>(_a[1]))); break;
        case 4: _t->changeActivePlayList((*reinterpret_cast< PlayListModel*(*)>(_a[1]))); break;
        case 5: _t->addPathToPlayList((*reinterpret_cast< QList<QUrl>(*)>(_a[1]))); break;
        case 6: _t->deletePlayList((*reinterpret_cast< unsigned long long int(*)>(_a[1]))); break;
        case 7: _t->playFile((*reinterpret_cast< const QString*(*)>(_a[1]))); break;
        case 8: _t->fileEnded(); break;
        case 9: _t->togglePlayback(); break;
        case 10: _t->startPlayback(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainControler::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainControler::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MainControler,
      qt_meta_data_MainControler, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainControler::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainControler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainControler::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainControler))
        return static_cast<void*>(const_cast< MainControler*>(this));
    return QObject::qt_metacast(_clname);
}

int MainControler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void MainControler::StatusChanged(SharedTypes::PlaybackState _t1, SharedTypes::PlaybackState _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE

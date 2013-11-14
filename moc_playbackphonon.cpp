/****************************************************************************
** Meta object code from reading C++ file 'playbackphonon.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "playbackphonon.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'playbackphonon.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PlaybackPhonon[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      36,   16,   15,   15, 0x0a,
      83,   78,   15,   15, 0x0a,
     108,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_PlaybackPhonon[] = {
    "PlaybackPhonon\0\0oldstatus,newstatus\0"
    "changeStatus(Phonon::State,Phonon::State)\0"
    "path\0playFile(const QString*)\0"
    "togglePlayback()\0"
};

void PlaybackPhonon::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PlaybackPhonon *_t = static_cast<PlaybackPhonon *>(_o);
        switch (_id) {
        case 0: _t->changeStatus((*reinterpret_cast< Phonon::State(*)>(_a[1])),(*reinterpret_cast< Phonon::State(*)>(_a[2]))); break;
        case 1: _t->playFile((*reinterpret_cast< const QString*(*)>(_a[1]))); break;
        case 2: _t->togglePlayback(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PlaybackPhonon::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PlaybackPhonon::staticMetaObject = {
    { &PlaybackModel::staticMetaObject, qt_meta_stringdata_PlaybackPhonon,
      qt_meta_data_PlaybackPhonon, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PlaybackPhonon::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PlaybackPhonon::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PlaybackPhonon::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PlaybackPhonon))
        return static_cast<void*>(const_cast< PlaybackPhonon*>(this));
    return PlaybackModel::qt_metacast(_clname);
}

int PlaybackPhonon::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PlaybackModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

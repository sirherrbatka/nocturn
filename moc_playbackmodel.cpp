/****************************************************************************
** Meta object code from reading C++ file 'playbackmodel.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "playbackmodel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'playbackmodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PlaybackModel[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,
      27,   14,   14,   14, 0x05,
      46,   14,   14,   14, 0x05,
      66,   64,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
     140,  135,   14,   14, 0x0a,
     165,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_PlaybackModel[] = {
    "PlaybackModel\0\0FileEnded()\0"
    "PlayingLocalFile()\0SecondHasPassed()\0"
    ",\0"
    "StatusChanged(SharedTypes::PlaybackState,SharedTypes::PlaybackState)\0"
    "path\0playFile(const QString*)\0"
    "stopPlaying()\0"
};

void PlaybackModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PlaybackModel *_t = static_cast<PlaybackModel *>(_o);
        switch (_id) {
        case 0: _t->FileEnded(); break;
        case 1: _t->PlayingLocalFile(); break;
        case 2: _t->SecondHasPassed(); break;
        case 3: _t->StatusChanged((*reinterpret_cast< SharedTypes::PlaybackState(*)>(_a[1])),(*reinterpret_cast< SharedTypes::PlaybackState(*)>(_a[2]))); break;
        case 4: _t->playFile((*reinterpret_cast< const QString*(*)>(_a[1]))); break;
        case 5: _t->stopPlaying(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PlaybackModel::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PlaybackModel::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PlaybackModel,
      qt_meta_data_PlaybackModel, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PlaybackModel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PlaybackModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PlaybackModel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PlaybackModel))
        return static_cast<void*>(const_cast< PlaybackModel*>(this));
    return QObject::qt_metacast(_clname);
}

int PlaybackModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void PlaybackModel::FileEnded()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void PlaybackModel::PlayingLocalFile()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void PlaybackModel::SecondHasPassed()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void PlaybackModel::StatusChanged(SharedTypes::PlaybackState _t1, SharedTypes::PlaybackState _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE

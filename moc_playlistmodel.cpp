/****************************************************************************
** Meta object code from reading C++ file 'playlistmodel.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "playlistmodel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'playlistmodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PlayListModel[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,
      51,   14,   14,   14, 0x05,
      87,   14,   14,   14, 0x05,
     101,   14,   14,   14, 0x05,
     115,   14,   14,   14, 0x05,
     135,   14,   14,   14, 0x05,
     157,   14,   14,   14, 0x05,
     174,   14,   14,   14, 0x05,
     190,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
     203,   14,   14,   14, 0x0a,
     219,   14,   14,   14, 0x0a,
     235,   14,   14,   14, 0x0a,
     263,  252,   14,   14, 0x0a,
     297,  286,   14,   14, 0x0a,
     321,   14,   14,   14, 0x0a,
     343,  337,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_PlayListModel[] = {
    "PlayListModel\0\0CurrentTrackChanged(const QString*)\0"
    "CurrentModelChanged(PlayListModel*)\0"
    "NoNextTrack()\0NoPrevTrack()\0"
    "FileDoesNotExists()\0PlayListNameChanged()\0"
    "NewTracksAdded()\0PlayListEmpty()\0"
    "OutOfRange()\0playNextTrack()\0"
    "playPrevTrack()\0replayPlayList()\0"
    "RandomMode\0enableRandomMode(bool)\0"
    "RepeatMode\0enableRepeateMode(bool)\0"
    "startPlayback()\0track\0playTrack(int)\0"
};

void PlayListModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PlayListModel *_t = static_cast<PlayListModel *>(_o);
        switch (_id) {
        case 0: _t->CurrentTrackChanged((*reinterpret_cast< const QString*(*)>(_a[1]))); break;
        case 1: _t->CurrentModelChanged((*reinterpret_cast< PlayListModel*(*)>(_a[1]))); break;
        case 2: _t->NoNextTrack(); break;
        case 3: _t->NoPrevTrack(); break;
        case 4: _t->FileDoesNotExists(); break;
        case 5: _t->PlayListNameChanged(); break;
        case 6: _t->NewTracksAdded(); break;
        case 7: _t->PlayListEmpty(); break;
        case 8: _t->OutOfRange(); break;
        case 9: _t->playNextTrack(); break;
        case 10: _t->playPrevTrack(); break;
        case 11: _t->replayPlayList(); break;
        case 12: _t->enableRandomMode((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: _t->enableRepeateMode((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: _t->startPlayback(); break;
        case 15: _t->playTrack((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PlayListModel::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PlayListModel::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PlayListModel,
      qt_meta_data_PlayListModel, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PlayListModel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PlayListModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PlayListModel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PlayListModel))
        return static_cast<void*>(const_cast< PlayListModel*>(this));
    return QObject::qt_metacast(_clname);
}

int PlayListModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void PlayListModel::CurrentTrackChanged(const QString * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PlayListModel::CurrentModelChanged(PlayListModel * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PlayListModel::NoNextTrack()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void PlayListModel::NoPrevTrack()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void PlayListModel::FileDoesNotExists()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void PlayListModel::PlayListNameChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void PlayListModel::NewTracksAdded()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}

// SIGNAL 7
void PlayListModel::PlayListEmpty()
{
    QMetaObject::activate(this, &staticMetaObject, 7, 0);
}

// SIGNAL 8
void PlayListModel::OutOfRange()
{
    QMetaObject::activate(this, &staticMetaObject, 8, 0);
}
QT_END_MOC_NAMESPACE

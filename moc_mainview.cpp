/****************************************************************************
** Meta object code from reading C++ file 'mainview.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x05,
      35,    9,    9,    9, 0x05,
      63,    9,    9,    9, 0x05,
      80,    9,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
     112,    9,    9,    9, 0x08,
     136,  130,    9,    9, 0x08,
     150,  130,    9,    9, 0x08,
     222,  202,    9,    9, 0x08,
     290,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainView[] = {
    "MainView\0\0pathDropped(QList<QUrl>)\0"
    "modelSignal(PlayListModel*)\0"
    "TogglePlayback()\0StartPlaybackOnActivePlaylist()\0"
    "newPlayListView()\0index\0closeTab(int)\0"
    "notifyPlayListManagerAboutActivePlayListChange(int)\0"
    "oldstatus,newstatus\0"
    "changeStatus(SharedTypes::PlaybackState,SharedTypes::PlaybackState)\0"
    "toggleButtonControl()\0"
};

void MainView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainView *_t = static_cast<MainView *>(_o);
        switch (_id) {
        case 0: _t->pathDropped((*reinterpret_cast< QList<QUrl>(*)>(_a[1]))); break;
        case 1: _t->modelSignal((*reinterpret_cast< PlayListModel*(*)>(_a[1]))); break;
        case 2: _t->TogglePlayback(); break;
        case 3: _t->StartPlaybackOnActivePlaylist(); break;
        case 4: _t->newPlayListView(); break;
        case 5: _t->closeTab((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->notifyPlayListManagerAboutActivePlayListChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->changeStatus((*reinterpret_cast< SharedTypes::PlaybackState(*)>(_a[1])),(*reinterpret_cast< SharedTypes::PlaybackState(*)>(_a[2]))); break;
        case 8: _t->toggleButtonControl(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainView::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainView,
      qt_meta_data_MainView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainView))
        return static_cast<void*>(const_cast< MainView*>(this));
    if (!strcmp(_clname, "Ui_MainWindow"))
        return static_cast< Ui_MainWindow*>(const_cast< MainView*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void MainView::pathDropped(QList<QUrl> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainView::modelSignal(PlayListModel * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MainView::TogglePlayback()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void MainView::StartPlaybackOnActivePlaylist()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}
QT_END_MOC_NAMESPACE

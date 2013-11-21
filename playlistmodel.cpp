/*
 * <one line to give the library's name and an idea of what it does.>
 * Copyright 2013  Marek Kochanowicz <sirherrbatka@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License or (at your option) version 3 or any later version
 * accepted by the membership of KDE e.V. (or its successor approved
 * by the membership of KDE e.V.), which shall act as a proxy
 * defined in Section 14 of version 3 of the license.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "playlistmodel.h"
#include <QDebug>
#include <cassert>
#include <memory>
#include "./maincontroler.h"
#include <qstringlist.h>
#include "./audiotrackmodel.h"
#include <QString>
#include <vector>
#include "./taghandler.h"


PlayListModel::PlayListModel(unsigned long long int key) :
    mKey(key)
{
    qDebug()<<"Playlist Model created";

//     connect(this, SIGNAL(CurrentTrackChanged(const QString*)), SLOT() );
    connect(this, SIGNAL(CurrentModelChanged(PlayListModel*)), MainControler::getMainControler(), SLOT(changeCurrentPlayList(PlayListModel*)));
    connect(this, SIGNAL(CurrentTrackChanged(const QString*)), MainControler::getMainControler(), SLOT(playFile(const QString*)));
    connect(this, SIGNAL(NoNextTrack()), this, SLOT(replayPlayList()));

}

PlayListModel::~PlayListModel()
{
    qDebug()<<"Play List model Is being destroyed";
}

long long unsigned int PlayListModel::getKey() const
{
    return mKey;
}

const QString* PlayListModel::getTrackPath(int tracknumber) const
{
    assert(tracknumber < mTracks.size() and tracknumber != 0);
    return (mTracks[tracknumber-1])->getPath();
}

PlayListModel* PlayListModel::getPlayListModel()
{
    return this;
}

const QString* PlayListModel::getPlayListName() const
{
    return &mPlayListName;
}

void PlayListModel::changePlayListName(const QString& name)
{
    mPlayListName = name;
}

void PlayListModel::enableRandomMode(bool RandomMode)
{
    mRandomMode = RandomMode;
}

void PlayListModel::enableRepeateMode(bool RepeatMode)
{
    mRepateMode = RepeatMode;
}

void PlayListModel::goToFirstTrack()
{
    mCurrentTrack = 0;
}

void PlayListModel::addTracks(const QStringList& paths)
{
    assert (!paths.empty()); //yes, assert. Make sure that you are actually passing any paths.

    foreach(QString path, paths)
    {
        mTracks.push_back(std::unique_ptr<AudioTrackModel>(new AudioTrackModel(path)));
    }
    emit NeedRefreshView();
}

void PlayListModel::playNextTrack()
{
    if (!playListChecks())
    {
        return;
    }
    if (mCurrentTrack >= mTracks.size() )
    {
        emit NoNextTrack();
        return;
    }
    ++mCurrentTrack;
    qDebug()<<"Playing Next track";
    startPlayback();
}

void PlayListModel::playPrevTrack()
{
    if (!playListChecks())
    {
        return;
    }
    if (mCurrentTrack == 0 )
    {
        emit NoPrevTrack();
        return;
    }
    --mCurrentTrack;
    qDebug()<<"Playing Prev track";
    startPlayback();
}

void PlayListModel::startPlayback()
{
    if (playListChecks() == false)
    {
        qDebug()<<"Playlist not usable";
        return;
    }
    if (mTracks[mCurrentTrack]->fileExists() == false)
    {
        qDebug()<<"File does not exists!";
        emit FileDoesNotExists();
        mTracks[mCurrentTrack].reset();
        mTracks.erase(mTracks.begin()+mCurrentTrack);
        emit NeedRefreshView();
        startPlayback();
        return;
    } else {
        emit CurrentTrackChanged(mTracks[mCurrentTrack]->getPath());
        emit CurrentModelChanged(this);
        emit NeedRefreshView();
        return;
    }
}

unsigned int PlayListModel::getPlayListSize() const
{
    return mTracks.size();
}

const QString* PlayListModel::getTrackName(int tracknumber) const
{
    return (mTracks[tracknumber])->getName();
}

bool PlayListModel::playListChecks()
{
    if (mTracks.empty())
    {
        emit PlayListEmpty();
        return false;
    }

    if (mCurrentTrack >= mTracks.size() )
    {
        emit NoNextTrack();
        return false;
    }
    return true;
}

void PlayListModel::playTrack(int track)
{
    mCurrentTrack = track;
    startPlayback();
}

const QString* PlayListModel::getCurrentTrackPath() const
{
    return (mTracks[mCurrentTrack])->getPath();
}

void PlayListModel::replayPlayList()
{
    mCurrentTrack = 0;
    startPlayback();
}

int PlayListModel::getCurrentTrack()
{
    return mCurrentTrack;
}

bool PlayListModel::getCurrent() const
{
    return mCurrent;
}

void PlayListModel::setCurrent(bool locCurrent)
{
    mCurrent = locCurrent;
}

void PlayListModel::requestRefresh()
{
 emit NeedRefreshView();
}

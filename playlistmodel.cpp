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
#include <algorithm>
#include <cassert>
#include <memory>
#include "./maincontroler.h"
#include <qstringlist.h>
#include "./audiotrackmodel.h"
#include <QString>
#include <vector>
#include <qt4/QtCore/qnamespace.h>
#include "./taghandler.h"
#include <Qt>
#include <algorithm>


PlayListModel::PlayListModel(unsigned long long int key) :
    mKey(key)
{
    qDebug()<<"Playlist Model created";

    connect(this, SIGNAL(CurrentModelChanged(PlayListModel*)), MainControler::getMainControler(), SLOT(changeCurrentPlayList(PlayListModel*)));
    connect(this, SIGNAL(CurrentTrackChanged(const QString&)), MainControler::getMainControler(), SLOT(playFile(const QString&)));
    connect(this, SIGNAL(NoNextTrack()), this, SLOT(replayPlayList()));
    connect(this, SIGNAL(NoPrevTrack()), this, SLOT(replayPlayList()));

}

PlayListModel::~PlayListModel()
{
    qDebug()<<"Play List model Is being destroyed";
}

PlayListModel& PlayListModel::operator=(const PlayListModel&& other)
{
    mKey = other.mKey;
    mTracks = other.mTracks;
    mCurrentTrack = other.mCurrentTrack;
    mRandomMode = other.mRandomMode;
    mPlayListName = other.mPlayListName;
    mCustomPlayListName = other.mCustomPlayListName;
    mCurrent = other.mCurrent;
    mTotalDuration = other.mTotalDuration;

    connect(this, SIGNAL(CurrentModelChanged(PlayListModel*)), MainControler::getMainControler(), SLOT(changeCurrentPlayList(PlayListModel*)));
    connect(this, SIGNAL(CurrentTrackChanged(const QString&)), MainControler::getMainControler(), SLOT(playFile(const QString&)));
    connect(this, SIGNAL(NoNextTrack()), this, SLOT(replayPlayList()));
    connect(this, SIGNAL(NoPrevTrack()), this, SLOT(replayPlayList()));
}

PlayListModel::PlayListModel(const PlayListModel&& other) :
    mKey(other.mKey),
    mTracks(other.mTracks),
    mCurrentTrack(other.mCurrentTrack),
    mRandomMode(other.mRandomMode),
    mPlayListName(other.mPlayListName),
    mCustomPlayListName(other.mCustomPlayListName),
    mCurrent(other.mCurrent),
    mTotalDuration(other.mTotalDuration)
{
    connect(this, SIGNAL(CurrentModelChanged(PlayListModel*)), MainControler::getMainControler(), SLOT(changeCurrentPlayList(PlayListModel*)));
    connect(this, SIGNAL(CurrentTrackChanged(const QString&)), MainControler::getMainControler(), SLOT(playFile(const QString&)));
    connect(this, SIGNAL(NoNextTrack()), this, SLOT(replayPlayList()));
    connect(this, SIGNAL(NoPrevTrack()), this, SLOT(replayPlayList()));
}


long long unsigned int PlayListModel::getKey() const
{
    return mKey;
}

QString PlayListModel::getTrackPath(int tracknumber) const
{
    assert(tracknumber < static_cast<int>(mTracks.size()) and tracknumber != 0);
    return (mTracks[tracknumber-1]).getPath();
}

const PlayListModel* PlayListModel::getPlayListModel()
{
    return this;
}

QString PlayListModel::getPlayListName() const
{
    return mPlayListName;
}

void PlayListModel::changePlayListName(const QString& name)
{
    mPlayListName = name;
}

void PlayListModel::enableRandomMode(bool RandomMode)
{
    mRandomMode = RandomMode;
}

inline void PlayListModel::goToFirstTrack()
{
    mCurrentTrack = 0;
}

void PlayListModel::addTracks(const QStringList& paths)
{
    assert (!paths.empty()); //yes, assert. Make sure that you are actually passing any paths.

    for(const auto &path : paths)
    {
        mTracks.emplace_back(path);
        mTotalDuration += (mTracks.rbegin())->getDuration();
    }
    generatePlayListName();
    sortPlayList();
    emit NeedRefreshView();
    MainControler::getMainControler()->requestTotalDurationLabelUpdate(mTotalDuration);
}

void PlayListModel::playNextTrack()
{
    if (static_cast<unsigned>(mCurrentTrack) >= mTracks.size() ) //silencing the warning.
    {
        emit NoNextTrack();
        return;
    }
    ++mCurrentTrack;
    qDebug()<<"Playing Next track";
    startPlayback(true);
}

void PlayListModel::playPrevTrack()
{
    if (!playListChecks())
    {
        return;
    }
    if (mCurrentTrack <= 0 ) //initial value for mCurrentTrack = -1. This way playlist initially does not display active track.
    {
        emit NoPrevTrack();
        return;
    }
    --mCurrentTrack;
    qDebug()<<"Playing Prev track";
    startPlayback(false); //Playlist checks already done
}

void PlayListModel::startPlayback(bool locRequestPlayListCheck = true)
{
    if (locRequestPlayListCheck)
    {
        if (playListChecks() == false)
        {
            qDebug()<<"Playlist not usable";
            return;
        }
    }
    if (mCurrentTrack == -1) //true for newly created playlist, without active track. If we reached the point when we start playback on such playlist, we should start from the begining (0);
    {
        mCurrentTrack = 0; //Sets to the begining.
    }
    if (mTracks[mCurrentTrack].fileExists() == false)
    {
        qDebug()<<"File does not exists!";
        emit FileDoesNotExists();
        mTracks.erase(mTracks.begin()+mCurrentTrack);
        emit NeedRefreshView();
        startPlayback();
        return;
    } else {
        emit CurrentTrackChanged(mTracks[mCurrentTrack].getPath());
        emit CurrentModelChanged(this);
        emit NeedRefreshView();
        return;
    }
}

unsigned int PlayListModel::getPlayListSize() const
{
    return mTracks.size();
}

QString PlayListModel::getTrackName(int tracknumber) const
{
    return (mTracks[tracknumber]).getName();
}

inline bool PlayListModel::playListChecks()
{
    if (mTracks.empty())
    {
        emit PlayListEmpty();
        return false;
    }

    if (static_cast<unsigned>(mCurrentTrack) >= mTracks.size() ) //static_cast silences the warning.
    {
        emit NoNextTrack();
        return false;
    }

    return true;
}

void PlayListModel::playTrack(unsigned int track)
{
    mCurrentTrack = track;
    startPlayback();
}

QString PlayListModel::getCurrentTrackPath() const
{
    return (mTracks[mCurrentTrack]).getPath();
}

void PlayListModel::replayPlayList()
{
    if (MainControler::getMainControler()->getRepeatMode())
    {
        mCurrentTrack = 0;
        startPlayback();
        return;
    } else {
        mCurrentTrack = -1;
        emit NeedRefreshView();
    }
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

void PlayListModel::sortPlayList()
{
    if(mCurrentTrack >= 0)
    {
        mTracks[mCurrentTrack].markAsCurrent(true);
    }

    std::sort(begin(mTracks), begin(mTracks), [](const AudioTrackModel& prev, const AudioTrackModel& next)->bool
    {
        if(0<(prev.getAlbum().compare(next.getAlbum()), Qt::CaseSensitive))
        {
            return true;
        }

        if(0>(prev.getAlbum().compare(next.getAlbum()), Qt::CaseSensitive))
        {
            return false;
        }

        if(prev.getDiscNumber()>next.getDiscNumber() and prev.getDiscNumber() != -1 and next.getDiscNumber() != -1 )
        {
            return false;
        }

        if(prev.getDiscNumber()<next.getDiscNumber() and prev.getDiscNumber() != -1 and next.getDiscNumber() != -1 )
        {
            return true;
        }

        if(prev.getTrackNumber()<next.getTrackNumber() )
        {
            return true;
        }

        if(prev.getTrackNumber()>next.getTrackNumber() )
        {
            return false;
        }
        return false; //silencing warning
    }); //lambda expression

    if (mCurrentTrack >= 0)
    {
        for(unsigned i = 0; i<mTracks.size(); ++i)
        {
            if (mTracks[i].isCurrent())
            {
                mCurrentTrack = i;
                break;
            }
        }
    }
}

int PlayListModel::getTrackNumber(int locTrack) const
{
    return mTracks[locTrack].getTrackNumber();
}

QString PlayListModel::getArtist(int locTrack) const
{
    return mTracks[locTrack].getArtist();
}

void PlayListModel::clearMe()
{
    mTracks.erase(mTracks.begin(), mTracks.end());
    mCurrentTrack = -1;
    generatePlayListName();
    mTotalDuration = 0;
    emit NeedRefreshView();
    MainControler::getMainControler()->requestTotalDurationLabelUpdate(mTotalDuration);
}

void PlayListModel::generatePlayListName(bool onlyUpdate)
{
    if (onlyUpdate)
    {
        emit(NeedRefreshPlayListName(mPlayListName));
        return;
    }
    QString locPlayListName("Playlist");
    if (!mCustomPlayListName)
    {
        bool locGeneratedNewName(true);
        if(mTracks.size() > 1)
        {
            auto prev = begin(mTracks);
            for(auto next = begin(mTracks) + 1; next != end(mTracks); ++next)
            {
                if ( (next->getAlbum() != prev->getAlbum()) or prev->getAlbum().isEmpty())
                {
                    locGeneratedNewName = false;
                    break;
                } else {
                    ++prev;
                }
            }
        } else if(mTracks.size() == 1 and begin(mTracks)->getAlbum().isEmpty())
        {
            locGeneratedNewName = false;
        } else if(mTracks.empty())
        {
            locGeneratedNewName = false;
        }

        if (locGeneratedNewName)
        {
            locPlayListName = begin(mTracks)->getAlbum();
        }
    }
    mPlayListName = locPlayListName;
    emit(NeedRefreshPlayListName(mPlayListName));
}

void PlayListModel::calculateTotalDuration()
{
    mTotalDuration = 0;
    for(auto& each : mTracks)
    {
        mTotalDuration += each.getDuration();
    }
}

long long unsigned int PlayListModel::getTotalDuration()
{
    return mTotalDuration;
}

void PlayListModel::setTrackNumber(int locTrack)
{
    mCurrentTrack = locTrack;
    emit requestRefresh();
}

void PlayListModel::playSelected()
{
    emit PlaySelected();
}

QStringList PlayListModel::getPaths()
{
    QStringList Paths;
    for (auto &each : mTracks)
    {
        Paths<<(each.getPath());
    }
    return Paths;
}

void PlayListModel::removeSelected()
{
    emit RemoveSelected();
}

void PlayListModel::removeTrack(int track) //does not work
{
    assert(track >= 0);
    if (not mTracks.empty() and static_cast<int>(track) < mTracks.size())
    {
        mTracks.erase(begin(mTracks) + track);
        emit NeedRefreshView();
    }
}

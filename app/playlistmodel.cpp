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

#include <algorithm>
#include <cassert>
#include <memory>
#include <vector>

#include <QDebug>
#include <qstringlist.h>
#include <QString>
#include <qt4/QtCore/qnamespace.h>
#include <Qt>

#include "./maincontroler.h"
#include "./audiotrackmodel.h"
#include "settingsmanager.h"

PlayListModel::PlayListModel(unsigned long long int key) :
    mKey(key)
{
    connect(this, SIGNAL(CurrentModelChanged(PlayListModel*)), MainControler::getMainControler(),
            SLOT(changeCurrentPlayList(PlayListModel*)));
}

PlayListModel::~PlayListModel()
{
}

PlayListModel& PlayListModel::operator=(PlayListModel&& other)
{
    mKey = other.mKey;
    mRandomMode = other.mRandomMode;
    mPlayListName = std::move(other.mPlayListName);
    mCustomPlayListName = other.mCustomPlayListName;
    mCurrent = other.mCurrent;
    mTotalDuration = other.mTotalDuration;
    mTracksVector = std::move(other.mTracksVector);
    mCurrentTrack = std::move(other.mCurrentTrack);

    connect(this, SIGNAL(CurrentModelChanged(PlayListModel*)), MainControler::getMainControler(),
            SLOT(changeCurrentPlayList(PlayListModel*)));
    return *this;
}

PlayListModel::PlayListModel(PlayListModel&& other) :
    mKey(other.mKey),
    mRandomMode(other.mRandomMode),
    mPlayListName(std::move(other.mPlayListName)),
    mCustomPlayListName(other.mCustomPlayListName),
    mCurrent(other.mCurrent),
    mTotalDuration(other.mTotalDuration),
    mTracksVector(std::move(other.mTracksVector)),
    mCurrentTrack(std::move(other.mCurrentTrack))
{
    connect(this, SIGNAL(CurrentModelChanged(PlayListModel*)), MainControler::getMainControler(),
            SLOT(changeCurrentPlayList(PlayListModel*)));
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

void PlayListModel::addTracks(const QList<QUrl>& paths)
{
    assert (!paths.empty()); //yes, assert. Make sure that you are actually passing any paths.
    for (auto &each : paths)
    {
        mTracksVector.emplace(mTracksVector.end(), AudioTrackModel(each, this));
        mTotalDuration += mTracksVector.rbegin()->getDuration();
    }
    generatePlayListName();
    sortPlayList();
    emit NeedRefreshView();
    MainControler::getMainControler()->requestTotalDurationLabelUpdate(mTotalDuration);
}

void PlayListModel::addTracks(const QStringList & paths)
{
    assert (!paths.empty()); //yes, assert. Make sure that you are actually passing any paths.

    for (auto &each : paths)
    {
        mTracksVector.emplace(mTracksVector.end(), AudioTrackModel(QUrl(each), this));
        mTotalDuration += mTracksVector.rbegin()->getDuration();
    }
    generatePlayListName();
    sortPlayList();
    emit NeedRefreshView();
    MainControler::getMainControler()->requestTotalDurationLabelUpdate(mTotalDuration);
}

void PlayListModel::playNextTrack()
{
    if (mCurrentTrack < mTracksVector.size())
    {
        mTracksVector[mCurrentTrack].setAsPlayed(false);
    }
    mCurrentTrack += 1;
    startPlayback(true);
}

void PlayListModel::playPrevTrack()
{
    if (mCurrentTrack <= 0)
    {
        mCurrentTrack = 0;
        startPlayback(true);
        return;
    } else if (mCurrentTrack < mTracksVector.size()) {
        mTracksVector[mCurrentTrack].setAsPlayed(false);
    }
    --mCurrentTrack;
    startPlayback(true);
    return;
}

void PlayListModel::startPlayback(bool locRequestPlayListCheck = true)
{
    if (locRequestPlayListCheck)
    {
        if (playListChecks() == false)
        {
            return;
        }
    }

    if (mCurrentTrack == -1)
    {
        mCurrentTrack += 1;
        startPlayback(false);
        return;
    }

    if (mCurrentTrack >= (int)(mTracksVector.size()) )
    {
        replayPlayList(false);
        return;
    }

    if (mTracksVector[mCurrentTrack].fileExists() == false)
    {
        emit FileDoesNotExists();
        deleteCurrentTrackModel();
        mCurrentTrack += 1;
        startPlayback(true);
        return;
    } else {
        mTracksVector.at(mCurrentTrack).setAsPlayed(true);
        mTracksVector.at(mCurrentTrack).playThisTrack();
        emit NeedRefreshView();
        emit CurrentModelChanged(this);
        emit CurrentTrackChanged();
        return;
    }
    emit CurrentTrackChanged();
}

void PlayListModel::deleteCurrentTrackModel()
{
    if (mCurrentTrack == -1)
    {
        return;
    }

    mTracksVector.erase(mTracksVector.begin()+mCurrentTrack);
    generatePlayListName(false);
    emit NeedRefreshView();
    if (mTracksVector.empty())
    {
        generatePlayListName();
    }
}

unsigned int PlayListModel::getPlayListSize() const
{
    return mTracksVector.size();
}

inline bool PlayListModel::playListChecks()
{
    if (mTracksVector.empty())
    {
        emit PlayListEmpty();
        return false;
    }

    return true;
}

void PlayListModel::replayPlayList(bool skipModeCheck)
{
    if (SettingsManager::getSettingsManager()->getRepeatMode() or skipModeCheck)
    {
        mCurrentTrack = 0;
        startPlayback(true);
        return;
    } else {
        MainControler::getMainControler()->stopPlayback();
    }
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
    std::sort(mTracksVector.begin(), mTracksVector.end());
}

void PlayListModel::clearMe()
{
    mTracksVector.erase(mTracksVector.begin(), mTracksVector.end());
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
        if(mTracksVector.size() > 1)
        {
            auto prev(mTracksVector.begin());
            auto next(mTracksVector.begin() +1);
            while(next != mTracksVector.end())
            {
                if(next->getAlbum() != prev->getAlbum() or prev->getAlbum().isEmpty())
                {
                    locGeneratedNewName  = false;
                    break;
                } else {
                    ++prev;
                    ++next;
                }
            }
        } else if(mTracksVector.size() == 1 and mTracksVector.begin()->getAlbum().isEmpty())
        {
            locGeneratedNewName = false;
        } else if(mTracksVector.empty())
        {
            locGeneratedNewName = false;
        }

        if (locGeneratedNewName)
        {
            locPlayListName = mTracksVector.begin()->getAlbum();
        }
    }
    mPlayListName = locPlayListName;
    emit(NeedRefreshPlayListName(mPlayListName));
}

void PlayListModel::calculateTotalDuration()
{
    mTotalDuration = 0;
    for (auto &each : mTracksVector)
    {
        mTotalDuration += each.getDuration();
    }
}

long long unsigned int PlayListModel::getTotalDuration() const
{
    return mTotalDuration;
}

void PlayListModel::playSelected()
{
    emit PlaySelected();
}

QStringList PlayListModel::getPaths() const
{
    QStringList Paths;
    for (auto &each : mTracksVector)
    {
        Paths<<each.getPath();
    }
    return Paths;
}

void PlayListModel::removeSelected()
{
    emit RemoveSelected();
}

void PlayListModel::deleteTrackModel(unsigned int number)
{
    assert(!mTracksVector.empty());
    if (mCurrentTrack == number)
    {
        deleteCurrentTrackModel();
        return;
    }
    mTracksVector.erase(mTracksVector.begin()+number);
    if (mTracksVector.empty())
    {
        generatePlayListName();
    }
}

void PlayListModel::changeCurrentAudioTrackModel(unsigned int number)
{
    if (mCurrentTrack < mTracksVector.size())
    {
        mTracksVector[mCurrentTrack].setAsPlayed(false);
    }
    mCurrentTrack = number;
    if (mCurrentTrack < mTracksVector.size())
    {
        mTracksVector[mCurrentTrack].setAsPlayed(true);
    }
}

void PlayListModel::clearCurrentTrack()
{
    if (mCurrentTrack < mTracksVector.size())
    {
        mTracksVector[mCurrentTrack].setAsPlayed(false);
    }
    mCurrentTrack = -1;
    emit CurrentTrackChanged();
    emit NeedRefreshView();
}

void PlayListModel::updateCurrentPlayListModel()
{
    emit CurrentModelChanged(this);
}

void PlayListModel::setNewCurrent(unsigned int number)
{
    if (mCurrentTrack < mTracksVector.size())
    {
        mTracksVector[mCurrentTrack].setAsPlayed(false);
    }
    mCurrentTrack = number;
}

const long long unsigned int PlayListModel::getKey() const
{
    return mKey;
}

const AudioTrackModel& PlayListModel::getAudioTrackModel(unsigned int number) const
{
    return mTracksVector.at(number);
}

int PlayListModel::getCurrentTrackNumber() const
{
    return mCurrentTrack;
}

void PlayListModel::addStream()
{
    
}
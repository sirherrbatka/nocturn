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
#include <Qt>
#include <algorithm>


PlayListModel::PlayListModel(unsigned long long int key) :
    mKey(key)
{
    mCurrentTrack = mTracks.end();
    connect(this, SIGNAL(CurrentModelChanged(PlayListModel*)), MainControler::getMainControler(), SLOT(changeCurrentPlayList(PlayListModel*)));
}

PlayListModel::~PlayListModel()
{
    mCurrentTrack = mTracks.end();
}

PlayListModel& PlayListModel::operator=(PlayListModel&& other)
{
    mKey = other.mKey;
    mRandomMode = other.mRandomMode;
    mPlayListName = std::move(other.mPlayListName);
    mCustomPlayListName = other.mCustomPlayListName;
    mCurrent = other.mCurrent;
    mTotalDuration = other.mTotalDuration;
    mTracks = std::move(other.mTracks);
    mCurrentTrack = std::move(other.mCurrentTrack);
    mFirstTrack = std::move(other.mFirstTrack);
    mLastTrack = std::move(other.mLastTrack);

    connect(this, SIGNAL(CurrentModelChanged(PlayListModel*)), MainControler::getMainControler(), SLOT(changeCurrentPlayList(PlayListModel*)));
    return *this;
}

PlayListModel::PlayListModel(PlayListModel&& other) :
    mKey(other.mKey),
    mRandomMode(other.mRandomMode),
    mPlayListName(std::move(other.mPlayListName)),
    mCustomPlayListName(other.mCustomPlayListName),
    mCurrent(other.mCurrent),
    mTotalDuration(other.mTotalDuration),
    mTracks(std::move(other.mTracks)),
    mCurrentTrack(std::move(other.mCurrentTrack)),
    mFirstTrack(std::move(other.mFirstTrack)),
    mLastTrack(std::move(other.mLastTrack))
{
    connect(this, SIGNAL(CurrentModelChanged(PlayListModel*)), MainControler::getMainControler(), SLOT(changeCurrentPlayList(PlayListModel*)));
}


long long unsigned int PlayListModel::getKey() const
{
    return mKey;
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

void PlayListModel::addTracks(const QList<QUrl>& paths)
{
    assert (!paths.empty()); //yes, assert. Make sure that you are actually passing any paths.
    for (auto &each : paths)
    {
        mTracks.emplace(mTrackKey, AudioTrackModel(each, this));
        ++mTrackKey;
        mTotalDuration += mTracks.rbegin()->second.getDuration();
    }
    sortPlayList();
    generatePlayListName();
//     debugOrder();
    emit NeedRefreshView();
    MainControler::getMainControler()->requestTotalDurationLabelUpdate(mTotalDuration);
    mCurrentTrack = mTracks.end();
}

void PlayListModel::addTracks(const QStringList & paths)
{
    assert (!paths.empty()); //yes, assert. Make sure that you are actually passing any paths.

//     bool noCurrent = false;
//     if (mCurrentTrack == mTracks.end())
//     {
//         noCurrent = true;
//     }

    for (auto &each : paths)
    {
        mTracks.emplace(mTrackKey, AudioTrackModel(QUrl(each), this));
        ++mTrackKey;
        mTotalDuration += mTracks.rbegin()->second.getDuration();
    }
    sortPlayList();
    generatePlayListName();
//     debugOrder();
    emit NeedRefreshView();
    MainControler::getMainControler()->requestTotalDurationLabelUpdate(mTotalDuration);
//     if (noCurrent)
//     {
    mCurrentTrack = mTracks.end();
//     }
}

void PlayListModel::playNextTrack()
{
    if (mCurrentTrack != mTracks.end() and not mTracks.empty())
    {
        auto iterator = mCurrentTrack->second.getNextTrack();
        if (iterator != mTracks.end())
        {
            if(mCurrentTrack == mLastTrack)
            {
                replayPlayList(false);
                return;
            } else {
                iterator->second.playThisTrack();
            }
        } else {
            replayPlayList(false);
        }
    }
    return;
}

void PlayListModel::playPrevTrack()
{
    if (mCurrentTrack != mTracks.end() and not mTracks.empty())
    {
        auto iterator = mCurrentTrack->second.getPrevTrack();
        if (iterator != mTracks.end())
        {
            iterator->second.playThisTrack();
        } else {
            replayPlayList(false);
        }
    }
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

    if (mCurrentTrack == mTracks.end() )
    {
        replayPlayList(false);
        return;
    }


    if (mCurrentTrack->second.fileExists() == false)
    {
        emit FileDoesNotExists();
        deleteCurrentTrackModel();
        startPlayback();
        return;
    } else {
        mCurrentTrack->second.playThisTrack();
        emit CurrentModelChanged(this);
        return;
    }
}

void PlayListModel::deleteCurrentTrackModel()
{
    if (mCurrentTrack != mTracks.end())
    {

        if (mCurrentTrack == mFirstTrack)
        {
            mFirstTrack = mCurrentTrack->second.getNextTrack();
        }

        if (mCurrentTrack == mLastTrack)
        {
            mLastTrack = mCurrentTrack->second.getPrevTrack();
        }

        auto tmpnewcurrent = mCurrentTrack;
        mCurrentTrack = tmpnewcurrent->second.getNextTrack();
        deleteTrackModel(tmpnewcurrent);
        mCurrentTrack->second.playThisTrack();
    }

    mAddingIterator = mTracks.end();
}

unsigned int PlayListModel::getPlayListSize() const
{
    return mTracks.size();
}

inline bool PlayListModel::playListChecks()
{
    if (mTracks.empty())
    {
        emit PlayListEmpty();
        return false;
    }

    return true;
}

void PlayListModel::replayPlayList(bool skipModeCheck = false)
{
    clearCurrentTrack();
    if (MainControler::getMainControler()->getRepeatMode() or skipModeCheck)
    {
        mCurrentTrack = mFirstTrack;
        if (mCurrentTrack != mTracks.end() and playListChecks())
        {
            mCurrentTrack->second.playThisTrack();
        }
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
    mFirstTrack = mTracks.begin();
    mLastTrack = mTracks.begin();

    for (auto each = mTracks.begin(); each != mTracks.end(); ++each)
    {
        delinkModel(each);
    }

    for (auto each = mTracks.begin(); each != mTracks.end(); ++each)
    {
//         qDebug()<<each->second.getPath();
        auto current = mFirstTrack;
        auto next = current->second.getNextTrack();
        auto prev = current->second.getPrevTrack();
        if (each != current)
        {
            if (next == mTracks.end() and prev == mTracks.end()) //first iteration
            {
                if(each->second == current->second)
                {
                    linkTwo(current, each);
                    mFirstTrack = current;
                    mLastTrack = each;
                    continue;
                }
                if(each->second < current->second)
                {
                    linkTwo(each, current);
                    mFirstTrack = each;
                    mLastTrack = current;
                    continue;
                }
                if (current->second < each->second)
                {
                    linkTwo(current, each);
                    mFirstTrack = current;
                    mLastTrack = each;
                    continue;
                }
            }
        }

        while (true)
        {
            if(each != current)
            {
                if (current->second == each->second) //when no tag is present, mostly
                {
                    if (next == mTracks.end())
                    {
                        linkTwo(current, each);
                        if (current == mLastTrack)
                        {
                            mLastTrack = each;
                        }
                        break;
                    }
                }
                if (next != mTracks.end() and prev == mTracks.end())
                {
                    if (each->second < current->second)
                    {
//                         qDebug()<<"While loop link before current. 1";
                        linkTwo(each, current);
                        if (current == mFirstTrack)
                        {
                            each->second.storePrev(mTracks.end());
                            mFirstTrack = each;
                        }
                        break;
                    }
                    if ((current->second < each->second) and (each->second < next->second))
                    {
//                         qDebug()<<"While loop link after current. 2";
                        linkThree(current, each, next);
                        break;
                    }
                }
                if (next == mTracks.end() and prev != mTracks.end())
                {
                    if (each->second < current->second and prev->second < each->second)
                    {
//                         qDebug()<<"While loop link before current. 2";
                        linkThree(prev, each, current);
                        break;
                    }
                    if (current->second < each->second)
                    {
//                         qDebug()<<"While loop link after current. 2";
                        linkTwo(current, each);
                        if (current == mLastTrack)
                        {
                            each->second.storeNext(mTracks.end());
                            mLastTrack = each;
                        }
                        break;
                    }
                }
                if (next != mTracks.end() and prev != mTracks.end())
                {
                    if (each->second < current->second and prev->second < each->second)
                    {
//                         qDebug()<<"While dual loop.";
                        linkThree(prev, each, current);
                        break;
                    }
                    if (current->second < each->second and each->second < next->second)
                    {
//                         qDebug()<<"While dual loop 2.";
                        linkThree(current, each, next);
                        break;
                    }
                }
            }
            if(next == mTracks.end())
            {
                break;
            } else {
//                 qDebug()<<"Moving current.";
                current = next;
                prev = current->second.getPrevTrack();
                next = current->second.getNextTrack();
            }
        }
    }
    mAddingIterator = mFirstTrack;
}

void PlayListModel::clearMe()
{
    mTracks.erase(mTracks.begin(), mTracks.end());
    mCurrentTrack = mTracks.end();
    mAddingIterator = mTracks.end();
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
            auto prev = mTracks.begin();
            auto next = mTracks.begin();
            ++next;
            while(next != mTracks.end())
            {
                if(next->second.getAlbum() != prev->second.getAlbum() or prev->second.getAlbum().isEmpty())
                {
                    locGeneratedNewName  = false;
                    break;
                } else {
                    ++prev;
                    ++next;
                }
            }
        } else if(mTracks.size() == 1 and mTracks.begin()->second.getAlbum().isEmpty())
        {
            locGeneratedNewName = false;
        } else if(mTracks.empty())
        {
            locGeneratedNewName = false;
        }

        if (locGeneratedNewName)
        {
            locPlayListName = mTracks.begin()->second.getAlbum();
        }
    }
    mPlayListName = locPlayListName;
    emit(NeedRefreshPlayListName(mPlayListName));
}

void PlayListModel::calculateTotalDuration()
{
    mTotalDuration = 0;
    for (auto &each : mTracks)
    {
        mTotalDuration += each.second.getDuration();
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

QStringList PlayListModel::getPaths()
{
    QStringList Paths;
    for (auto &each : mTracks)
    {
        Paths<<each.second.getPath();
    }
    return Paths;
}

void PlayListModel::removeSelected()
{
    emit RemoveSelected();
}

void PlayListModel::deleteTrackModel(const std::map< unsigned long long, AudioTrackModel >::iterator& track) //does not work
{
    if (mCurrentTrack == track)
    {
        deleteCurrentTrackModel();
        return;
    }
    assert(!mAudioTrackModels.empty());
    linkTwo( track->second.getPrevTrack(), track->second.getNextTrack() );
    mTracks.erase(track);
    mAddingIterator = mTracks.end();
}

void PlayListModel::playCurrentTrack()
{
    if (mCurrentTrack != mTracks.end())
    {
        mCurrentTrack->second.playThisTrack();
    }
}

std::map< unsigned long long, AudioTrackModel >::iterator PlayListModel::getFirstAudioTrackModel() const
{
    return mFirstTrack;
}

std::map< unsigned long long, AudioTrackModel >::iterator PlayListModel::getLastAudioTrackModel() const
{
    return mLastTrack;
}

bool PlayListModel::modelsToAdd()
{
    if (mAddingIterator == mTracks.end() or mTracks.empty())
    {
        return false;
    }

    return true;
}

std::map< unsigned long long, AudioTrackModel >::iterator PlayListModel::getAudioTrackModel()
{
    assert(mAddingIterator != mAudioTrackModels.end());
    auto resoult = mAddingIterator;
    mAddingIterator = mAddingIterator->second.getNextTrack();
    return resoult;
}

void PlayListModel::changeCurrentAudioTrackModel(const std::map< unsigned long long, AudioTrackModel >::iterator& newcurrent)
{
    if (mCurrentTrack != mTracks.end())
    {
        mCurrentTrack->second.setAsPlayed(false);
    }
    mCurrentTrack = newcurrent;
    if (mCurrentTrack != mTracks.end())
    {
        mCurrentTrack->second.setAsPlayed(true);
    }
}

void PlayListModel::resetLooper()
{
    mAddingIterator = mFirstTrack;
}

void PlayListModel::clearCurrentTrack()
{
    if (mCurrentTrack != mTracks.end())
    {
        mCurrentTrack->second.setAsPlayed(false);
    }
    mCurrentTrack = mTracks.end();
    mAddingIterator = mTracks.end();
}


void PlayListModel::delinkModel(const std::map< unsigned long long, AudioTrackModel >::iterator& iterator)
{
    iterator->second.storeNext(mTracks.end());
    iterator->second.storePrev(mTracks.end());
}

void PlayListModel::linkTwo(const std::map< unsigned long long, AudioTrackModel >::iterator& iterator1, const std::map< unsigned long long, AudioTrackModel >::iterator& iterator2)
{
    iterator1->second.storeNext(iterator2);
    iterator2->second.storePrev(iterator1);
}

void PlayListModel::linkThree(const std::map< unsigned long long, AudioTrackModel >::iterator& iterator1, const std::map< unsigned long long, AudioTrackModel >::iterator& iterator2, const std::map< unsigned long long, AudioTrackModel >::iterator& iterator3)
{
    iterator1->second.storeNext(iterator2);
    iterator2->second.storePrev(iterator1);
    iterator2->second.storeNext(iterator3);
    iterator3->second.storePrev(iterator2);
}

void PlayListModel::updateCurrentPlayListModel()
{
    emit CurrentModelChanged(this);
}

void PlayListModel::debugOrder()
{
    qDebug()<<"\n";
    resetLooper();
    while(modelsToAdd())
    {
        qDebug()<<getAudioTrackModel()->second.getPath();
    }
    qDebug()<<"The First track is: "<<mFirstTrack->second.getPath();
    qDebug()<<"The Last track is: "<<mLastTrack->second.getPath();
    resetLooper();
}

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

#include "playlistmanager.h"

#include <cassert>
#include <utility>
#include <iostream>

#include <QUrl>
#include <QDebug>
#include <QDir>
#include <QFileInfoList>
#include <QFileInfo>

#include "maincontroler.h"
#include "playlistmodelfilehandler.h"
#include "audiotrackmodel.h"
#include "settingsmanager.h"
#include "playlistmodel.h"

PlayListManager::PlayListManager() :
mAudioFilePattern(".*.mp4$|.*.mp3$|.*.ogg$|.*.wav$|.*.flac$|.*.mpc$|.*.ape$|.*.m4a$", Qt::CaseInsensitive)
{
    connect(SettingsManager::getSettingsManager(), SIGNAL(ConfigurationUpdated()), this, SLOT(currentSongChanged()));
}

PlayListManager::~PlayListManager()
{
}

void PlayListManager::addFilesToActivePlayList(const QList< QUrl >& locFiles)
{
    QList<QUrl> locPaths;
    foreach(QUrl url, locFiles)
    {
        QDir dir(url.path());
        if (dir.exists())
        {
            locPaths = locPaths + scanDirectory(dir);
        } else {
            if (isSupportedFile(url.path()))
            {
                locPaths.push_back(std::move(url));
            }
        }
    }

    if (!locPaths.empty())
    {
        mActivePlayList->addTracks(locPaths);
    }
}

void PlayListManager::addFilesToPlaylist(const QString& locpath, PlayListModel* PlayList)
{

    QList<QUrl> locPaths;
    QDir dir(locpath);
    if (dir.exists())
    {
        locPaths = locPaths + scanDirectory(dir);
    } else if (isSupportedFile(locpath))
    {
        locPaths << locpath;
    }

    if (!locPaths.empty())
    {
        PlayList->addTracks(locPaths);
    }
}


PlayListModel* PlayListManager::getCurrentModel() const
{
    return mCurrentPlayList;
}


void PlayListManager::changeActivePlaylist(PlayListModel * locPlayList)
{
    mActivePlayList = locPlayList;
    if (!mCurrentPlayList)
    {
        mCurrentPlayList = locPlayList;
        qDebug()<<"Changing current playlist";
    }
    MainControler::getMainControler()->requestTotalDurationLabelUpdate(mActivePlayList->getTotalDuration());
    emit ActivePlayListChanged();
}

PlayListModel* PlayListManager::newPlayList()
{
    ++mNewKey;
    PlayListModel* locPlayList = &(mPlayLists.emplace(mNewKey, PlayListModel(mNewKey)).first->second);
    if (mPlayLists.size() == 1)
    {
        changeCurrentPlaylist(locPlayList);
        changeActivePlaylist(locPlayList);
    }
    return locPlayList;
}

void PlayListManager::deletePlayList(long long unsigned int locKey)
{
    auto it = mPlayLists.find(locKey);
    if (locKey == mCurrentPlayList->getKey())
    {
        if (mActivePlayList)
        {
            mCurrentPlayList = mActivePlayList;
        } else {
            mCurrentPlayList = nullptr;
        }
    }
    mPlayLists.erase(it);
}

QList<QUrl> PlayListManager::scanDirectory(const QDir & dir)
{
    QList <QUrl> locFiles;
    const QFileInfoList list = dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    foreach(const QFileInfo & info, list)
    {
        if(info.isFile())
        {
            if (isSupportedFile(info.absoluteFilePath()))
            {
                locFiles << info.absoluteFilePath();
            }
        } else if (info.isDir()) {
            locFiles = locFiles + scanDirectory(info.absoluteFilePath());
        }
    }
    return locFiles;
}

inline bool PlayListManager::isSupportedFile(const QString& path)
{
    return isAudioFile(path);
}

inline bool PlayListManager::isAudioFile(const QString& path)
{
    return path.contains(mAudioFilePattern);
}

void PlayListManager::changeCurrentPlaylist(PlayListModel* locPlayList)
{
    if (mCurrentPlayList)
    {
        mCurrentPlayList->setCurrent(false);
    }
    locPlayList->setCurrent(true);
    mCurrentPlayList = locPlayList;
    connect(mCurrentPlayList, SIGNAL(CurrentTrackChanged()), this, SLOT(currentSongChanged()));
}

void PlayListManager::fileEnded()
{
    if (!mCurrentPlayList)
    {
        mCurrentPlayList = mActivePlayList;
    }
    mCurrentPlayList->playNextTrack();
}

void PlayListManager::startPlayback()
{
    changeCurrentPlaylist(mActivePlayList);
    mCurrentPlayList->startPlayback(true);
}

void PlayListManager::playNextTrack()
{
    if (!mCurrentPlayList)
    {
        mCurrentPlayList = mActivePlayList;
    }
    mCurrentPlayList->playNextTrack();
}

void PlayListManager::playPrevTrack()
{
    if (!mCurrentPlayList)
    {
        mCurrentPlayList = mActivePlayList;
    }
    mCurrentPlayList->playPrevTrack();
}

void PlayListManager::clearActivePlayList()
{
    mActivePlayList->clearMe();
}

long long unsigned int PlayListManager::getTotalDurationOfActivePlaylist()
{
    return mActivePlayList->getTotalDuration();
}

void PlayListManager::clearCurrentTrack()
{
    assert(mCurrentPlayList);
    mCurrentPlayList->clearCurrentTrack();
}

void PlayListManager::playSelected()
{
    mActivePlayList->playSelected();
}

void PlayListManager::setRepeatMode()
{
    mRepeateMode = !mRepeateMode;
}

bool PlayListManager::getRepeatMode() const
{
    return mRepeateMode;
}

void PlayListManager::autoLoadPath(const QString& path)
{
    PlayListModel* tmpPlayList = newPlayList();
    addFilesToPlaylist(path, tmpPlayList);
    MainControler::getMainControler()->relayPlayListModel(tmpPlayList);
    changeActivePlaylist(tmpPlayList);
    changeCurrentPlaylist(tmpPlayList);
    startPlayback();
}

void PlayListManager::autoLoadPath(const QStringList& paths)
{
    PlayListModel* tmpPlayList = newPlayList();
    for (auto &path : paths)
    {
        addFilesToPlaylist(path, tmpPlayList);
    }
    MainControler::getMainControler()->relayPlayListModel(tmpPlayList);
    changeActivePlaylist(tmpPlayList);
    changeCurrentPlaylist(tmpPlayList);
    startPlayback();
}


void PlayListManager::savePlayListFiles()
{
    PlayListModelFileHandler saver;
    for (auto &each : mPlayLists)
    {
        saver.savePlayListFile(each.second.getPaths());
    }
}

void PlayListManager::restorePlayListFromFiles()
{
    std::vector<PlayListModel*> PlayLists;
    PlayListModelFileHandler loader;
    for (auto &each : loader.loadPlayListFile())
    {
        QStringList paths;
        PlayLists.push_back(newPlayList());
        for (auto &path : each)
        {
            paths<<path;
        }
        PlayListModel* tmpPlayList = *(PlayLists.rbegin());
        if (!(paths.empty()))
        {
            tmpPlayList->addTracks(paths);
        }
    }
    MainControler::getMainControler()->relayPlayListModel(PlayLists);
    loader.removePlayListFile();
}

void PlayListManager::removeSelected()
{
    mActivePlayList->removeSelected();
}

void PlayListManager::currentSongChanged()
{
    if (mCurrentPlayList)
    {
	int number = mCurrentPlayList->getCurrentTrackNumber();
        if (number != -1)
        {
            emit CurrentSongChanged(mCurrentPlayList->getAudioTrackModel(number).getName());
        } else {
            emit CurrentSongChanged("");
        }
    }
}

PlayListModel* PlayListManager::getActiveModel() const
{
  return mActivePlayList;
}

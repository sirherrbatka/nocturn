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
#include <QUrl>
#include <cassert>
#include <utility>
#include <QDebug>
#include "./playlistmodel.h"
#include <QDir>
#include <QFileInfoList>
#include <QFileInfo>
#include <iostream>

PlayListManager::PlayListManager()
{
}

PlayListManager::~PlayListManager()
{
    for (auto it = mPlayLists.begin(); it != mPlayLists.end(); ++it)
    {
        delete it->second;
        mPlayLists.erase(it);
    }
}

void PlayListManager::addFilesToActivePlaylist(QList< QUrl >& locFiles)
{
    QStringList locPaths;
    foreach(QUrl url, locFiles)
    {
        QString locpath = url.path();
        QDir dir(locpath);
        if (dir.exists())
        {
            locPaths = locPaths + scanDirectory(dir);
        } else {
            if (isSupportedFile(locpath))
            {
                locPaths << locpath;
            }
        }
    }

    if (!locPaths.empty())
    {
        mActivePlayList->addTracks(locPaths);
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
}

PlayListModel* PlayListManager::newPlayList()
{
    ++mNewKey;
    PlayListModel* locPlayList = new PlayListModel(mNewKey);
    mPlayLists.insert(std::pair<unsigned long long int, PlayListModel*>(mNewKey, locPlayList));
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
        qDebug()<<"Deleting current playlist";
        mCurrentPlayList = nullptr;
    }
    delete it->second;
    mPlayLists.erase(it);
}

QStringList PlayListManager::scanDirectory(const QDir & dir)
{
    QStringList locFiles;
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

bool PlayListManager::isSupportedFile(const QString& path)
{
    qDebug()<<path;
    return isAudioFile(path);
}

bool PlayListManager::isAudioFile(const QString& path)
{
    return path.contains(QRegExp(".*.mp3$|.*.ogg$|.*.wav$|.*.flac$|.*.mpc$", Qt::CaseInsensitive));
}

void PlayListManager::changeCurrentPlaylist(PlayListModel* locPlayList)
{
    qDebug()<<"Changing current model";
    if (mCurrentPlayList)
    {
        mCurrentPlayList->setCurrent(false);
	mCurrentPlayList->requestRefresh();
    }
    locPlayList->setCurrent(true);
    mCurrentPlayList = locPlayList;
}

const QString* PlayListManager::getCurrentTrackPath() const
{
    return mCurrentPlayList->getCurrentTrackPath();
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
    mCurrentPlayList->replayPlayList();
}

void PlayListManager::playNextTrack()
{
    mCurrentPlayList->playNextTrack();
}

void PlayListManager::playPrevTrack()
{
    mCurrentPlayList->playPrevTrack();
}

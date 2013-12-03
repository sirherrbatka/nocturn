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

#include "maincontroler.h"
#include "./modelmanager.h"
#include "./playlistmanager.h"
#include <qobject.h>
#include "./sharedtypes.h"

MainControler* MainControler::mThisPointer = nullptr;

MainControler::MainControler(ModelManager* locModelManager) :
    mModelManager(locModelManager)
{
    assert (!mThisPointer);
    mThisPointer = this;

//     Status from PlaybackManager is forwarded by the main controler
    connect(mModelManager->getPlaybackManager(), SIGNAL(StatusChanged(SharedTypes::PlaybackState, SharedTypes::PlaybackState)), this, SIGNAL(StatusChanged(SharedTypes::PlaybackState, SharedTypes::PlaybackState)));
}

MainControler::~MainControler()
{
}

void MainControler::addPathToPlayList(QList< QUrl > list)
{
    mModelManager->getPlayListManager()->addFilesToActivePlayList(list);
}

MainControler* MainControler::getMainControler()
{
    return mThisPointer;
}

void MainControler::changeActivePlayList(PlayListModel* activePlayList)
{
    mModelManager->getPlayListManager()->changeActivePlaylist(activePlayList);
}

void MainControler::changeCurrentPlayList(PlayListModel* currentPlaylist)
{
    mModelManager->getPlayListManager()->changeCurrentPlaylist(currentPlaylist);
}


void MainControler::deletePlayList(long long unsigned int key)
{
    mModelManager->getPlayListManager()->deletePlayList(key);
}

PlayListModel* MainControler::generatePlayListModel()
{
    return mModelManager->getPlayListManager()->newPlayList();
}

void MainControler::playFile(const QString& path)
{
    mModelManager->getPlaybackManager()->playFile(path);
}

void MainControler::fileEnded()
{
    mModelManager->getPlayListManager()->fileEnded();
}

void MainControler::togglePlayback()
{
    mModelManager->getPlaybackManager()->togglePlayback();
}

void MainControler::startPlayback()
{
    mModelManager->getPlayListManager()->startPlayback();
}

void MainControler::nextTrack()
{
    mModelManager->getPlayListManager()->playNextTrack();
}

void MainControler::prevTrack()
{
    mModelManager->getPlayListManager()->playPrevTrack();
}

void MainControler::clearActivePlayList()
{
    mModelManager->getPlayListManager()->clearActivePlayList();
}

void MainControler::requestTotalDurationLabelUpdate(unsigned long long duration)
{
    emit TotalDurationChanged(duration);
}

void MainControler::stopPlayback()
{
    mModelManager->getPlaybackManager()->stopPlayback();
    mModelManager->getPlayListManager()->clearCurrentTrack();
}

void MainControler::playSelected()
{
    mModelManager->getPlayListManager()->playSelected();
}

void MainControler::setRepeateMode()
{
    mModelManager->getPlayListManager()->setRepeatMode();
}

bool MainControler::getRepeatMode() const
{
    return mModelManager->getPlayListManager()->getRepeatMode();
}

KeyHandler* MainControler::getGlobalKeyHandler()
{
    return &mGlobalKeyHandler;
}

void MainControler::quitNocturn()
{
    mModelManager->getPlayListManager()->savePlayListFiles();
}

void MainControler::relayPlayListModel(const std::vector< PlayListModel* >& playlists)
{
    emit RelayPlayListModel(playlists);
}

void MainControler::relayPlayListModel(PlayListModel* playlist)
{
    emit AutoLoadedPlayList(playlist);
}

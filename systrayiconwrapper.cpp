/*
 * <one line to give the library's name and an idea of what it does.>
 * Copyright 2014  Marek Kochanowicz <sirherrbatka@gmail.com>
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

#include "systrayiconwrapper.h"

#include <QMenu>
#include <QSystemTrayIcon>

#include "settingsmanager.h"
#include "mainview.h"
#include "playlistmanager.h"
#include "playlistmodel.h"
#include "audiotrackmodel.h"
#include "audiotrackproxy.h"
#include "maincontroler.h"

SysTrayIconWrapper::SysTrayIconWrapper(const MainView& view, const PlayListManager& playlists):
    QObject(),
    mPlaylists(playlists),
    mSystemTrayIcon(QIcon(":/nocturn.png")),
    mSystemTrayMenu(),
    mPlayAction(QIcon::fromTheme("media-playback-start"), tr("Play"), nullptr),
    mStopAction(QIcon::fromTheme("media-playback-stop"), tr("Stop"), nullptr),
    mStatus(SharedTypes::StoppedState)
{
    connect(SettingsManager::getSettingsManager(), SIGNAL(ConfigurationUpdated()), this, SLOT(updateTrayVisibility()));
    connect(&mSystemTrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), &view, SLOT(toggleWindowVisiblity(QSystemTrayIcon::ActivationReason)));
    connect(&mPlaylists, SIGNAL(CurrentSongChanged(const QString&)), this, SLOT(rebuildMenu()));
    connect(&mPlaylists, SIGNAL(ActivePlayListChanged()), this, SLOT(rebuildMenu()));
    connect(&mPlaylists, SIGNAL(TrackListChanged()), this, SLOT(rebuildMenu()));

    connect(&mPlayAction, SIGNAL(triggered(bool)), MainControler::getMainControler(), SLOT(startPlayback()));
    connect(&mStopAction, SIGNAL(triggered(bool)), MainControler::getMainControler(), SLOT(stopPlayback()));

    connect(MainControler::getMainControler(), SIGNAL(StatusChanged(SharedTypes::PlaybackState, SharedTypes::PlaybackState)),
            this, SLOT(changeStatus(SharedTypes::PlaybackState, SharedTypes::PlaybackState)));

    updateTrayVisibility();
    rebuildMenu();
    mSystemTrayIcon.setContextMenu(&mSystemTrayMenu);
}

void SysTrayIconWrapper::rebuildMenu()
{
    if(!SettingsManager::getSettingsManager()->getShowTrayIcon())
    {
      return;
    }

    PlayListModel* model = nullptr;
    if (mStatus == SharedTypes::StoppedState)
    {
        model = mPlaylists.getActiveModel();
    } else {
        model = mPlaylists.getCurrentModel();
        if (!model)
        {
            model = mPlaylists.getActiveModel();
            if (!model)
            {
                mSystemTrayMenu.clear();
                mSystemTrayMenu.addAction(&mPlayAction);
                mSystemTrayMenu.addAction(&mStopAction);
                return;
            }
        }
    }

    mSystemTrayMenu.clear();
    mSystemTrayMenu.addAction(&mPlayAction);
    mSystemTrayMenu.addAction(&mStopAction);
    mSystemTrayMenu.addSeparator();

    mTrackProxys.erase(mTrackProxys.begin(), mTrackProxys.end());
    for(unsigned i = 0; i < model->getPlayListSize(); ++i)
    {
        std::unique_ptr<AudioTrackProxy> proxy(new AudioTrackProxy(i, *this));
        mTrackProxys.push_back(std::move(proxy));
	
        connect(mSystemTrayMenu.addAction(model->getAudioTrackModel(i).getName()), SIGNAL(triggered(bool)),
                mTrackProxys.rbegin()->get(), SLOT(playThisTrack()));
    }
    mSystemTrayIcon.setContextMenu(&mSystemTrayMenu);
}

void SysTrayIconWrapper::updateTrayVisibility()
{
    mSystemTrayIcon.setVisible(SettingsManager::getSettingsManager()->getShowTrayIcon());
    rebuildMenu();
}

void SysTrayIconWrapper::playTrack(unsigned int track)
{
    PlayListModel* model = nullptr;
    if (mStatus == SharedTypes::StoppedState)
    {
        model = mPlaylists.getActiveModel();
    } else {
        model = mPlaylists.getCurrentModel();
        if (!model)
        {
            model = mPlaylists.getActiveModel();
        }
    }

    if (model)
    {
        model->setNewCurrent(track);
        model->startPlayback(false);
    }
}

void SysTrayIconWrapper::changeStatus(SharedTypes::PlaybackState newStatus, SharedTypes::PlaybackState oldStatus)
{
    mStatus = newStatus;
    if (mStatus == SharedTypes::StoppedState &&
	mPlaylists.getActiveModel() != mPlaylists.getCurrentModel())
    {
        rebuildMenu();
    }
}

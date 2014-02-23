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

#ifndef SYSTRAYICONWRAPPER_H
#define SYSTRAYICONWRAPPER_H

#include <vector>
#include <memory>

#include <QObject>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>

#include "audiotrackproxy.h"
#include "sharedtypes.h"

class MainView;
class PlayListManager;
class AudioTrackProxy;

class SysTrayIconWrapper : public QObject
{
    Q_OBJECT

public:
    SysTrayIconWrapper(const MainView& view, const PlayListManager& playlists);

private:
    QSystemTrayIcon mSystemTrayIcon;
    QMenu mSystemTrayMenu;
    const PlayListManager& mPlaylists;
    QAction mPlayAction;
    QAction mStopAction;
    SharedTypes::PlaybackState mStatus;
    std::vector<std::unique_ptr<AudioTrackProxy>> mTrackProxys;

    QString replaceUnderline(const QString& text);

private slots:
    void rebuildMenu();
    void updateTrayVisibility();
    void changeStatus(SharedTypes::PlaybackState newStatus, SharedTypes::PlaybackState oldStatus);

public slots:
    void playTrack(unsigned track);
};

#endif // SYSTRAYICONWRAPPER_H
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

#ifndef PLAYLISTMANAGER_H
#define PLAYLISTMANAGER_H

#include <map>
#include <qlist.h>
#include <qstringlist.h>
#include <QRegExp>

class QUrl;
class QDir;
class PlayListModel;
class QStringList;

class PlayListManager
{

public:
    PlayListManager();
    ~PlayListManager();

    PlayListModel* newPlayList();
    void changeActivePlaylist(PlayListModel* locPlayList);
    void changeCurrentPlaylist(PlayListModel* locPlayList);

//     Playing model is the playlist that currently plays music. Acvtive model is the model that is active in the interface

    PlayListModel* getActiveModel() const;
    PlayListModel* getCurrentModel() const;
    const QString* getCurrentTrackPath() const;

    void addFilesToActivePlaylist(QList<QUrl> &locFiles);
    void deletePlayList(long long unsigned int locKey);
    void fileEnded();
    void startPlayback();
    void playPrevTrack();
    void playNextTrack();

private:
    PlayListManager(const PlayListManager& other); //not implemented
    PlayListManager& operator=(const PlayListManager& other); //not implemented
    bool operator==(const PlayListManager& other); //not implemented
    QStringList scanDirectory(const QDir& dir);
    bool isSupportedFile(const QString& path);
    bool isAudioFile(const QString& path);

    //variables
    std::map<long long unsigned int, PlayListModel*> mPlayLists;
    unsigned long long int mNewKey {0}; //used to make unique key for mPlayLists map.
    PlayListModel* mActivePlayList {nullptr}; //Playlist model with active interface. For dropping stuff.
    PlayListModel* mCurrentPlayList {nullptr}; //playlist with song currently played. For playback controling.
};

#endif // PLAYLISTMANAGER_H

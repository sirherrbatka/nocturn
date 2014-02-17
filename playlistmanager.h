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

class PlayListManager : public QObject
{
  Q_OBJECT

public:
    PlayListManager();
    ~PlayListManager();

    PlayListModel* newPlayList();
    void changeActivePlaylist(PlayListModel* locPlayList);
    void changeCurrentPlaylist(PlayListModel* locPlayList);
    void autoLoadPath(const QString& path);
    void autoLoadPath(const QStringList& paths);

//     Playing model is the playlist that currently plays music. Acvtive model is the model that is active in the interface

    PlayListModel* getActiveModel() const;
    PlayListModel* getCurrentModel() const;
    void clearCurrentTrack(); //used to set current track on current playlist to -1, this prevents bold text on any item.
    void addFilesToActivePlayList(const QList<QUrl> &locFiles);
    void deletePlayList(long long unsigned int locKey);
    void fileEnded();
    void startPlayback();
    void playPrevTrack();
    void playNextTrack();
    void clearActivePlayList();
    void playSelected();
    void removeSelected();
    unsigned long long int getTotalDurationOfActivePlaylist();
    void setRepeatMode(); //repeat mode is configured globally.
    bool getRepeatMode() const;
    void savePlayListFiles();
    void restorePlayListFromFiles();

signals:
    void CurrentSongChanged(const QString& title);
    void ActivePlayListChanged();

private:
    PlayListManager(const PlayListManager& other); //not implemented
    PlayListManager& operator=(const PlayListManager& other); //not implemented
    bool operator==(const PlayListManager& other); //not implemented
    QList< QUrl > scanDirectory(const QDir& dir); //not implemented

    inline bool isSupportedFile(const QString& path);
    inline bool isAudioFile(const QString& path);
    void addFilesToPlaylist(const QString& locpath, PlayListModel* PlayList);

    //variables
    std::map<long long unsigned int, PlayListModel> mPlayLists;
    unsigned long long int mNewKey {0}; //used to make unique key for mPlayLists map.
    PlayListModel* mActivePlayList {nullptr}; //Playlist model with active (visible) interface. For dropping stuff.
    PlayListModel* mCurrentPlayList {nullptr}; //playlist with song currently played. For playback controling.
    bool mRepeateMode{true};
    QRegExp mAudioFilePattern;

private slots:
  void currentSongChanged();
};

#endif // PLAYLISTMANAGER_H

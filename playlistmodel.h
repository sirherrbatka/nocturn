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

#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

#include <vector>
#include <memory>
#include <qlist.h>
#include <qstringlist.h>
#include <QString>
#include <qobject.h>

class AudioTrackModel;
class TagHandler;

class PlayListModel : public QObject
{

    Q_OBJECT

public:
    PlayListModel(unsigned long long int key);
    ~PlayListModel();

    unsigned long long int getKey() const;
    void addTracks(const QStringList & paths);
    const PlayListModel* getPlayListModel();
    QString getTrackPath(int tracknumber) const;
    QString getCurrentTrackPath() const;
    QString getPlayListName() const;
    void changePlayListName(const QString& name);
    unsigned int getPlayListSize() const;
    QString getTrackName(int tracknumber) const;
    int getCurrentTrack();
    void setCurrent(bool locCurrent);
    bool getCurrent() const;
    void requestRefresh();
    int getTrackNumber(int locTrack) const;
    void setTrackNumber(int locTrack);
    QString getArtist(int locTrack) const;
    void clearMe();
    unsigned long long int getTotalDuration();
    void playSelected();

signals:
    void CurrentTrackChanged(const QString&); //transmits the path to the playback controler. Emited after track changed.
    void CurrentModelChanged(PlayListModel*); //transmits the playlist model to the playlistmanager. Emited after track changed.
    void NoNextTrack();
    void NoPrevTrack();
    void FileDoesNotExists();
    void PlayListNameChanged();
    void NeedRefreshView();
    void PlayListEmpty();
    void OutOfRange();
    void NeedRefreshPlayListName(const QString&);
    void PlaySelected();

public slots:
    void playNextTrack();
    void playPrevTrack();
    void replayPlayList();
    void enableRandomMode(bool RandomMode);
    void startPlayback(bool locRequestPlayListCheck);
    void playTrack(int track);

private:
    PlayListModel(const PlayListModel& other); //not implemented
    PlayListModel& operator=(const PlayListModel& other); //not implemented
    bool operator==(const PlayListModel& other); //not implemented
    inline void goToFirstTrack();
    inline bool playListChecks();
    void sortPlayList(); //sorts playlist according to the: album name, disc nr., track nr.
    void generatePlayListName(); //makes new name (based on the album title) when mCustomPlayListName is false
    void calculateTotalDuration();

    //variables
    unsigned long long int mKey;
    std::vector<std::unique_ptr<AudioTrackModel> > mTracks;
    std::vector<std::unique_ptr<AudioTrackModel> > mRandomModeTracks;
    int mCurrentTrack {-1};
    bool mRandomMode {false};
    QString mPlayListName {"Playlist"};
    bool mCustomPlayListName{false};
    bool mCurrent {false};
    unsigned long long int mTotalDuration{0};
};

#endif // PLAYLISTMODEL_H

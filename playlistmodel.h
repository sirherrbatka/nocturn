/*
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
#include <map>
#include <qlist.h>
#include <qstringlist.h>
#include <QString>
#include <qobject.h>
#include <QUrl>

class AudioTrackModel;

class PlayListModel : public QObject
{

    Q_OBJECT

public:
    PlayListModel(unsigned long long int key);
    ~PlayListModel();
    PlayListModel& operator=(PlayListModel&& other);
    PlayListModel(PlayListModel&& other);

    void addTracks(const QList< QUrl >& paths);
    void addTracks(const QStringList & paths);
    const PlayListModel* getPlayListModel();
    QString getPlayListName() const;
    void changePlayListName(const QString& name);
    unsigned int getPlayListSize() const;
    void setCurrent(bool locCurrent);
    bool getCurrent() const;
    void requestRefresh();
    void changeCurrentAudioTrackModel(unsigned number);
    void clearMe();
    unsigned long long int getTotalDuration() const;
    void playSelected();
    QStringList getPaths() const;
    void removeSelected();
    void deleteTrackModel(unsigned number);
    const AudioTrackModel& getAudioTrackModel(unsigned number) const;

    const unsigned long long getKey() const;
    const AudioTrackModel& getFirstAudioTrackModel() const;
    const AudioTrackModel& getLastAudioTrackModel() const;

    void playFirstTrack();
    void clearCurrentTrack();
    void updateCurrentPlayListModel();

signals:
    void CurrentModelChanged(PlayListModel*); //transmits the playlist model to the playlistmanager. Emited after track changed.
    void FileDoesNotExists();
    void PlayListNameChanged();
    void NeedRefreshView();
    void PlayListEmpty();
    void OutOfRange();
    void NeedRefreshPlayListName(const QString&);
    void PlaySelected();
    void RemoveSelected();
    void CurrentTrackChanged(int number);

public slots:
    void setNewCurrent(unsigned number);
    void playNextTrack();
    void playPrevTrack();
    void replayPlayList(bool skipModeCheck = false);
    void enableRandomMode(bool RandomMode); //not implemented
    void startPlayback(bool locRequestPlayListCheck);
    void generatePlayListName(bool mOnlyUpdate = false); //makes new name (based on the album title) when mCustomPlayListName is false

private:
    bool operator==(const PlayListModel& other); //not implemented
    inline void goToFirstTrack();
    inline bool playListChecks();
    void calculateTotalDuration();
    void deleteCurrentTrackModel();
    void sortPlayList();
    void changeCurrentTrack(int newCurrent);

    //variables
    unsigned long long int mKey;
    bool mRandomMode {false};
    QString mPlayListName {"Playlist"};
    bool mCustomPlayListName {false};
    bool mCurrent {false};
    unsigned long long int mTotalDuration {0};
    std::vector<AudioTrackModel> mTracksVector;

    int mCurrentTrack{-1};
};

#endif // PLAYLISTMODEL_H

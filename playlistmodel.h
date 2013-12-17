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
#include <map>
#include <qlist.h>
#include <qstringlist.h>
#include <QString>
#include <qobject.h>

class AudioTrackModel;

class PlayListModel : public QObject
{

    Q_OBJECT

public:
    PlayListModel(unsigned long long int key);
    ~PlayListModel();
    PlayListModel& operator=(PlayListModel&& other);
    PlayListModel(PlayListModel&& other);

    unsigned long long int getKey() const;
    void addTracks(const QStringList & paths);
    const PlayListModel* getPlayListModel();
    
    std::map<unsigned long long, AudioTrackModel>::iterator getAudioTrackModel();
    QString getPlayListName() const;
    void changePlayListName(const QString& name);
    unsigned int getPlayListSize() const;
    void setCurrent(bool locCurrent);
    bool getCurrent() const;
    void requestRefresh();
    void changeCurrentAudioTrackModel(const std::map<unsigned long long, AudioTrackModel>::iterator& newcurrent);
    void clearMe();
    unsigned long long int getTotalDuration();
    void playSelected();
    QStringList getPaths();
    void removeSelected();
    void deleteTrackModel(const std::map<unsigned long long, AudioTrackModel>::iterator &iterator);
    bool modelsToAdd();
    bool iteratorCurrent(std::map<unsigned long long, AudioTrackModel>::iterator& iterator) const;

    std::map<unsigned long long, AudioTrackModel>::iterator getFirstAudioTrackModel() const;
    std::map<unsigned long long, AudioTrackModel>::iterator getLastAudioTrackModel() const;

    void playCurrentTrack();
    void playFirstTrack();
    bool iteratorExists(std::map< unsigned long long, AudioTrackModel >::iterator& iterator);
    void clearCurrentTrack();
    void resetLooper();
    void updateCurrentPlayListModel();

signals:
    void CurrentTrackChanged(const QString&); //transmits the path to the playback controler. Emited after track changed.
    void CurrentModelChanged(PlayListModel*); //transmits the playlist model to the playlistmanager. Emited after track changed.
    void FileDoesNotExists();
    void PlayListNameChanged();
    void NeedRefreshView();
    void PlayListEmpty();
    void OutOfRange();
    void NeedRefreshPlayListName(const QString&);
    void PlaySelected();
    void RemoveSelected();

public slots:
    void playNextTrack();
    void playPrevTrack();
    void replayPlayList(bool skipModeCheck);
    void enableRandomMode(bool RandomMode);
    void startPlayback(bool locRequestPlayListCheck);
    void generatePlayListName(bool mOnlyUpdate = false); //makes new name (based on the album title) when mCustomPlayListName is false

private:
    bool operator==(const PlayListModel& other); //not implemented
    inline void goToFirstTrack();
    inline bool playListChecks();
    void calculateTotalDuration();
    void deleteCurrentTrackModel();
    void sortPlayList();
    void delinkModel(const std::map<unsigned long long, AudioTrackModel>::iterator &iterator);
    void linkTwo(const std::map<unsigned long long, AudioTrackModel>::iterator &iterator1, const std::map<unsigned long long, AudioTrackModel>::iterator &iterator2);
    void linkThree(const std::map<unsigned long long, AudioTrackModel>::iterator &iterator1, const std::map<unsigned long long, AudioTrackModel>::iterator &iterator2, const std::map<unsigned long long, AudioTrackModel>::iterator &iterator3);

    //variables
    unsigned long long int mKey;
    bool mRandomMode {false};
    QString mPlayListName {"Playlist"};
    bool mCustomPlayListName {false};
    bool mCurrent {false};
    unsigned long long int mTotalDuration {0};
    std::map<unsigned long long, AudioTrackModel> mTracks;
    unsigned long long mTrackKey{0};
    
    std::map<unsigned long long, AudioTrackModel>::iterator mCurrentTrack;
    std::map<unsigned long long, AudioTrackModel>::iterator mFirstTrack;
    std::map<unsigned long long, AudioTrackModel>::iterator mLastTrack;
    std::map<unsigned long long, AudioTrackModel>::iterator mAddingIterator;
    
};

#endif // PLAYLISTMODEL_H

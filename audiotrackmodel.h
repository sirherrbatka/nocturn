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

#ifndef AUDIOTRACKMODEL_H
#define AUDIOTRACKMODEL_H

#include <qlist.h>
#include <qstring.h>
#include <QFile>
#include <QFileInfo>
#include <memory>
#include "./taghandler.h"
#include "./playlistmodel.h"

class PlayListPageViewItem;
class PlayListModel;

class AudioTrackModel : public QObject
{
  Q_OBJECT
public:
    AudioTrackModel(const QUrl& path, PlayListModel* playlist);
    ~AudioTrackModel();
    AudioTrackModel(AudioTrackModel&& other);
    AudioTrackModel(const AudioTrackModel& other);
    AudioTrackModel& operator=(AudioTrackModel&& other);
    AudioTrackModel& operator=(const AudioTrackModel& other);
    bool operator<(const AudioTrackModel& other) const;
    bool operator==(const AudioTrackModel& other) const;

    void setAsPlayed(bool played);
    bool isPlayed() const;
    QString getPath() const;
    QUrl getURL() const;
    QString getName() const;
    long long unsigned int getDuration() const;
    bool fileExists() const;
    int getTrackNumber() const;
    QString getAlbum() const;
    int getDiscNumber() const;
    QString getArtist() const;
    void playThisTrack();
    void storeNext(const std::map<unsigned long long, AudioTrackModel>::iterator& next);
    void storePrev(const std::map<unsigned long long, AudioTrackModel>::iterator& prev);
    void storeThis(const std::map<unsigned long long, AudioTrackModel>::iterator& thistrack);
    std::map<unsigned long long, AudioTrackModel>::iterator getNextTrack() const;
    std::map<unsigned long long, AudioTrackModel>::iterator getPrevTrack() const;
//     void storeView(PlayListPageViewItem* view);
    
signals:
  void NeedRefreshLabel();
    
private:

    inline void storeName(const QString& name);
    inline void storeAlbum(const QString& album);
    inline void storeArtist(const QString& artist);

    //variables
    QFileInfo mFile;
    PlayListModel* mModel;
    QString mName;
    QString mAlbum;
    QString mArtist;
    QUrl mURL;
    bool mLinked{false};
    bool mPlayed{false};
    long long mDuration {0};
    int mTrackNumber {0};
    int mDiscNumber {-1}; //-1 = disc number not present.
    bool mCurrent {false}; //for sorting
//     PlayListPageViewItem* mView;
    std::map<unsigned long long, AudioTrackModel>::iterator mThis;
    std::map<unsigned long long, AudioTrackModel>::iterator mNext;
    std::map<unsigned long long, AudioTrackModel>::iterator mPrev;
};

#endif // AUDIOTRACKMODEL_H

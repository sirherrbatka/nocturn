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

#include <memory>

#include <qlist.h>
#include <qstring.h>
#include <QFile>
#include <QFileInfo>

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

    void setAsPlayed(bool played);
    bool isPlayed() const;
    const QString getPath() const;
    const QUrl getURL() const;
    const QString getName() const;
    const long long unsigned int getDuration() const;
    const bool fileExists() const;
    const int getTrackNumber() const;
    const QString getAlbum() const;
    const int getDiscNumber() const;
    const QString getArtist() const;
    void playThisTrack();
//     void storeView(PlayListPageViewItem* view);

signals:
  void NeedRefreshLabel();

private:

    inline void storeName(const QString& name);
    inline void storeAlbum(const std::string& album);
    inline void storeArtist(const QString& artist);

    //variables
    QFileInfo mFile;
    PlayListModel* mModel;
    QString mName;
    std::string mAlbum {""};
    QString mArtist {""};
    QUrl mURL;
    bool mPlayed{false};
    long long mDuration {0};
    int mTrackNumber {0};
    int mDiscNumber {-1}; //-1 = disc number not present.
    bool mCurrent {false}; //for sorting
};

#endif // AUDIOTRACKMODEL_H

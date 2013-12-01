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

class AudioTrackModel
{
public:
    AudioTrackModel(const QString& path);
    ~AudioTrackModel();

    QString getPath() const;
    QString getName() const;
    long long unsigned int getDuration() const;
    bool fileExists() const;
    int getTrackNumber() const;
    QString getAlbum() const;
    int getDiscNumber() const;
    QString getArtist() const;

    void markAsCurrent(bool active); //for sorting purpose
    bool isCurrent(); //for sorting

private:
//     AudioTrackModel& operator=(const AudioTrackModel& other); //not implemented
    bool operator==(const AudioTrackModel& other); //not implemented

    inline void storeName(const QString& name);
    inline void storeAlbum(const QString& album);
    inline void storeArtist(const QString& artist);

    //variables
    QString mPath;
    QFileInfo mFile;

    QString mName;
    QString mAlbum;
    QString mArtist;
    long long mDuration {0};
    int mTrackNumber {0};
    int mDiscNumber {-1}; //-1 = disc number not present.
    bool mCurrent {false}; //for sorting
};

#endif // AUDIOTRACKMODEL_H

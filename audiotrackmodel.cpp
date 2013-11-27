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

#include "audiotrackmodel.h"
#include "taghandler.h"
#include <QFile>
#include <QDebug>
#include <memory>


AudioTrackModel::AudioTrackModel(const QString& path) :
    mPath(path),
    mFile(new QFileInfo(path))
{
    qDebug()<<"loaded file"<<" "<<path;
    TagHandler TagHandler(path);
    if (TagHandler.hasTags() == false)
    {
        mName = mFile->baseName();
    } else {
        storeName(TagHandler.getTitle());
	storeArtist(TagHandler.getArtist());
        mDuration = TagHandler.getDuration();
        mDiscNumber = TagHandler.getDisc();
        mTrackNumber = TagHandler.getTrack();
        storeAlbum(TagHandler.getAlbum());
        qDebug()<<"Track number is"<<mTrackNumber;
        qDebug()<<"Disc number is"<<mDiscNumber;
    }
}

AudioTrackModel::~AudioTrackModel()
{
    qDebug()<<"AudioTrackModel Destroyed";
    delete mFile;
}

inline void AudioTrackModel::storeAlbum(const QString& album)
{
    mAlbum = album;
}


const QString* AudioTrackModel::getPath() const
{
    return &mPath;
}

const QString* AudioTrackModel::getName() const
{
    return &mName;
}

bool AudioTrackModel::fileExists() const
{
    return mFile->exists();
}

inline void AudioTrackModel::storeName(const QString& name)
{
    if (name == "")
    {
        mName = mFile->baseName();
    } else {
        mName = name;
    }
}

long int AudioTrackModel::getDuration() const
{
    return mDuration;
}

int AudioTrackModel::getDiscNumber() const
{
    return mDiscNumber;
}

const QString* AudioTrackModel::getAlbum() const
{
    return &mAlbum;
}

int AudioTrackModel::getTrackNumber() const
{
    return mTrackNumber;
}

const QString* AudioTrackModel::getArtist() const
{
    return &mArtist;
}

void AudioTrackModel::storeArtist(const QString& artist)
{
    mArtist = artist;
}

bool AudioTrackModel::isCurrent()
{
  return mCurrent;
  mCurrent = false;
}

void AudioTrackModel::markAsCurrent(bool active)
{
 mCurrent = active;
}

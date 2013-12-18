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
#include <QString>
#include "./maincontroler.h"
#include "playlistpageviewitem.h"

class AudioTracksHolder;
AudioTrackModel::AudioTrackModel(const QString& path, PlayListModel* playlist) :
    mPath(path),
    mFile(path),
    mModel(playlist)
{
    qDebug()<<"loaded file"<<" "<<path;
    TagHandler TagHandler(path);
    if (TagHandler.hasTags() == false)
    {
        mName = mFile.baseName();
    } else {
        storeName(TagHandler.getTitle());
        storeArtist(TagHandler.getArtist());
        mDiscNumber = TagHandler.getDisc();
        mTrackNumber = TagHandler.getTrack();
        storeAlbum(TagHandler.getAlbum());
        qDebug()<<"Track number is"<<mTrackNumber;
        qDebug()<<"Disc number is"<<mDiscNumber;
    }
    mDuration = TagHandler.getDuration();
}

AudioTrackModel::~AudioTrackModel()
{
}

AudioTrackModel::AudioTrackModel(AudioTrackModel&& other) :
    mName(std::move(other.mName)),
    mPath(std::move(other.mPath)),
    mFile(std::move(other.mFile)),
    mDuration(other.mDuration),
    mDiscNumber(other.mDiscNumber),
    mAlbum(std::move(other.mAlbum)),
    mArtist(std::move(other.mArtist)),
    mTrackNumber(other.mTrackNumber),
    mCurrent(other.mCurrent),
    mModel(other.mModel)
{
}

AudioTrackModel::AudioTrackModel(const AudioTrackModel& other) :
    mName(std::move(other.mName)),
    mPath(std::move(other.mPath)),
    mFile(std::move(other.mFile)),
    mDuration(other.mDuration),
    mDiscNumber(other.mDiscNumber),
    mAlbum(std::move(other.mAlbum)),
    mArtist(std::move(other.mArtist)),
    mTrackNumber(other.mTrackNumber),
    mCurrent(other.mCurrent),
    mModel(other.mModel)
{
}

AudioTrackModel& AudioTrackModel::operator=(AudioTrackModel&& other)
{
    mPath = std::move(other.mPath);
    mFile = std::move(other.mFile);
    mDuration = std::move(other.mDuration);
    mDiscNumber = std::move(other.mDiscNumber);
    mAlbum = std::move(other.mAlbum);
    mArtist = std::move(other.mArtist);
    mTrackNumber = std::move(other.mTrackNumber);
    mCurrent = std::move(other.mCurrent);
    mModel = std::move(other.mModel);
    return *this;
}

AudioTrackModel& AudioTrackModel::operator=(const AudioTrackModel& other)
{
    mPath =other.mPath;
    mFile = other.mFile;
    mDuration = other.mDuration;
    mDiscNumber = other.mDiscNumber;
    mAlbum = other.mAlbum;
    mArtist = other.mArtist;
    mTrackNumber = other.mTrackNumber;
    mCurrent = other.mCurrent;
    mModel = other.mModel;
    return *this;
}

inline void AudioTrackModel::storeAlbum(const QString& album)
{
    mAlbum = album;
}


QString AudioTrackModel::getPath() const
{
    return mPath;
}

QString AudioTrackModel::getName() const
{
    return mName;
}

bool AudioTrackModel::fileExists() const
{
    return mFile.exists();
}

inline void AudioTrackModel::storeName(const QString& name)
{
    if (name == "")
    {
        mName = mFile.baseName();
    } else {
        mName = name;
    }
}

unsigned long long int AudioTrackModel::getDuration() const
{
    return mDuration;
}

int AudioTrackModel::getDiscNumber() const
{
    return mDiscNumber;
}

QString AudioTrackModel::getAlbum() const
{
    return mAlbum;
}

int AudioTrackModel::getTrackNumber() const
{
    return mTrackNumber;
}

QString AudioTrackModel::getArtist() const
{
    return mArtist;
}

void AudioTrackModel::storeArtist(const QString& artist)
{
    mArtist = artist;
}

bool AudioTrackModel::operator==(const AudioTrackModel& other) const
{
    if (mAlbum != other.mAlbum)
    {
        return false;
    }
    if (mTrackNumber != other.mTrackNumber)
    {
        return false;
    }
    if (mTrackNumber != other.mTrackNumber)
    {
        return false;
    }
    return true; //silencing warning
}


bool AudioTrackModel::operator<(const AudioTrackModel& other) const
{
    if (mAlbum != other.mAlbum)
    {
        if(0<(mAlbum.localeAwareCompare(other.mAlbum), Qt::CaseSensitive))
        {
            return true;
        }

        if(0>(mAlbum.localeAwareCompare(other.mAlbum), Qt::CaseSensitive))
        {
            return false;
        }
    }
    
    if (mTrackNumber != other.mTrackNumber)
    {
        if(getDiscNumber() < other.getDiscNumber() and getDiscNumber() != -1 and other.getDiscNumber() != -1 )
        {
            return true;
        }

        if(getDiscNumber() > other.getDiscNumber() and other.getDiscNumber() != -1 and other.getDiscNumber() != -1 )
        {
            return false;
        }
    }
    
    if (mTrackNumber != other.mTrackNumber)
    {
        if(getTrackNumber() < other.getTrackNumber() )
        {
            return true;
        }

        if(getTrackNumber() > other.getTrackNumber() )
        {
            return false;
        }
    }
    return false; //silencing warning
}

void AudioTrackModel::playThisTrack()
{
    mModel->changeCurrentAudioTrackModel(mThis);
    MainControler::getMainControler()->playFile(mPath);
    mModel->updateCurrentPlayListModel();
}

std::map< unsigned long long, AudioTrackModel >::iterator AudioTrackModel::getNextTrack() const
{
    return mNext;
}

std::map< unsigned long long, AudioTrackModel >::iterator AudioTrackModel::getPrevTrack() const
{
    return mPrev;
}

void AudioTrackModel::storeNext(const std::map< unsigned long long, AudioTrackModel >::iterator& next)
{
    mNext = next;
}

void AudioTrackModel::storePrev(const std::map< unsigned long long, AudioTrackModel >::iterator& prev)
{
    mPrev = prev;
}

void AudioTrackModel::storeThis(const std::map< unsigned long long, AudioTrackModel >::iterator& thistrack)
{
    mThis = thistrack;
}

bool AudioTrackModel::isPlayed() const
{
    return mPlayed;
}

void AudioTrackModel::setAsPlayed(bool played)
{
    mPlayed = played;
    emit NeedRefreshLabel();
}



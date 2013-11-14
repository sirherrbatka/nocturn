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
#include <qt4/QtCore/QFile>
#include <QDebug>
#include <memory>


AudioTrackModel::AudioTrackModel(const QString& path) :
    mPath(path),
    mFile(new QFileInfo(path))
{
    qDebug()<<"loaded file"<<" "<<path;
    TagHandler TagHandler;
    TagHandler.inputFile(path);
    if (TagHandler.hasTags() == false)
    {
        mName = mFile->baseName();
    } else {
        storeName(TagHandler.getTitle());
        mDuration = TagHandler.getDuration();
    }
}

AudioTrackModel::~AudioTrackModel()
{
    delete mFile;
}

const QString* AudioTrackModel::getPath() const
{
    return &mPath;
}

const QString* AudioTrackModel::getName() const
{
    return &mName;
}

bool AudioTrackModel::fileExists()
{
    return mFile->exists();
}

void AudioTrackModel::storeName(const QString& name)
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


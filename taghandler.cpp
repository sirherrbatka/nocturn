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

#include "taghandler.h"
#include <QStringList>
#include <cassert>
#include <taglib/tpropertymap.h>
#include <taglib/fileref.h>
#include <taglib/tstring.h>
#include <taglib/tag.h>
#include <string>
#include <phonon/MediaObject>
#include <audioproperties.h>

TagHandler::TagHandler(const QString& path) :
    mFile(new TagLib::FileRef (path.toLocal8Bit() ) )
{
}

TagHandler::~TagHandler()
{
}

std::string TagHandler::getAlbum() const
{
    return mFile.get()->tag()->album().toCString();
}

QString TagHandler::getArtist() const
{
    return QString::fromStdString(mFile.get()->tag()->artist().toCString());
}

int TagHandler::getDisc() const
{
    TagLib::PropertyMap map = mFile->file()->properties();
    int discnumber = -1;
    if (map.contains("DISCNUMBER")) {
        discnumber = map["DISCNUMBER"][0].toInt();
    }
    return discnumber;
}

long long int TagHandler::getDuration() const
{
    return mFile->audioProperties()->length();
}

QString TagHandler::getTitle() const
{
    return QString::fromStdString(mFile.get()->tag()->title().toCString());
}

int TagHandler::getTrack() const
{
    return mFile.get()->tag()->track();
}

bool TagHandler::hasTags() const
{
    return  !(mFile.get()->tag()->isEmpty());
}


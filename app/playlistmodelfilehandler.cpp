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

#include "playlistmodelfilehandler.h"
#include <QDir>
#include <QDebug>

PlayListModelFileHandler::PlayListModelFileHandler()
{
    mPath = (QDir::homePath() + "/.nocturnplaylists");
}

PlayListModelFileHandler::~PlayListModelFileHandler()
{

}

void PlayListModelFileHandler::savePlayListFile(const QStringList& paths)
{
    QFile locFile(mPath);
    qint64 filesize = locFile.size();
    if (locFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
    {
        QTextStream in(&locFile);
        in<<"|Begin|"<<"\n";
        for (auto &path : paths)
        {
            in<<path<<"\n";
        }
        in<<"|End|"<<"\n\n";
        locFile.close();
    } else {
        qDebug()<<"Could not open playlist file for saving";
    }
}

bool PlayListModelFileHandler::removePlayListFile()
{
    QFile PlayListFile(mPath);
    return PlayListFile.remove();
}

std::vector< std::vector<QString> > PlayListModelFileHandler::loadPlayListFile()
{
    std::vector<std::vector<QString>> paths;

    QFile locFile(mPath);
    if (locFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        int position = -1; //actually easier this way
        QTextStream in (&locFile);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            if (line == "|Begin|")
            {
                position += 1;
                paths.resize(paths.size() + 1);
                continue;
            } else if (line == "|End|") {
                continue;
            } else {
                if (!(line.isEmpty()))
                {
                    if (paths.empty())
                    {
                        paths.resize(1);
                    }
                    (paths[position]).push_back(line);
                }
            }
        }
    }
    else {
        qDebug()<<"Could not open playlist file for loading";
    }

    return paths;
}

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

#ifndef PLAYBACKMODEL_H
#define PLAYBACKMODEL_H

#include <qobject.h>

#include "./sharedtypes.h"

class QUrl;
class PlaybackModel : public QObject
{
    Q_OBJECT
public:

    PlaybackModel();
    ~PlaybackModel();

    virtual qint64 getTotalTime();
    virtual void togglePlayback();
    
signals:
    void FileEnded();
    void PlayingLocalFile();
    void SecondHasPassed();
    void StatusChanged(SharedTypes::PlaybackState, SharedTypes::PlaybackState);

public slots:
    virtual void playFile(const QUrl& url);
    virtual void stopPlayback();

};

#endif // PLAYBACKMODEL_H

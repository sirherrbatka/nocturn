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

#ifndef PLAYBACKPHONON_H
#define PLAYBACKPHONON_H

#include <memory>

#include <QString>
#include <QUrl>

#include <phonon/mediaobject.h>
#include <phonon/audiooutput.h>

#include "maincontroler.h"
#include "sharedtypes.h"
#include "playbackmodel.h"

class PlaybackPhonon : public PlaybackModel
{
    Q_OBJECT
public:
    PlaybackPhonon();
    ~PlaybackPhonon();
    Phonon::MediaObject* getPhonon();
    Phonon::AudioOutput* getAudio();
public slots:

    void changeStatus(Phonon::State oldstatus, Phonon::State newstatus);
    void playFile(const QUrl& url);
    void togglePlayback();
    void stopPlayback();

private:
    std::unique_ptr<Phonon::MediaObject> mPhonon {new Phonon::MediaObject()};
    std::unique_ptr<Phonon::AudioOutput> mAudio {new Phonon::AudioOutput()};

};

#endif // PLAYBACKPHONON_H

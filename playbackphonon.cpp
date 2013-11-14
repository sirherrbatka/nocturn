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

#include "playbackphonon.h"
#include <QDebug>
#include "./sharedtypes.h"

PlaybackPhonon::PlaybackPhonon()
{
    qDebug()<<"Phonon Created!";
    Phonon::createPath(mPhonon.get(), mAudio.get());
    mPhonon->setTickInterval(1000);
    connect(mPhonon.get(), SIGNAL(tick(qint64)), this, SIGNAL(SecondHasPassed()));
    connect(mPhonon.get(), SIGNAL(finished()), this, SIGNAL(FileEnded()));
    connect(mPhonon.get(), SIGNAL(stateChanged(Phonon::State, Phonon::State)), this, SLOT(changeStatus(Phonon::State, Phonon::State)));
}

void PlaybackPhonon::playFile(const QString* path)
{
    qDebug()<<"Phonon playing";
    mPhonon->setCurrentSource(*path);
    mPhonon->play();
    emit PlayingLocalFile();
}

PlaybackPhonon::~PlaybackPhonon()
{

}

Phonon::AudioOutput* PlaybackPhonon::getAudio()
{
    return mAudio.get();
}


Phonon::MediaObject* PlaybackPhonon::getPhonon()
{
    return mPhonon.get();
}

void PlaybackPhonon::togglePlayback()
{
    auto picker = mPhonon->state();
    switch (picker)
    {
    case 2:
        mPhonon->pause();
        break;
    case 1:
        break;
    case 0:
        break;
    case 3:
        break;
    case 5:
        break;
    case 4:
        mPhonon->play();
        break;
    }
}

void PlaybackPhonon::changeStatus(Phonon::State newstatus, Phonon::State oldstatus)
{
    SharedTypes::PlaybackState locnew;
    SharedTypes::PlaybackState locold;

    switch (newstatus)
    {
    case Phonon::LoadingState:
        locnew = SharedTypes::LoadingState;
        break;
    case Phonon::StoppedState:
        locnew = SharedTypes::StoppedState;
        break;
    case Phonon::PlayingState:
        locnew = SharedTypes::PlayingState;
        break;
    case Phonon::BufferingState:
        locnew = SharedTypes::BufferingState;
        break;
    case Phonon::PausedState:
        locnew = SharedTypes::PausedState;
        break;
    case Phonon::ErrorState:
        locnew = SharedTypes::ErrorState;
        break;
    }

    switch (oldstatus)
    {
    case Phonon::LoadingState:
        locold = SharedTypes::LoadingState;
        break;
    case Phonon::StoppedState:
        locold = SharedTypes::StoppedState;
        break;
    case Phonon::PlayingState:
        locold = SharedTypes::PlayingState;
        break;
    case Phonon::BufferingState:
        locold = SharedTypes::BufferingState;
        break;
    case Phonon::PausedState:
        locold = SharedTypes::PausedState;
        break;
    case Phonon::ErrorState:
        locold = SharedTypes::ErrorState;
        break;
    }
    
    emit StatusChanged(locnew, locold);
}

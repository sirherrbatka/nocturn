/*
 * <one line to give the library's name and an idea of what it does.>
 * Copyright 2014  Marek Kochanowicz <sirherrbatka@gmail.com>
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

#include "settingsmanager.h"

#include <cassert>
#include <QSettings>
#include <iostream>
#include <QStringList>
#include <QUrl>

SettingsManager* SettingsManager::mThisPointer = nullptr;

SettingsManager::SettingsManager() :
    mSettings("Nocturn")
{
    assert(!mThisPointer);
    mThisPointer = this;

    mSettings.beginGroup("View");
    mSongAsWIndowTitle = mSettings.value("SongTitleAsWindowTitle").toBool();
    mShowTrayIcon = mSettings.value("ShowTrayIcon").toBool();
    mSettings.endGroup();

    mSettings.beginGroup("Streams");
    const QStringList& streams(mSettings.childKeys());
    bool url = false;
    QString name;
    for (auto it(streams.begin()); it != streams.end(); ++it)
    {
        auto value(mSettings.value(*it));
        url = !url;
        if (url)
        {
            name = value.toString();
        } else {
            mAudioStreams.push_back(std::make_pair(name, value.toUrl()));
        }
    }
    mSettings.endGroup();
}

SettingsManager* SettingsManager::getSettingsManager()
{
    return mThisPointer;
}

const bool SettingsManager::getSongAsWindowTitle() const
{
    return mSongAsWIndowTitle;
}

const bool SettingsManager::getShowTrayIcon() const
{
    return mShowTrayIcon;
}

void SettingsManager::setShowTrayIcon(bool checked)
{
    mShowTrayIcon = checked;
    mSettings.beginGroup("View");
    mSettings.setValue("ShowTrayIcon", checked);
    mSettings.endGroup();
    emit ConfigurationUpdated();
}


void SettingsManager::setSongAsWindowTitle(bool checked)
{
    mSongAsWIndowTitle = checked;
    mSettings.beginGroup("View");
    mSettings.setValue("SongTitleAsWindowTitle", checked);
    mSettings.endGroup();
    emit ConfigurationUpdated();
}

void SettingsManager::setRepeatMode()
{
    mRepeatMode = !mRepeatMode;
}

const bool SettingsManager::getRepeatMode() const
{
  return mRepeatMode;
}

const std::vector< std::pair< QString, QUrl > > SettingsManager::getStreams()
{
  return mAudioStreams;
}

void SettingsManager::replaceAudioStreams(const std::vector<std::pair<QString, QUrl>>& streams)
{
    mAudioStreams = streams;
    mSettings.remove("Streams");
    mSettings.beginGroup("Streams");
    int i = 0;
    for (auto it(mAudioStreams.begin()); it != mAudioStreams.end(); ++it)
    {
            mSettings.setValue(QString(i), it->first);
            ++i;
            mSettings.setValue(QString(i), it->second);
            ++i;
    }
    mSettings.endGroup();

    emit streamsChanged();
}
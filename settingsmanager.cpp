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

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

#include "settingsview.h"

#include "settingsmanager.h"
#include "nocturn.h"

SettingsView::SettingsView()
{
    setupUi(this);
    mSongAsWindowTitle->setChecked(SettingsManager::getSettingsManager()->getSetting("view/SongTitleAsWindowTitle").toBool());
    mShowTrayIcon->setChecked(SettingsManager::getSettingsManager()->getSetting("view/ShowTrayIcon").toBool());
    mPathEdit->setText(SettingsManager::getSettingsManager()->getSetting("file/PathToMusic").toString());

    connect(mStoreButton, SIGNAL(clicked()), this, SLOT(storeValues()));

    setWindowTitle("Settings");
}

void SettingsView::storeValues()
{
    SettingsManager::getSettingsManager()->setValue("view/SongTitleAsWindowTitle", mSongAsWindowTitle->isChecked());
    SettingsManager::getSettingsManager()->setValue("view/ShowTrayIcon", mShowTrayIcon->isChecked());
    SettingsManager::getSettingsManager()->setValue("file/PathToMusic", mPathEdit->text());
}

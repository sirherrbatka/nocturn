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

#include "mainviewkeyhandler.h"
#include "./maincontroler.h"
#include <QDebug>
#include <Qt>

MainViewKeyHandler::MainViewKeyHandler()
{
    mGlobalKeyHandler = MainControler::getMainControler()->getGlobalKeyHandler();
}

MainViewKeyHandler::~MainViewKeyHandler()
{

}

void MainViewKeyHandler::grabKeyEvent(int key)
{
    switch (key)
    {
    case Qt::Key_C:
        mGlobalKeyHandler->grabGlobalKeyEvent(key);
        break;
    case Qt::Key_P:
        mGlobalKeyHandler->grabGlobalKeyEvent(key);
        break;
    case Qt::Key_S:
        mGlobalKeyHandler->grabGlobalKeyEvent(key);
        break;
    case Qt::Key_D:
	MainControler::getMainControler()->removeSelected();
        break;
    case Qt::Key_W:
        emit CloseTabKey(-1);
        break;
    case Qt::Key_T:
        emit NewPlayListViewKey();
        break;
    case Qt::Key_L:
        emit SwitchPlayListViewKey(1);
        break;
    case Qt::Key_H:
        emit SwitchPlayListViewKey(-1);
        break;
    case Qt::Key_J:
        emit SwitchRowKey(1);
        break;
    case Qt::Key_K:
        emit SwitchRowKey(-1);
        break;
    case Qt::Key_Return:
        MainControler::getMainControler()->playSelected();
        break;
    case Qt::Key_R:
        mGlobalKeyHandler->grabGlobalKeyEvent(key);
        break;
    }
}

void MainViewKeyHandler::newPlaybackStatus(SharedTypes::PlaybackState newStatus)
{
    mGlobalKeyHandler->storeState(newStatus);
}

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

#ifndef MAINCONTROLER_H
#define MAINCONTROLER_H

#include <qobject.h>
#include <QUrl>
#include <memory>
#include <cassert>
#include "./sharedtypes.h"
#include "./keyhandler.h"

class ModelManager;
class PlayListModel;

class MainControler : public QObject
{
    Q_OBJECT

public:
    MainControler(ModelManager* locModelManager);
    ~MainControler();
    static MainControler* getMainControler();
    PlayListModel* generatePlayListModel(); //TODO consider different solution
    void requestTotalDurationLabelUpdate(unsigned long long duration);
    void playSelected();
    bool getRepeatMode() const;
    KeyHandler* getGlobalKeyHandler();

signals:
    void StatusChanged(SharedTypes::PlaybackState, SharedTypes::PlaybackState);
    void TotalDurationChanged(unsigned long long);

public slots:
    void nextTrack();
    void prevTrack();
    void changeCurrentPlayList(PlayListModel* currentPlaylist);
    void changeActivePlayList(PlayListModel* activePlayList);
    void addPathToPlayList(QList< QUrl > list); //called by the inteface drag&drop signal currently.
    void deletePlayList(unsigned long long int key);
    void playFile(const QString& path);
    void fileEnded();
    void togglePlayback();
    void stopPlayback();
    void startPlayback();
    void clearActivePlayList();
    void setRepeateMode();

private:
    MainControler(const MainControler& other); //not implemented
    MainControler& operator=(const MainControler& other); //not implemented
    bool operator==(const MainControler& other); //not implemented

    ModelManager* mModelManager;
    static MainControler* mThisPointer;
    KeyHandler mGlobalKeyHandler;
};

#endif // MAINCONTROLER_H

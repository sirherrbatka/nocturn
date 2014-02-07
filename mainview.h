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

#ifndef MAINVIEW_H
#define MAINVIEW_H

#include "./ui_mainform.h"
#include <QMainWindow>
#include <QDropEvent>
#include <QKeyEvent>
#include <QUrl>
#include <vector>
#include "./sharedtypes.h"
#include "./mainviewkeyhandler.h"
#include <memory>
#include <QHBoxLayout>

class PlayListModel;
class PlayListPageView;
class PlaybackModel;
class MainView : public QMainWindow, public Ui_MainWindow
{
    Q_OBJECT

public:
    void dropEvent(QDropEvent *ev);
    void dragEnterEvent(QDragEnterEvent *ev);
    void keyPressEvent(QKeyEvent *ev);
    void setFirstTab(); //creates one playlist if there is no playlist present.

    MainView(PlaybackModel* PlaybackModel, bool autoLoadMode);
//     ~MainView(); TODO add definition

    MainViewKeyHandler* getKeyHandler();

signals:
    void pathDropped(QList<QUrl>);
    void modelSignal(PlayListModel*);
    void TogglePlayback();
    void StartPlaybackOnActivePlaylist();

private slots:
    void newPlayListView(bool autoswitch = true, PlayListModel* playlist = nullptr);
    void closeTab(int index);
    void notifyPlayListManagerAboutActivePlayListChange(int index);
    void changeStatus(SharedTypes::PlaybackState oldstatus, SharedTypes::PlaybackState newstatus);
    void toggleButtonControl();
    void refreshTotalDurationLabel(unsigned long long duration);
    void switchPlayListView(int side);
    void relayPlayListModel(const std::vector<PlayListModel*>& playlists);
    void autoLoadPlayList(PlayListModel* playlist);
    void showConfWindow();

private:
    //methods
    PlayListModel* getPlayListModel(int index);
    inline void updateLabel();
    inline void updateToggleButtonIcon();

    //variables
    SharedTypes::PlaybackState mState{SharedTypes::StoppedState};
    MainViewKeyHandler mKeyHandler;
};

#endif

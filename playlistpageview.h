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

#ifndef PLAYLISTPAGEVIEW_H
#define PLAYLISTPAGEVIEW_H
#include <QListWidget>
#include <memory>
#include <QKeyEvent>

class AudioTrackModel;
class MainViewKeyHandler;
class PlayListModel;
class QWidget;
class QTabWidget;
class PlayListPageView : public QListWidget
{
    Q_OBJECT
public:
    PlayListModel* getModel();
    PlayListPageView(PlayListModel* model, QTabWidget* parent, MainViewKeyHandler* keyhandler);
    ~PlayListPageView();
    void keyPressEvent(QKeyEvent *ev);
    int getCurrentRow();
    const AudioTrackModel& getAudioTrackModel(unsigned number) const;
    QString getPlayListName();

public slots:
    void refreshView();
    void doubleClicked ( QListWidgetItem* item );
    void needRefreshPlayListName(const QString& locNewName);
    void switchRow(int direction);
    void playSelected();
    void removeSelected();
    void updateMe();

signals:
    void PlayListViewDestroyed(unsigned long long int);

private:
    //methods

    //variables
    PlayListModel* mModel;
    QTabWidget* mParent;
    MainViewKeyHandler* mKeyHandler;
    
private slots:
  void markNewPlayed(int oldNumber, int newNumber);
};

#endif // PLAYLISTPAGEVIEW_H

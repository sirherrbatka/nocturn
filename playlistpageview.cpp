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

#include "playlistpageview.h"
#include "./playlistmodel.h"
#include "maincontroler.h"
#include <qt4/QtGui/qfont.h>
#include <qlist.h>
#include <QDebug>
#include "./mainviewkeyhandler.h"
#include "./nocturn.h"
#include <QListWidgetItem>
#include "./playlistpageviewitem.h"
#include <QTabWidget>

PlayListPageView::PlayListPageView(PlayListModel* model, QTabWidget* parent, MainViewKeyHandler* keyhandler) :
    mParent(parent),
    mModel(model),
    mKeyHandler(keyhandler)
{
    //PlayListPageView -> main controler
    connect(this, SIGNAL( PlayListViewDestroyed(unsigned long long int) ), MainControler::getMainControler(), SLOT( deletePlayList(unsigned long long int ) ) );

    //internal connections
    connect(this, SIGNAL(itemDoubleClicked(QListWidgetItem* )), this, SLOT(doubleClicked(QListWidgetItem* )));

    //signals from model
    connect(mModel, SIGNAL(PlaySelected()), this, SLOT(playSelected()));
    connect(mModel, SIGNAL(NeedRefreshPlayListName(const QString&)), this, SLOT(needRefreshPlayListName(const QString&))); //ugly! works only for active playlist. At least I don't need to create new class from qtabwidget
    connect(mModel, SIGNAL( NeedRefreshView() ), this, SLOT( refreshView() ) );

    //signals from keyhandler
    connect(mKeyHandler, SIGNAL(SwitchRowKey(int)), this, SLOT(switchRow(int)));

    //Setting behavior
    setSortingEnabled(false);
    setCurrentRow(0);
    setSelectionMode(QAbstractItemView::SingleSelection);
    refreshView();
}


PlayListModel* PlayListPageView::getModel()
{
    return mModel;
}

PlayListPageView::~PlayListPageView()
{
    if (!(nocturn::getNocturn()->nocturnQuits()))
    {
        emit PlayListViewDestroyed(mModel->getKey());
    }
    qDebug()<<"Play List view Is being destroyed";
}

void PlayListPageView::refreshView()
{
    int selected = currentRow();
    clear();
    int locCurrent = getModel()->getCurrentTrack();
    int locSize = mModel->getPlayListSize();
    for (int i = 0; i < locSize; ++i )
    {
        QListWidgetItem* item = new PlayListPageViewItem(mModel->getArtist(i) + " - " + mModel->getTrackName(i), i);
        if (i == locCurrent and mModel->getCurrent())
        {
            QFont font;
            font.setBold(true);
            item->setFont(font);
        }
        addItem(item);
    }
    setCurrentRow(selected);
}

void PlayListPageView::doubleClicked(QListWidgetItem * item)
{
    mModel->playTrack(dynamic_cast<PlayListPageViewItem*>(item)->getPosition());
}

void PlayListPageView::needRefreshPlayListName(const QString &locNewName)
{
    mParent->setTabText(mParent->currentIndex(), locNewName);
    mParent->update();
}

void PlayListPageView::keyPressEvent(QKeyEvent *ev)
{
    ev->setAccepted(true);
    mKeyHandler->grabKeyEvent(ev->key());
}

void PlayListPageView::switchRow(int direction)
{
    int newRow = currentRow() + direction;
    if(newRow >= count())
    {
        newRow = count() - 1;
    }
    if(newRow < 0)
    {
        newRow = 0;
    }
    setCurrentRow(newRow);
}

void PlayListPageView::playSelected()
{
    mModel->playTrack(currentRow());
}

QString PlayListPageView::getPlayListName()
{
    return mModel->getPlayListName();
}

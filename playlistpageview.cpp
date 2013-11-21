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
#include <QDebug>

PlayListPageView::PlayListPageView(PlayListModel* model) :
    mModel(model)
{
    connect(this, SIGNAL( PlayListViewDestroyed(unsigned long long int) ), MainControler::getMainControler(), SLOT( deletePlayList(unsigned long long int ) ) );
    connect(mModel, SIGNAL( NeedRefreshView() ), this, SLOT( refreshView() ) );
    connect(this, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(doubleClicked(int, int)));
    qDebug()<<"Playlist view created";
}


PlayListModel* PlayListPageView::getModel()
{
    return mModel;
}

PlayListPageView::~PlayListPageView()
{
    emit PlayListViewDestroyed(mModel->getKey());
    qDebug()<<"Play List view Is being destroyed";
}

void PlayListPageView::refreshView()
{
    clear();
    unsigned locCurrent = getModel()->getCurrentTrack();
    unsigned int locSize = mModel->getPlayListSize();
    setRowCount(locSize);
    setColumnCount(1);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    for (unsigned int i = 0; i < locSize; ++i )
    {
	QTableWidgetItem* item = new QTableWidgetItem(*(mModel->getTrackName(i)));
	if (i == locCurrent and mModel->getCurrent())
	{
	  QFont font;
	  font.setBold(true);
	  item->setFont(font);
	}
        setItem(i, 0, item);
    }
}

void PlayListPageView::doubleClicked(int row, int column)
{
    mModel->playTrack(row);
}
